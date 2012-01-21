#include"database.h"
#include<QApplication>
#include "../status/playerStatus.h"
#include<kconfiggroup.h>
#include"../config/config.h"
#include<ksharedconfig.h>
#include<KGlobal>
#include<KStandardDirs>
#include<QThread>
#include"../func.h"
#include"../status/playerStatus.h"
#include"databaseScanner.h"
 #include <QProcess>

core::database::database()
        :QObject(),
        _state(NORMAL)
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    readSettings();    
}

bool core::database::createConnection()
{
    
    if(dbName.isEmpty())
    {
        return false;
    }
    
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    db.setPassword(dbPass);

    if (!db.open())
    {

	   status->addError(QObject::tr("Can not connect to database") );
	   status->addErrorP("Database Error"+db.lastError().text());
       return false;
    }
    
    status->addInfo(QObject::tr("Connected to database") );
    return true;
}

bool core::database::dBConnect(QString n,QString u,QString p)
{
    dbName=n;
    dbUser=u;
    dbPass=p;
    bool k=createConnection();
    emit(changed() );
    writeSettings();
    return k;
}


void core::database::readSettings()
{
     KSharedConfigPtr config=core::config->configFile("database");
     KConfigGroup group( config, "database" );
     dbName=group.readEntry("database",QString());
     dbUser=group.readEntry("user",QString());
     dbPass=group.readEntry("pass",QString());    
}

void core::database::setUpDb()
{
    QSqlQuery q(db);
    QString s=KGlobal::dirs()->findResource("data",QString("player/sql/create.txt") );   

    QString command("mysql "+dbName+" -u "+dbUser+" -p"+dbPass+" < "+s);
    int stat=system(command.toStdString().c_str() );
    status->addInfoP("setting up the database");
    status->addInfoP("exec: "+command);
    status->addInfoP("exit status "+QString::number(stat) );

    if(stat!=0)
    {
        status->addError(QObject::tr("Could not set up database") );
    }
}


void core::database::writeSettings()
{

    KSharedConfigPtr config=core::config->configFile("database");
    KConfigGroup group( config, "database" );
    group.writeEntry("database",QVariant(dbName) );
    group.writeEntry("user",QVariant(dbUser));
    group.writeEntry("pass",QVariant(dbPass) );
    group.config()->sync(); 
  
}

QSqlDatabase core::database::getDatabase()
{
    mutex.lock();
    if(QThread::currentThread()==core::mainThr() )
    {
        if(!db.isOpen() )
        {
            status->addErrorP("database is closed: "+db.lastError().text() );
            createConnection();
        }
        mutex.unlock();
        return db;
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
            newDb=QSqlDatabase::cloneDatabase(db,name);
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
                status->addErrorP("database error: "+db.lastError().text() );
            }
	}
	mutex.unlock();	
	return newDb;
	
    }
}

void core::database::closeDatabase()
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
	    
	    qDebug()<<"close "<<name;
	}
    }	 
    mutex.unlock();    
}

void core::database::closeDatabase(QSqlDatabase &dbase)
{   
    mutex.lock();    
    QString name=dbase.connectionName();    
    if(name==db.connectionName() )
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


QString core::database::apprName(QThread *thr)
{
    return QString::number((long int) thr);
}

QStringList core::database::getLibraryFolders()
{
    QSqlQuery q("select path from library_folders",db);
    QStringList l;

    q.exec();

    while (q.next() )
    {
        l<<q.value(0).toString();
    }
    return l;
}


const QString core::database::error()
{
    return db.lastError().text();
}

void core::database::toSqlSafe(QString &s)
{
    s.replace('\\',"\\\\");
    s.replace('\'',"\\\'");
    s.replace('\"',"\\\"");
//      s.replace('%',"\'");
}

const QString core::database::trackTable()
{
    return QString("trackView");
}

core::database::~database()
{
    if(db.isOpen())	db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase(db.databaseName() );
}

void core::database::addLibraryFolder(QString s)
{
    QSqlQuery q(getDatabase() );
    QStringList l=getLibraryFolders();

    KUrl newU(s);
    
    foreach(QString s,l)
    {
        KUrl u(s);        
        if(u.isParentOf(newU) )
        {
            //we do not need to add the newU as library folder
            closeDatabase();
            status->addInfo(tr("Some library folders have been merged") );
            return ;
        }
        if(newU.isParentOf(u) )
        {
            //we do not need the u any more
            removeLibraryFolder(s);
            status->addInfo(tr("Some library folders have been merged") );
        }
    }

    q.prepare("insert into library_folders(path) values(?)");
    q.addBindValue(s);
    q.exec();
    closeDatabase();
}

void core::database::removeLibraryFolder(QString s)
{
    QSqlQuery q(db);
    q.prepare("delete from library_folders where path=?");
    q.addBindValue(s);
    q.exec();
}

QSqlQuery core::database::playlists()
{
  QSqlQuery q("select * from playlists",db);
  return q;
}

void core::database::scan(core::databaseScanner* sc)
{
    mutex.lock();    
    scanners.append(dbScanner(sc) );
    connect(sc,SIGNAL(finished()),this,SLOT(scanFinished()),Qt::QueuedConnection);

    if(_state==NORMAL)
    {
        nextState();        
    }
    else
    {
        mutex.unlock();
    }

}

void core::database::scanFinished()
{
    mutex.lock();
    scanners.removeFirst();
    nextState();
}

void core::database::nextState()
{
    dbState oldState=_state;
    if(scanners.isEmpty() )
    {
        _state=NORMAL;
        mutex.unlock();
        emit stateCanged(oldState,_state);
    }
    else
    {
        _state=scanners.first()->type();
        mutex.unlock();
        emit stateCanged(oldState,_state);
        scanners.first()->startScan();
    }
}


namespace core
{
    database *db;
};


