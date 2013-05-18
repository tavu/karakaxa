#include"trackRecord.h"
#include"albumRecord.h"
#include"artistRecord.h"
#include<Basic/tagsTable.h>
#include"columnEntry.h"
#include<QDebug>
database::dbPrivate::trackRecord::trackRecord ( QString p ):baseRecord(QString("tracks") )
{
    setTable("tracks");
    columnEntry *path=new columnEntry("path","varchar(255)",true);
    path->setNotNull(true);  
    path->setAllowValueChanges(false);
    path->setValue(p);
    addEntry(Basic::PATH,path);    
    
//     qDebug()<<path->value();
    
    entry *title=new columnEntry("title","varchar(255)");
    addEntry(Basic::TITLE,title);
    
    entry *comment=new columnEntry("comment","text");
    addEntry(Basic::COMMENT,comment);
    
    entry *lyrics=new columnEntry("lyrics","text");
    addEntry(Basic::LYRICS,lyrics);
    
    entry *number=new columnEntry("tracknumber","int");
    addEntry(Basic::TRACK,number);
    
    entry *artist=new artistRecord();
    artist->setName("artist");
    addEntry(Basic::ARTIST,artist);
    
    entry *leadArtist=new artistRecord();
    leadArtist->setName("lead_artist");
    addEntry(Basic::LEAD_ARTIST,leadArtist);
    
    entry *album=new albumRecord();
    album->setName("album");
    addEntry(Basic::ALBUM,album);

    entry *genre=new simpleRecord(Basic::GENRE);
    genre->setName("genre");
    addEntry(Basic::GENRE,genre);
    
    entry *composer=new simpleRecord(Basic::COMPOSER);
    composer->setName("composer");
    addEntry(Basic::COMPOSER,composer);

    entry *year=new columnEntry("year","int");
    addEntry(Basic::YEAR,year);
    
    entry *length=new columnEntry("length","int" );
    addEntry(Basic::LENGTH,length);
    
    entry *rating=new columnEntry("rating","SMALLINT" );
    addEntry(Basic::RATING,rating);
    
    entry *bitrate=new columnEntry("bitrate","SMALLINT" );
    addEntry(Basic::BITRATE,bitrate);
    
    entry *count=new columnEntry("count","int" );
    addEntry(Basic::COUNTER,count);
}

int database::dbPrivate::trackRecord::save()
{
    doSave();
    if(entries[Basic::GENRE]->hasChanged() )
    {
        clearGenre();
    }
    
    if(entries[Basic::COMPOSER]->hasChanged())
    {
        clearComposer();
    }
    
    if(entries[Basic::ALBUM]->hasChanged() )
    {
        clearAlbum();
        clearArtist();
    }
    else if(entries[Basic::ARTIST]->hasChanged() ||entries[Basic::LEAD_ARTIST]->hasChanged() )
    {
        clearArtist();
    }
        
    saveDataLocaly();
    saveValue();
    
    if(lastError().isValid() )
    {
        return Basic::DBERR;
    }
    return Basic::OK;
}


void  database::dbPrivate::trackRecord::clearArtist()
{
     QSqlQuery q(databs );

     q.prepare("delete from artists where artists.id not in (select tracks.lead_artist from tracks) and artists.id not in (select tracks.artist from tracks) and artists.id not in (select albums.artist from albums)");

     if (!q.exec() )
     {
        setError(q.lastError());
     }
}

void  database::dbPrivate::trackRecord::clearAlbum()
{
     QSqlQuery q(databs );

     q.prepare("delete from albums where albums.id not in (select tracks.album from tracks)");

     if (!q.exec() )
     {
        setError(q.lastError());
     }
}

void  database::dbPrivate::trackRecord::clearGenre()
{
     QSqlQuery q(databs );

     q.prepare("delete from genres where genres.id not in (select tracks.genre from tracks)");

     if (!q.exec() )
     {
       setError(q.lastError());
     }
}

void  database::dbPrivate::trackRecord::clearComposer()
{
     QSqlQuery q(databs );

     q.prepare("delete from composers where composers.id not in (select tracks.composer from tracks)");

     if (!q.exec() )
     {
        setError(q.lastError());
     }
}
