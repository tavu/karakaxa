#include <stdlib.h>
#include<QApplication>
#include<kconfiggroup.h>
#include<ksharedconfig.h>
#include<KGlobal>
#include<KStandardDirs>
#include <QProcess>
#include<QDebug>

#include<func.h>
#include<config/config.h>
#include<status/playerStatus.h>
#include<audioFiles.h>

#include"database.h"
#include"editMultFiles.h"
#include"dbJobs/rescanJob.h"
#include"libraryFolder.h"




database::databaseConection::databaseConection()
        :QObject(),
        _state(NORMAL)
{
//     using namespace audioFiles
    dBase=QSqlDatabase::addDatabase("QMYSQL");
    connect(audioFiles::self(),SIGNAL(changed(audioFiles::audioFile)),this,SLOT(emitUpdated(audioFiles::audioFile)) );
    connect(editMultFiles::self(),SIGNAL(started()),this,SLOT(editMultFilesStart() ) );
    connect(editMultFiles::self(),SIGNAL(finished()),this,SLOT(editMultFilesStop()) );
    readSettings();
}

bool database::databaseConection::createConnection()
{

    if(dbName.isEmpty())
    {
        return false;
    }

    dBase.setHostName("localhost");
    dBase.setDatabaseName(dbName);
    dBase.setUserName(dbUser);
    dBase.setPassword(dbPass);

    if (!dBase.open())
    {

	   core::status->addError(QObject::tr("Can not connect to database") );
	   core::status->addErrorP("Database Error"+dBase.lastError().text());
       return false;
    }

    core::status->addInfo(QObject::tr("Connected to database") );
    return true;
}

bool database::databaseConection::dBConnect(QString n,QString u,QString p)
{
    dbName=n;
    dbUser=u;
    dbPass=p;
    bool k=createConnection();
    emit(changed() );
    writeSettings();
    return k;
}


void database::databaseConection::readSettings()
{
     KSharedConfigPtr config=core::config->configFile("database");
     KConfigGroup group( config, "database" );
     dbName=group.readEntry("database",QString());
     dbUser=group.readEntry("user",QString());
     dbPass=group.readEntry("pass",QString());
}

void database::databaseConection::setUpDb()
{
    QSqlQuery q(dBase);
    QString s=KGlobal::dirs()->findResource("data",QString("karakaxa/sql/create.txt") );

    QString command("mysql "+dbName+" -u "+dbUser+" -p"+dbPass+" < "+s);
    int stat=system(command.toStdString().c_str() );
    core::status->addInfoP("setting up the database");
    core::status->addInfoP("exec: "+command);
    core::status->addInfoP("exit status "+QString::number(stat) );

    if(stat!=0)
    {
        core::status->addError(QObject::tr("Could not set up database") );
    }
}


void database::databaseConection::writeSettings()
{

    KSharedConfigPtr config=core::config->configFile("database");
    KConfigGroup group( config, "database" );
    group.writeEntry("database",QVariant(dbName) );
    group.writeEntry("user",QVariant(dbUser));
    group.writeEntry("pass",QVariant(dbPass) );
    group.config()->sync();

}

QSqlDatabase database::databaseConection::getDatabase()
{
    mutex.lock();
    if(QThread::currentThread()==core::mainThr() )
    {
        if(!dBase.isOpen() )
        {
            core::status->addErrorP("database is closed: "+dBase.lastError().text() );
            createConnection();
        }
        mutex.unlock();
        return dBase;
    }
    else
    {
        QString name=apprName(QThread::currentThread() );

        dBEntry* dbE=dBMap[name];
        QSqlDatabase newDb;
        if(dbE==0)
        {
            dbE=new dBEntry;
            dbE->name=name;
            dbE->thr=QThread::currentThread();
            dbE->used=1;
            dBMap[name]=dbE;
            newDb=QSqlDatabase::cloneDatabase(dBase,name);
        }
        else
        {
            dbE->used++;
            newDb=QSqlDatabase::database(name,false);
        }

        if(!newDb.isOpen() )
        {
            if(!newDb.open() )
            {
                core::status->addErrorP("database error: "+dBase.lastError().text() );
            }
	}
	mutex.unlock();
	return newDb;

    }
}

void database::databaseConection::closeDatabase()
{
    if(QThread::currentThread()==core::mainThr() )
    {
        return ;
    }

    QString name=apprName(QThread::currentThread() );

    mutex.lock();
    dBEntry* dbE=dBMap.value(name);

    if(dbE==0)
    {
        core::status->addErrorP("Can't close a non exist database connection");
    }
    else
    {
        dbE->used--;
        if(dbE->used==0)
        {
            QSqlDatabase dbase=QSqlDatabase::database(name,false);
            dbase.close();
            dbase=QSqlDatabase();
            QSqlDatabase::removeDatabase(name);
            dBMap.remove(name);
            delete dbE;
        }
    }
    mutex.unlock();
}

void database::databaseConection::closeDatabase(QSqlDatabase &dbase)
{
    mutex.lock();
    QString name=dbase.connectionName();
    if(name==dBase.connectionName() )
    {
        mutex.unlock();
        return ;
    }

    dBEntry* dbE=dBMap.value(name);

    if(dbE==0)
    {
        core::status->addErrorP("Can't close a non exist database connection");
    }
    else
    {
	dbE->used--;
	if(dbE->used==0)
	{
 	    dbase.close();
	    dbase=QSqlDatabase();
	    QSqlDatabase::removeDatabase(name);
	    dBMap.remove(name);
 	    delete dbE;
	}
    }

    mutex.unlock();
}

QString database::databaseConection::apprName(QThread *thr)
{
    return QString::number((long int) thr);
}

const QString database::databaseConection::error()
{
    return dBase.lastError().text();
}


database::databaseConection::~databaseConection()
{
    if(dBase.isOpen())	dBase.close();
    dBase=QSqlDatabase();
    QSqlDatabase::removeDatabase(dBase.databaseName() );
}

database::dbJobP database::databaseConection::rescan()
{
    rescanJob *sc=new rescanJob(RESCAN);
    libraryFolder lf;
    sc->setDirs(lf.libraryFolders());

    dbJobP p(sc);
    addJob(p);

    return p;
}

database::dbJobP database::databaseConection::update()
{
    rescanJob *sc=new rescanJob(UPDATE);
    libraryFolder lf;
    sc->setDirs(lf.libraryFolders());

    dbJobP p(sc);
    addJob(p);

    return p;
}


void database::databaseConection::addJob(database::dbJobP j)
{
    mutex.lock();
    jobs.append(j);
    if(currJob.isNull())
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
    if(jobs.size()==0 || !currJob.isNull())
    {
        mutex.unlock();
        emit newJob(dbJobP() );
        return ;
    }
    currJob=jobs.first();
    jobs.removeFirst();
    connect(currJob.data(),SIGNAL(finished()),this,SLOT(jobFinished()),Qt::QueuedConnection);
    mutex.unlock();
    currJob->start();
    emit newJob(currJob );
}

void database::databaseConection::jobFinished()
{
    mutex.lock();
    currJob.clear();
    nextJob();
}

void database::databaseConection::emitUpdated(audioFiles::audioFile f)
{
    if(!f.inDataBase() )
    {
        return ;
    }
    if(editFiles.isNull() )
    {
        dbEventAF *ev=new dbEventAF();
        ev->files.append(f);
        dbEventP e=dbEventP(ev);
        emit newEvent(e);
    }
    else
    {
        dbEventAF *e=static_cast<dbEventAF*>(editFiles.data() );
        e->files<<f;
    }
}

void database::databaseConection::editMultFilesStart()
{
        editFiles=dbEventP( new dbEventAF() );
}

void database::databaseConection::editMultFilesStop()
{
    dbEventP e=editFiles;
    editFiles.clear();
    emit newEvent(e);

}

void database::databaseConection::init()
{
    if(db==0)
    {
        databaseConection::db=new databaseConection();
        databaseConection::db->createConnection();
    }
}

database::databaseConection* database::databaseConection::db=0;

