#include"libraryImporter.h"

#include<QWidget>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>

#include<audioFiles.h>
#include<status/playerStatus.h>

#include"database.h"

// using namespace core;
using namespace audioFiles;
// using namespace std;


database::libraryImporter::libraryImporter(QObject *parent)
        :dbBase(parent)
{
    database=db()->getDatabase();

    if (!database.isOpen() )
    {
        core::status->addErrorP("Database Error: "+database.lastError().text() );
        return;
    }  
}

database::albumEntry database::libraryImporter::import(const QString &url)
{
    albumEntry al;
    if(!database.isOpen() )
    {
	   core::status->addErrorP("Database is closed trying to reopen" );
	   if(!database.open() )
	   {
          core::status->addErrorP("Can't open database" );
		  return al;
	   }
    }
    
    audioFile f(url);
    
    QSqlQuery q(database);               

    QVariant *albumArtist;
    QVariant var[FRAME_NUM];
    
    for(int i=0;i<FRAME_NUM;++i)
    {
        var[i]=f.tag(i,audioFile::ONCACHE|audioFile::TITLEFP|audioFile::LOAD_FILE);	
        if(f.error()==NS_TAG)
        {
            var[i]=f.tag((tagsEnum)i,audioFile::ONDATAB|audioFile::SELECT);
        }
    }    
    
    if(!var[LEAD_ARTIST].toString().isEmpty() )
    {
        albumArtist=&(var[LEAD_ARTIST] );
    }
    else
    {
       albumArtist=&(var[ARTIST] );
    }

    qDebug()<<"FR "<< var[FRAME_NUM];
    
    return importToDb(var,albumArtist);
}

database::albumEntry database::libraryImporter::importToDb(QVariant var[],QVariant *albumArtist)
{
    QSqlQuery q(database);
    albumEntry al;
    al.name=var[ALBUM].toString();
    al.artist=var[FRAME_NUM].toString();

    var[ARTIST]=getId(var[ARTIST],artistTable);
    var[LEAD_ARTIST]=getId(var[LEAD_ARTIST],artistTable);
    var[GENRE]=getId(var[GENRE],genreTable);
    var[COMPOSER]=getId(var[COMPOSER],composerTable);
    var[ALBUM]= getAlbumId(var[ALBUM],*albumArtist);

    
    al.id=var[ALBUM].toInt();
    q.prepare("INSERT INTO " +trackTable + " (tracknumber,title,album,artist,lead_artist,comment,genre,composer,length,rating,year,bitrate,path,count)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    for (int i=0;i<FRAME_NUM;i++)
    {
        q.addBindValue( var[i] );
    }

    if (!q.exec() )
    {
        qDebug()<<"Importer error:";
        qDebug()<<q.lastError().text();
        al.artist.clear();        
        al.id=-1;
        al.name.clear();
    }

    return al;
}


bool database::libraryImporter::importPl(const QString &path )
{     
    if(!database.isOpen() )
    {
	   core::status->addErrorP("Database is closed trying to reopen" ); 
	   if(!database.open() )
	   {
		  core::status->addErrorP("Can't open database" );
		  return false;
	   }
    } 
  
    QSqlQuery q(database);
    q.prepare("insert into "+ playlistTable + "(path) values(?)");
    q.addBindValue( path );
    q.exec();

    return true;
}

//int database::libraryImporter::n=0;

QString database::libraryImporter::error()
{
    return database.lastError().text();
}

database::libraryImporter::~libraryImporter()
{
    db()->closeDatabase(database);
}

void database::libraryImporter::saveAlbumArt(const QString &albumArt , const albumEntry &al)
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
    query.prepare("update " + albumTable + " set image = ? where id=?");
    query.addBindValue(albumArt );
    query.addBindValue(al.id);

    if (!query.exec() )
    {
        qDebug()<<"error: can't save album art";
        qDebug()<<query.lastError().text();
    }
}

QVariant database::libraryImporter::getId(QVariant var,QString table)
{
    QSqlQuery q(database);

    qDebug()<<"get id "<<table;
    
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
      qDebug()<<"insert to "+table+" error";
      qDebug()<<q.lastError().text();
    }    
    
    q.prepare(s );
    q.addBindValue(var);
    
    if(!q.exec() )
    {
        qDebug()<<"select from "+table+" error";
        qDebug()<<q.lastError().text();
    }
    q.next();
           
    return q.value(0);    
}

QVariant database::libraryImporter::getAlbumId(QVariant album,QVariant artist)
{
    QSqlQuery q(database);
    QString name=album.toString();
    name=name.trimmed();
    if(name.isEmpty() )
    {
        name=QString(" ");
    }
    album=QVariant(name);
    
    q.prepare("select id from " + albumTable + " where name =? AND artist=?" );
    q.addBindValue(album);
    q.addBindValue(artist);
    
    q.exec();
    
    if(q.next() )
    {
        qDebug()<<"AL "<<q.value(0);
        return q.value(0);
    }
    
    q.prepare("insert into " + albumTable + " (name,artist) values (?,?);");
    q.addBindValue(album);
    q.addBindValue(artist );   

    if(!q.exec() )
    {
        qDebug()<<q.lastError().text();
    }    
    
    q.prepare("select id from " + albumTable + " where name =? AND artist=?" );
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



