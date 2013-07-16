#include <stdlib.h>
#include<QApplication>
#include<kconfiggroup.h>
#include<ksharedconfig.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<KGlobal>
#include<KStandardDirs>
#include <QProcess>
#include<QDebug>

#include<func.h>
#include<config/config.h>
#include<Basic/status.h>
#include<audioFiles.h>

#include"database.h"
#include"editMultFiles.h"
#include"dbJobs/rescanJob.h"
#include"libraryFolder.h"
#include<QSqlDriverPlugin>


#include<QDir>

#define DB_VERSION 1

#ifdef EMBEDDED_MYSQL
#include"embeddedMysqlCreator.h"
#endif

database::databaseConection::databaseConection()
    :QObject(),
     _state ( NORMAL )
{


    initDb();
    connect ( audioFiles::self(),SIGNAL ( changed ( audioFiles::audioFile ) ),this,SLOT ( emitUpdated ( audioFiles::audioFile ) ) );
    connect ( editMultFiles::self(),SIGNAL ( started() ),this,SLOT ( editMultFilesStart() ) );
    connect ( editMultFiles::self(),SIGNAL ( finished() ),this,SLOT ( editMultFilesStop() ) );

}

void database::databaseConection::initDb()
{
#ifdef EMBEDDED_MYSQL
    QString s=core::config->saveLocation ( "database" );
    mysqlServerOptions.append ( QString() );
    mysqlServerOptions.append ( "--datadir="+s );
    mysqlServerOptions.append ( "--character-set-server=utf8" );
    mysqlServerOptions.append ( "--collation-server=utf8_bin" );
    mysqlServerOptions.append ( QString() );
    mysqlHome=s;

    bool firstTime=false;

    QDir dbPath=QDir ( s );

    if ( !dbPath.exists ( "karakaxa" ) )
    {
        dbPath.mkpath ( "karakaxa" );
        firstTime=true;
    }

    QSqlDatabase::registerSqlDriver ( "EM_QMYSQL",new  embeddedMysqlCreator );
    createConnection();

    if ( firstTime||needSetup() )
    {
        setUpDb();
    }

#else
    createConnection();

    if ( needSetup() )
    {
        setUpDb();
    }

#endif
}


bool database::databaseConection::createConnection()
{
    if ( dBase.isValid() )
    {
        dBase.close();
        QSqlDatabase::removeDatabase ( dBase.connectionName() );
    }

#ifdef EMBEDDED_MYSQL
    dBase=QSqlDatabase::addDatabase ( "EM_QMYSQL" );
    dBase.setDatabaseName ( "karakaxa" );
#else
    dBase=QSqlDatabase::addDatabase ( "QMYSQL" );
    KSharedConfigPtr config=core::config->configFile ( "database.conf" );
    KConfigGroup group ( config, "database" );
    dBase.setHostName ( "localhost" );
    dBase.setDatabaseName ( group.readEntry ( "database",QString() ) );
    dBase.setUserName ( group.readEntry ( "user",QString() ) );
    dBase.setPassword ( group.readEntry ( "pass",QString() ) );

    qDebug()<<dBase.databaseName()<<" "<<dBase.userName()<<" "<<dBase.password();
    if ( dBase.databaseName().isEmpty() )
    {
        
        return false;
    }

#endif

    if ( !dBase.open() )
    {
        Basic::msg()->error( QObject::tr ( "Can not connect to database" ) );
        Basic::msg()->logErr( "Database Error"+dBase.lastError().text() );
        return false;
    }

    return true;
}

bool database::databaseConection::needSetup()
{
    QSqlQuery q ( dBase );
    q.prepare ( "select dbVersion from karakaxa_info" );

    if ( !q.exec() )
    {
        qDebug() <<q.lastError().text();
        return true;
    }

    return false;
    /*

    bool b;
    int version=q.value(0).toInt(&b);
    if(b==false || version!=DB_VERSION)
    {
        return true;
    }
    return false;
    */
}

void database::databaseConection::setUpDb()
{
    qDebug() <<"updating database tables";
    QString s=KGlobal::dirs()->findResource ( "data",QString ( "karakaxa/sql/create.txt" ) );
    QFile scriptFile ( s );
    QSqlQuery q ( dBase );

    if ( scriptFile.open ( QIODevice::ReadOnly ) )
    {
        QStringList scriptQueries = QTextStream ( &scriptFile ).readAll().split ( ';' );

        foreach ( QString queryTxt, scriptQueries )
        {
            if ( queryTxt.trimmed().isEmpty() )
            {
                continue;
            }

            if ( !q.exec ( queryTxt ) )
            {
                Basic::msg()->error( QObject::tr ( "Could not set up database" ) );
                Basic::msg()->logErr( q.lastError().text() );
                q.finish();
                return ;
            }

            q.finish();

        }
        q.prepare ( QString ( "INSERT INTO karakaxa_info (dbVersion) VALUES (" ) + DB_VERSION + QString ( ")" ) );

        if ( !q.exec() )
        {
            Basic::msg()->error( QObject::tr ( "Could not set up database" ) );
            Basic::msg()->logErr( q.lastError().text() );
        }
    }
}

QSqlDatabase database::databaseConection::getDatabase()
{
    mutex.lock();

    if ( QThread::currentThread() == qApp->thread()  )
    {
        if ( !dBase.isOpen() )
        {
            Basic::msg()->logErr( "database is closed: "+dBase.lastError().text() );
            createConnection();
        }

        mutex.unlock();
        return dBase;
    }
    else
    {
        QString name=apprName ( QThread::currentThread() );

        dBEntry *dbE=dBMap[name];
        QSqlDatabase newDb;

        if ( dbE==0 )
        {
            dbE=new dBEntry;
            dbE->name=name;
            dbE->thr=QThread::currentThread();
            dbE->used=1;
            dBMap[name]=dbE;
            newDb=QSqlDatabase::cloneDatabase ( dBase,name );
        }
        else
        {
            dbE->used++;
            newDb=QSqlDatabase::database ( name,false );
        }

        if ( !newDb.isOpen() )
        {
            if ( !newDb.open() )
            {
                Basic::msg()->logErr( "database error: "+dBase.lastError().text() );
            }
        }

        mutex.unlock();
        return newDb;

    }
}

void database::databaseConection::closeDatabase()
{
    if ( QThread::currentThread() == qApp->thread()  )
    {
        return ;
    }

    QString name=apprName ( QThread::currentThread() );

    mutex.lock();
    dBEntry *dbE=dBMap.value ( name );

    if ( dbE==0 )
    {
        Basic::msg()->logErr( "Can't close a non exist database connection" );
    }
    else
    {
        dbE->used--;

        if ( dbE->used==0 )
        {
            QSqlDatabase dbase=QSqlDatabase::database ( name,false );
            dbase.close();
            dbase=QSqlDatabase();
            QSqlDatabase::removeDatabase ( name );
            dBMap.remove ( name );
            delete dbE;
        }
    }

    mutex.unlock();
}

void database::databaseConection::closeDatabase ( QSqlDatabase &dbase )
{
    mutex.lock();
    QString name=dbase.connectionName();

    if ( name==dBase.connectionName() )
    {
        mutex.unlock();
        return ;
    }

    dBEntry *dbE=dBMap.value ( name );

    if ( dbE==0 )
    {
        Basic::msg()->logErr( "Can't close a non exist database connection" );
    }
    else
    {
        dbE->used--;

        if ( dbE->used==0 )
        {
            dbase.close();
            dbase=QSqlDatabase();
            QSqlDatabase::removeDatabase ( name );
            dBMap.remove ( name );
            delete dbE;
        }
    }

    mutex.unlock();
}

QString database::databaseConection::apprName ( QThread *thr )
{
    return QString::number ( ( long int ) thr );
}

const QString database::databaseConection::error()
{
    return dBase.lastError().text();
}


database::databaseConection::~databaseConection()
{
    if ( dBase.isOpen() )  dBase.close();

    dBase=QSqlDatabase();
    QSqlDatabase::removeDatabase ( dBase.connectionName() );
}

database::dbJobP database::databaseConection::rescan()
{
    rescanJob *sc=new rescanJob ( RESCAN );
    libraryFolder lf;
    sc->setDirs ( lf.libraryFolders() );

    dbJobP p ( sc );
    addJob ( p );

    return p;
}

database::dbJobP database::databaseConection::update()
{
    rescanJob *sc=new rescanJob ( UPDATE );
    libraryFolder lf;
    sc->setDirs ( lf.libraryFolders() );

    dbJobP p ( sc );
    addJob ( p );

    return p;
}


void database::databaseConection::addJob ( database::dbJobP j )
{
    mutex.lock();
    jobs.append ( j );

    if ( currJob.isNull() )
    {
        nextJob();
    }
    else
    {
        mutex.unlock();
    }
}

void database::databaseConection::nextJob()
{
    if ( jobs.size() ==0 || !currJob.isNull() )
    {
        mutex.unlock();
        emit newJob ( dbJobP() );
        return ;
    }

    currJob=jobs.first();
    jobs.removeFirst();
    connect ( currJob.data(),SIGNAL ( finished() ),this,SLOT ( jobFinished() ),Qt::QueuedConnection );
    mutex.unlock();
    currJob->start();
    emit newJob ( currJob );
}

void database::databaseConection::jobFinished()
{
    mutex.lock();
    currJob.clear();
    nextJob();
}

void database::databaseConection::emitUpdated ( audioFiles::audioFile f )
{
    if ( !f.inDataBase() )
    {
        return ;
    }

    if ( editFiles.isNull() )
    {
        dbEventAF *ev=new dbEventAF();
        ev->files.append ( f );
        dbEventP e=dbEventP ( ev );
        emit newEvent ( e );
    }
    else
    {
        dbEventAF *e=static_cast<dbEventAF *> ( editFiles.data() );
        e->files<<f;
    }
}

void database::databaseConection::editMultFilesStart()
{
    editFiles=dbEventP ( new dbEventAF() );
}

void database::databaseConection::editMultFilesStop()
{
    dbEventP e=editFiles;
    editFiles.clear();
    emit newEvent ( e );

}

void database::databaseConection::init()
{
    if ( db==0 )
    {
        databaseConection::db=new databaseConection();
    }
}

database::databaseConection *database::databaseConection::db=0;

