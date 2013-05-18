#include"dbBase.h"
#include<QSqlQuery>
#include<QSqlError>

#include<status/playerStatus.h>
#include"database.h"
#include<QDebug>
void database::dbBase::cleanUp()
{
    clearAlbum();
    clearArtist();
    clearGenre();
    clearComposer();

}


void database::dbBase::clearArtist()
{
     QSqlQuery q(databs );

     q.prepare("delete from artists where artists.id not in (select tracks.lead_artist from tracks) and artists.id not in (select tracks.artist from tracks) and artists.id not in (select albums.artist from albums)");

     if (!q.exec() )
     {
        core::status->addErrorP(q.lastError().text() );
     }
}

void database::dbBase::clearAlbum()
{
     QSqlQuery q(databs );

     q.prepare("delete from albums where albums.id not in (select tracks.album from tracks)");

     if (!q.exec() )
     {
        core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::clearGenre()
{
     QSqlQuery q(databs );

     q.prepare("delete from genres where genres.id not in (select tracks.genre from tracks)");

     if (!q.exec() )
     {
       core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::clearComposer()
{
     QSqlQuery q(databs );

     q.prepare("delete from composers where composers.id not in (select tracks.composer from tracks)");

     if (!q.exec() )
     {
        core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::getDb()
{
	databs=db()->getDatabase();
}
		
void database::dbBase::closeDb()
{
	db()->closeDatabase(databs);
}

QVariant database::dbBase::getId(QVariant &var,const QString &table, bool *inserted)
{
    QSqlQuery q(databs);    
    if(inserted!=0)
    {
        *inserted=false;
    }
    QString s("select id from %1 where name =?");
    s=s.arg(table);
    QString name=var.toString();
    name=name.simplified();
    if(name.isEmpty() )
    {
        name=QString(" ");
    }
    
    var=QVariant(name);
    
    q.prepare(s);
    q.addBindValue(var);
    if(!q.exec() )
    {
        return QVariant();
    }
    
    if(q.first() )      
    {
        return q.value(0);
    }
    q.finish();
        
    QString s2("insert into %1 (name) values (? )");    
    s2=s2.arg(table);
    
    QVariant id=q.lastInsertId();
    q.finish();
    
    if(!id.isValid() )
    {
        q.prepare(s2);
        q.addBindValue(var);
            
        if(!q.exec() )      
        {   
            qDebug()<<q.lastError().text();
            return QVariant();
        }    
        q.finish();
        q.prepare(s );
        q.addBindValue(var);
        
        if(!q.exec() || !q.first() )
        {
            qDebug()<<q.lastError().text();
            return QVariant();
        }
        id=q.value(0);
    }
    
    if(inserted!=0)
    {
        *inserted=true;
    }
    return q.value(0);    
}

QVariant database::dbBase::getAlbumId(QVariant &album,int artistId,const QString &table, bool *b)
{
    QSqlQuery q(databs);
    QString name=album.toString();
    name=name.simplified();
    if(name.isEmpty() )
    {
        name=QString(" ");
    }
    album=QVariant(name);
    
    q.prepare("select id from " + table + " where name =? AND artist=?" );
    q.addBindValue(album);
    q.addBindValue(artistId);
    
    if(!q.exec() )
    {
        qDebug()<<q.lastError().text();
        return QVariant();
    }
    
    if(q.next() )
    {
        return q.value(0);
    }
    
    q.prepare("insert into " + table + " (name,artist) values (?,?);");
    q.addBindValue(album);
    q.addBindValue(artistId );   

    if(!q.exec() )
    {
        qDebug()<<q.lastError().text();
        return QVariant();
    }    
    
    q.prepare("select id from " + table + " where name =? AND artist=?" );
    q.addBindValue(album);
    q.addBindValue(artistId);
     
    if(!q.exec() )
    {
        qDebug()<<q.lastError().text();
        return QVariant();
    }
    
    if(!q.next() )
    {
        qDebug()<<"database error at the insertion of album";
        return QVariant();
    }

    return q.value(0);
}


QMutex database::dbBase::mutex;