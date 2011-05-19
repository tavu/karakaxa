#include"database.h"
#include<QApplication>
#include "../status/playerStatus.h"
// #include<player.h>
#include<kconfiggroup.h>
#include"../config/config.h"
#include<ksharedconfig.h>
#include<KGlobal>
#include<KStandardDirs>
core::database::database()
        :QObject()	
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
    q.prepare("source "+s );    
    
    if(!q.exec() )
    {
	status->addError(QObject::tr("Could not set up database") );
	status->addErrorP(q.lastError().text() );
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
    return db;
}


// QSqlQuery core::database::getLibraryFolders()
// {
//      return QSqlQuery("select path from library_folders",db);
// }

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

// bool core::database::isConnected=false;

// QSqlDatabase core::database::db=QSqlDatabase::addDatabase("QMYSQL");


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


QSqlDatabase core::database::clone(const QString &s)
{
    return db.cloneDatabase ( db, s );
}

core::database::~database()
{
    if(db.isOpen())	db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase(db.databaseName() );
}

void core::database::addLibraryFolder(QString s)
{
    QSqlQuery q(db);
    q.prepare("insert into library_folders(path) values(?)");
    q.addBindValue(s);
    q.exec();
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

namespace core
{
    database *db;
};
// int database::DBCHANGED=FRAME_NUM;
