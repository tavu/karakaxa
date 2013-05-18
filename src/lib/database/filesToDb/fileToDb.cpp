#include"fileToDb.h"
#include"database.h"
#include<QtDebug>
#include<QFileInfoList>

#include<tables.h>

#include<core.h>
#include<Basic/tagsTable.h>

// using namespace player;
using namespace core;
using namespace Basic;

database::fileToDb::fileToDb(QString path) :dbBase(),_record(0),_albumArtist(0)
{
    _recordError=NOT_SELECTED;
    _albumArtistError=NOT_SELECTED;
    _path=path;  
}

void database::fileToDb::updateRecord ( const QSqlRecord &r )
{
    if(_record!=0)
    {
        delete _record;
    }
    _record=fromSqlRecord(r);
    if(_record!=0)
    {
        _recordError=OK;
    }
    else
    {
        //actualy the type of the error is not kwnown. We use NOT_SELECTED in order to check later
        _recordError=NOT_SELECTED;
    }

    
    if(_albumArtist!=0)
    {
        if(_albumArtist->albumId!=_record->albumId)
        {
            delete _albumArtist;
            _albumArtist=0;
            _albumArtistError=NOT_SELECTED;
        }
    }
}


database::fileToDb::~fileToDb()
{
}


int database::fileToDb::setTag(int t, QVariant value)
{
    using namespace audioFiles;
    
    int err=_recordError;
    
    if(err!=OK)
    {
        err=select();
        if(err!=OK)
        {
            return err;
        }
    }

    switch (t)
    {
	   case LEAD_ARTIST:
	   {	  
		  err=setLeadArtist(value.toString());
		  break ;
	   }
	   case RATING:
	   {
		  err=setRating(value.toInt() );
		  break ;
	   }
	   case COUNTER:
	   {
		err=setCounter(value.toInt() );
		break ;
	   }
	   case COMPOSER:
	   {
		  err=setComposer(value.toString());	 
		  break ;
	   }
	   case TITLE:
	   {
		  err=setTitle(value.toString() );	  
		  break ;
	   }
	   case ALBUM:
	   {
		  err=setAlbum(value.toString(),_record->artistId);
		  break ;
	   }
	   case ARTIST:
	   {
		  err=setArtist(value.toString() );
		  break ;
	   }
	   case GENRE:
	   {
		  err=setGenre(value.toString() );	    
		  break ;
	   }
	   case COMMENT:
	   {
		  err=setComment(value.toString());	    
		  break ;
	   }
	   case TRACK:
	   {
		  err=setTrack(value.toInt() );	    
		  break ;
	   }
	   case YEAR:
	   {
		  err=setYear(value.toInt() );
		  break ;
	   }
           case ALBUM_ARTIST:
           {
               err=setAlbumArtist(value.toString());
               break;
           }
	   default:
	   {
                err=UNOWN;
	   }
    }

    return err;    
}

QVariant database::fileToDb::tag (int tag,int &err)
{
    err=_recordError;
    if(err!=OK)
    {
        return QVariant();
    }
    QVariant ret;
    switch (tag)
    {
           case LEAD_ARTIST:
           {      
                  ret=QVariant(_record->leadArtist);
                  break ;
           }
           case RATING:
           {
                  ret=QVariant(_record->rating);
                  break ;
           }
           case COUNTER:
           {
                ret=QVariant(_record->count);
                break ;
           }
           case COMPOSER:
           {
                  ret=QVariant(_record->composer);
                  break ;
           }
           case TITLE:
           {
                  ret=QVariant(_record->title);
                  break ;
           }
           case ALBUM:
           {
                  ret=QVariant(_record->album);
                  break ;
           }
           case ARTIST:
           {
                  ret=QVariant(_record->artist);
                  break ;
           }
           case GENRE:
           {
                  ret=QVariant(_record->genre);
                  break ;
           }
           case COMMENT:
           {
                  ret=QVariant(_record->comment);
                  break ;
           }
           case TRACK:
           {
                  ret=QVariant(_record->number);     
                  break ;
           }
           case YEAR:
           {
                  ret=QVariant(_record->year);
                  break ;
           }
           case ALBUM_ARTIST:
           {
                if(_albumArtist==0)
               {
                   ret=QVariant();
               }
               else
               {
                    ret=QVariant(_albumArtist->artist);
               }
               err=_albumArtistError;
               break;
           }
           default:
           {
               ret=QVariant();
               err=UNOWN;
           }
    }
    return ret;
}


int database::fileToDb::prepare()
{
    databs=db()->getDatabase();
    if (!databs.isOpen())
    {
        return DBERR;
    }    
    lock();
    return OK;
}

int database::fileToDb::end()
{
    unlock();
    return OK;
}



int database::fileToDb::setArtist (const QString &s)
{    
    QString artist=s.simplified();
    QVariant v(artist);
    QVariant artistId=getId(v,artistTable);
    if(artistId.isNull() )
    {
        return DBERR;
    }
    QSqlQuery q(databs);    

    q.prepare( "update tracks SET artist=? where path=?");
    q.addBindValue(artistId);
    q.addBindValue(QVariant(_path) );

    if (!q.exec() )
    {
        clearArtist();
        qDebug()<<"can't set artist "<< q.lastError().text();
        return DBERR;
    }
    _record->artist=s.simplified();
    if(_record->leadArtist.trimmed().isEmpty() )
    {
        if (setAlbumArtist(artistId.toInt() )!=OK )
        {
            qDebug()<<"Can't update album artist";
            clearArtist();
            return DBERR;
        }
    }
    clearArtist();
    return OK;
}

int database::fileToDb::selectAlbumArtist()
{
    databs=db()->getDatabase();
    if(_recordError!=OK)
    {
        select();
        if(_recordError!=OK)
        {
            db()->closeDatabase(databs);
            return _recordError;
        }
    }
    
    if(_albumArtist!=0)
    {
        delete _albumArtist;
    }

    QSqlQuery *q=new QSqlQuery(databs);
    q->prepare("select * from artist_album where id=?");
    q->addBindValue(QVariant(_record->albumId) );
    if(!q->exec())
    {
        _albumArtist=0;
        _albumArtistError=DBERR;
        delete q;
        db()->closeDatabase(databs);
        return DBERR;
    }
    
    if(!q->first())
    {
        _albumArtist=0;
        _albumArtistError=NOTINDB;
        delete q;
        db()->closeDatabase(databs);
        return NOTINDB;
    }
    
    _albumArtist=albumArtistFromRecord(q->record());
    if(_albumArtist==0)
    {
        _albumArtistError=DBERR;
    }
    else
    {
        _albumArtistError=OK;
    }
    
    delete q;
    db()->closeDatabase(databs);
    
    return _albumArtistError;
}

int database::fileToDb::setAlbum ( const QString &s, int artistId )
{
    QString album=s.simplified();
    albumArtistRecord *r=getAlbumId2(album,artistId);
    if(r==0)
    {
        return DBERR;
    }
    if(_albumArtist!=0)
    {
        delete _albumArtist;
    }
    
    int err=setAlbum(r->albumId);
    if(err==OK)
    {
        _albumArtist=r;
        _record->artistId=_albumArtist->artistId;
        _record->albumId=_albumArtist->albumId;
        _record->album=album;
    }
    else
    {
        _albumArtist=0;
    }
    _albumArtistError=err;
    
    clearAlbum();
    
    return err;
}

int database::fileToDb::setAlbum ( int albumId,QString albumArt)
{
    QSqlQuery q(databs);
    q.prepare( "update tracks SET album=? where path=?");
    q.addBindValue(QVariant(albumId) );
    q.addBindValue(QVariant(_path) );
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
    
    //TODO update the album art information
    return OK;

}




int database::fileToDb::setGenre (const QString &s)
{
    QSqlQuery q(databs);
    QString genre=s.simplified();
    QVariant v(s);
    
    QVariant id=getId(v,genreTable);

    if (id.isNull() )
    {
        return DBERR;
    }
    
    q.prepare( "update tracks SET genre=? where path=?");
    q.addBindValue(id );
    q.addBindValue(_path );

    if (!q.exec() )
    {
        return DBERR;
    }

    clearGenre();
    _record->genre=genre;

    return OK;
}

int database::fileToDb::setLeadArtist (const QString &s)
{


    return OK;
}

int database::fileToDb::setAlbumArtist(const QString &s)
{    
 return DBERR;    
}

int database::fileToDb::setAlbumArtist (int id )
{
    albumArtistRecord *r=getAlbumId2(_record->album,id);
    if(r==0)
    {
        return DBERR;
    }
    
    int err=setAlbum(r->albumId);
    
    if(_albumArtist!=0)
    {
        delete _albumArtist;
    }
    
    if(err==OK)
    {
        _albumArtist=r;
        _record->artistId=_albumArtist->artistId;
    }
    else
    {
        _albumArtist=0;
    }
    _albumArtistError=err;
    
    clearAlbum();    
    
    return err;
}

database::albumArtistRecord* database::fileToDb::getAlbumId2 ( const QString &album, int artistId )
{
    databs=db()->getDatabase();
    QSqlQuery *q=new QSqlQuery(databs);
    
    QString name=album.simplified();    
    if(name.isEmpty() )
    {
        name=QString(" ");
    }
    QVariant albumV=QVariant(name);
    
    q->prepare("select * from " + albumArtistTable + " where album =? AND artist_id=?" );
    q->addBindValue(albumV);
    q->addBindValue(artistId);
    
    if(!q->exec() )
    {
        qDebug()<<q->lastError().text();
        delete q;
        db()->closeDatabase(databs);
        return 0;
    }
    
    if(q->next() )
    {
        albumArtistRecord *r=albumArtistFromRecord(q->record() );
        delete q;
        db()->closeDatabase(databs);
        return r;
    }
    
    q->prepare("insert into " + albumTable + " (name,artist) values (?,?);");
    q->addBindValue(albumV);
    q->addBindValue(artistId );   

    if(!q->exec() )
    {
        delete q;
        db()->closeDatabase(databs);
        return 0;
    }    
    
    q->prepare("select * from " + albumArtistTable + " where album =? AND artist_id=?" );
    q->addBindValue(albumV);
    q->addBindValue(artistId);
    
    if(!q->exec() || !q->next() )
    {
        qDebug()<<q->lastError().text();
        delete q;
        db()->closeDatabase(databs);
        return 0;
    }
    
    albumArtistRecord *r=albumArtistFromRecord(q->record() );
    delete q;
    db()->closeDatabase(databs);
    
    return r;
}

database::albumArtistRecord *database::fileToDb::albumArtistFromRecord ( const QSqlRecord &r )
{
    albumArtistRecord *albumArtist=new albumArtistRecord;
    if(!r.isEmpty() )
    {
        albumArtist->artist=r.value(0).toString();
        albumArtist->album=r.value(1).toString();
        albumArtist->albumArt=r.value(2).toString();
        albumArtist->albumId=r.value(3).toInt();
        albumArtist->artistId=r.value(4).toInt();
        albumArtist->artistFoto=r.value(5).toString();
    }
    else
    {
        albumArtist->albumId=-1;
        albumArtist->artistId=-1;
    }
    return albumArtist;
}


int database::fileToDb::setComposer (const QString &s)
{

    return OK;
}


int database::fileToDb::setTitle(const QString &s)
{

    
    return OK;
}

int database::fileToDb::setComment (const QString &s)
{

    return OK;
}

int database::fileToDb::setYear (const unsigned int year)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET year=? where path=?");
    q.addBindValue(QVariant(year) );
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    _record->year=year;
    return OK;
}

int database::fileToDb::setTrack (const unsigned int track)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET tracknumber=? where path=?");
    q.addBindValue(QVariant(track) );
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    _record->number=track;
    return OK;
}

int database::fileToDb::setRating (const unsigned int rating)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET rating=? where path=?");
    q.addBindValue(QVariant(rating) );
    q.addBindValue(_path);
    
    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    _record->rating=rating;
    return OK;
}

int database::fileToDb::setCounter(const unsigned int num )
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET count=? where path=?");
    q.addBindValue(QVariant(num) );
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    _record->count=num;
    return OK;
}

int database::fileToDb::select()
{
    _record=record(_path,_recordError);
    return _recordError;
}


database::trackRecord* database::fileToDb::record(const QString &path,int &err)
{        
    QSqlDatabase databs=db()->getDatabase();

    if (!databs.isOpen() )
    {
         err=DBERR;
         db()->closeDatabase(databs);
         return 0;
    }
    
   QSqlQuery *q=new QSqlQuery(databs );

    q->prepare("select * from trackView where path=?");
    q->addBindValue(path);

    if (!q->exec() )
    {
        qDebug()<<"getting record error "<<q->lastError().text();
        err=DBERR;
        delete q;
        db()->closeDatabase(databs);
        return 0;
    }
    
    if(!q->first() )
    {
        err=NOTINDB;
        delete q;
        db()->closeDatabase(databs);
        return 0;
    }
    QSqlRecord r=q->record();
    trackRecord *ret=fromSqlRecord(r);
    err=OK;
    delete q;
    db()->closeDatabase(databs);

    return ret;
}

database::trackRecord* database::fileToDb::fromSqlRecord ( const QSqlRecord &r )
{
    if(r.isEmpty())
    {
        return 0;
    }
    
    trackRecord *ret=new trackRecord();
    ret->artistId=r.value(0).toInt();
    ret->albumId=r.value(1).toInt();
    ret->number=r.value(2).toInt();
    ret->title=r.value(3).toString();
    ret->album=r.value(4).toString();
    ret->artist=r.value(5).toString();
    ret->leadArtist=r.value(6).toString();
    ret->comment=r.value(7).toString();
    ret->genre=r.value(8).toString();
    ret->composer=r.value(9).toString();
    ret->lenght=r.value(10).toInt();
    ret->rating=r.value(11).toInt();
    ret->year=r.value(12).toInt();
    ret->bitrate=r.value(13).toInt();
    ret->path=r.value(14).toString();
    ret->count=r.value(15).toInt();    
    return ret;
}

int database::fileToDb::albumId ( int &err )
{
    err=_recordError;
    if(_record!=0)
        return _record->albumId;
    return -1;
}


QString database::fileToDb::albumArt(int &err)
{
    err=_albumArtistError;
    if(_albumArtist==0)
    {
        return QString();
    }
    return _albumArtist->albumArt;
}

int database::fileToDb::setAlbumArt(const QString &art)
{
    if(_albumArtist==0)
    {
        selectAlbumArtist();
        if(_albumArtistError!=OK)
        {
            return _albumArtistError;
        }
    }
    QSqlQuery q(databs);

    q.prepare("update albums SET image=? where id=?");
    q.addBindValue(art);
    q.addBindValue(_albumArtist->albumId);

    if (!q.exec() )
    {
        qDebug()<<"setting albumArt error "<<q.lastError().text();
        return DBERR;
    }
    
    _albumArtist->albumArt=art;
    return OK;
}
