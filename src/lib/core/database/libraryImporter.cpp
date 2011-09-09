#include"libraryImporter.h"
#include<QSqlDatabase>
#include<QWidget>
#include<../files/audioFile.h>
#include <qsqlquery.h>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>
#include<database.h>

// using namespace core;
using namespace audioFiles;
// using namespace std;


core::libraryImporter::libraryImporter()
        :QObject(),
        name("importer")
{
//      connect(this,SIGNAL(error(QString) ),&player::errors,SLOT(setError(QString)),Qt::QueuedConnection);
    database=db->getDatabase();
//     isConnected=database.open();

    if (!database.open() )
    {
        qDebug()<<"Database Error: "<<database.lastError().text();
	   return;
    }
    
    createTmpTable();
    
}

core::albumEntry core::libraryImporter::import(const QString &url)
{
    albumEntry al;
    if(!database.isOpen() )
    {
	   qDebug()<<"Database is closed trying to reopen";
	   if(!database.open() )
	   {
		  qDebug()<<"Can't open database";
		  return al;
	   }
    }
    
    audioFile f(url);
    
    QSqlQuery q(database);               

    QVariant var[FRAME_NUM];
    
    for(int i=TAGS_START;i<=TAGS_END;++i)
    {
	var[i]=f.tag(i,audioFile::ONCACHE|audioFile::TITLEFP|audioFile::LOAD_FILE);
	
	if(f.error()==NS_TAG)
	{
	    var[i]=f.tag((tagsEnum)i,audioFile::ONDATAB|audioFile::SELECT);
	}
    }    
    QVariant *v;
    
    if(!var[LEAD_ARTIST].toString().isEmpty() )
    {
	v=&var[LEAD_ARTIST];
    }
    else
    {
	v=&var[ARTIST];
    }
    
    
    al.name=var[ALBUM].toString();
    al.artist=v->toString();    
    
//     database.transaction(); 
    
    var[ARTIST]=getId(var[ARTIST],"artistsTmp");
    var[LEAD_ARTIST]=getId(var[LEAD_ARTIST],"artistsTmp");
    var[GENRE]=getId(var[GENRE],"genresTmp");
    var[COMPOSER]=getId(var[COMPOSER],"composersTmp");
    var[ALBUM]= getAlbumId(var[ALBUM],*v);
    
    al.id=var[ALBUM].toInt();

    
    q.prepare("INSERT INTO tracksTmp (tracknumber,title,album,artist,lead_artist,comment,genre,composer,length,rating,year,bitrate,path,count)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    for (int i=0;i<FRAME_NUM;i++)
    {
        q.addBindValue( var[i] );

    }

    if (!q.exec() )
    {
        qDebug()<<"Importer error:";
        qDebug()<<q.lastError().text();
    }

//     if (!database.commit() )
//     {
// 	   qDebug()<<"Importer error: can't commit";
//         qDebug()<<q.lastError().text();
//     }
    
    return al;
}

bool core::libraryImporter::importPl(const QString &path )
{
     
    if(!database.isOpen() )
    {
	   qDebug()<<"Database is closed trying to reopen";
	   if(!database.open() )
	   {
		  qDebug()<<"Can't open database";
		  return false;
	   }
    } 
  
    QSqlQuery q(database);
    q.prepare("insert into playlistsTmp (path) values(?)");
    q.addBindValue( path );
    q.exec();
    return true;
}

int core::libraryImporter::n=0;

QString core::libraryImporter::error()
{
    return database.lastError().text();
}

core::libraryImporter::~libraryImporter()
{
    db->closeDatabase(database);
}

void core::libraryImporter::saveAlbumArt(const QString &albumArt , const albumEntry &al)
{     
    if(!database.isOpen() )
    {
	   qDebug()<<"Database is closed trying to reopen";
	   if(!database.open() )
	   {
		  qDebug()<<"Can't open database";
		  return ;
	   }
    }
    
    QSqlQuery query(database);        
    query.prepare("update albumsTmp set image = ? where id=?");       
    query.addBindValue(albumArt );
    query.addBindValue(al.id);

    if (!query.exec() )
    {
	qDebug()<<"error: can't save album art";
	qDebug()<<query.lastError().text();
    }
}

QVariant core::libraryImporter::getId(QVariant var,QString table)
{
    
    
    QSqlQuery q(database);
    
    QString s("select id from %1 where name =?");
    s=s.arg(table);
    
    QString name=var.toString();
    name=name.trimmed();
    if(name.isEmpty() )
    {
	name=QString(" ");
    }
    var=QVariant(name);
    
    q.prepare(s);   
    q.addBindValue(var);
    q.exec();
    
    if(q.next() )      
    {
        return q.value(0);
    }
	
    QString s2("insert into %1 (name) values (? )");	
    s2=s2.arg(table);
        	
    q.prepare(s2);	
    q.addBindValue(var);
	
    if(!q.exec() )	
    {	
      qDebug()<<"insert to "+table+"error";
      qDebug()<<q.lastError().text();
    }    
    
    q.prepare(s );
    q.addBindValue(var);
    
    if(!q.exec() )
    {
	qDebug()<<"select from "+table+"error";
	qDebug()<<q.lastError().text();
    }
    q.next();
           
    return q.value(0);    
}

QVariant core::libraryImporter::getAlbumId(QVariant album,QVariant artist)
{
    QSqlQuery q(database);
    QString name=album.toString();
    name=name.trimmed();
    if(name.isEmpty() )
    {
	name=QString(" ");
    }
    album=QVariant(name);
    
    q.prepare("select id from albumsTmp where name =? AND artist=?" );    
    q.addBindValue(album);
    q.addBindValue(artist);
    
    q.exec();
    
    if(q.next() )
    {
        return q.value(0);
    }
    
    q.prepare("insert into albumsTmp (name,artist) values (?,?);");   
    q.addBindValue(album);
    q.addBindValue(artist );   

    if(!q.exec() )
    {
	qDebug()<<q.lastError().text();
    }    
    
    q.prepare("select id from albumsTmp where name =? AND artist=?" );    
    q.addBindValue(album);
    q.addBindValue(artist);
     
    if(!q.exec() )
    {
	qDebug()<<"Error selecting from albums";
	qDebug()<<q.lastError().text();
    }
    q.next();
           
    return q.value(0);
}

void core::libraryImporter::createTmpTable()
{
    QSqlQuery q(database);
    
    
    q.exec("CREATE  TABLE tracksTmp 	LIKE tracks");
    q.exec("CREATE  TABLE genresTmp 	LIKE genres");
    q.exec("CREATE  TABLE artistsTmp 	LIKE artists");
    q.exec("CREATE  TABLE albumsTmp 	LIKE albums");
    q.exec("CREATE  TABLE composersTmp LIKE composers");    
    q.exec("CREATE  TABLE playlistsTmp LIKE playlists");   
}

void core::libraryImporter::save()
{
    qDebug()<<"Saving new data";
//     database.transaction();
    
    QSqlQuery q(database);
    
    q.exec("delete  from tracks");
    q.exec("delete  from genres");
    q.exec("delete  from albums");
    q.exec("delete  from artists");    
    q.exec("delete  from composers");
    q.exec("delete  from playlists");
    
    if(!q.exec("INSERT INTO artists select * from artistsTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("INSERT INTO genres select * from genresTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("INSERT INTO albums select * from albumsTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("INSERT INTO composers select * from composersTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("INSERT INTO tracks select * from tracksTmp"))
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("INSERT INTO playlists select * from playlistsTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    
    if(!q.exec("drop table artistsTmp") )
    {
	qDebug()<<q.lastError().text();
    }    
    if(!q.exec("drop table genresTmp") )
    {
	qDebug()<<q.lastError().text();
    }
    if(!q.exec("drop table albumsTmp") )
    {
	qDebug()<<q.lastError().text();
    }  
    if(!q.exec("drop table composersTmp") )
    {
	qDebug()<<q.lastError().text();
    }  
    if(!q.exec("drop table tracksTmp") )
    {
	qDebug()<<q.lastError().text();
    }  
    if(!q.exec("drop table playlistsTmp") )
    {
	qDebug()<<q.lastError().text();
    }  
  
        
    
//     if (!database.commit() )
//     {
// 	qDebug()<<"Importer error: can't commit";
//         qDebug()<<q.lastError().text();
//     }
}




