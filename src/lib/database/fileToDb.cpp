#include"fileToDb.h"
#include"database.h"
#include<QtDebug>
#include<QFileInfoList>

#include<core.h>


// using namespace player;
using namespace core;

database::fileToDb::fileToDb(QString path) :dbBase()
{
  _path=path;  
}

database::fileToDb::~fileToDb()
{
    db()->closeDatabase(databs);
}


int database::fileToDb::setTag(int t, QVariant var)
{
    using namespace audioFiles;
    tag=t;
    value=var;
    
    int err;  
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
		  err=setAlbum(value.toString());
		  if(err==OK)
		  {
		    _album=value.toString();
		  }
		  break ;
	   }
	   case ARTIST:
	   {
		  err=setArtist(value.toString() );	    
		  if(err==OK)
		  {
		    _artist=value.toString();
		  }
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
	   default:
	   {
		  err=UNOWN;
	   }
    }

    return err;    
}

int database::fileToDb::commit()
{
    return OK;

}

int database::fileToDb::prepare()
{
    databs=db()->getDatabase();
    if (!databs.isOpen())
    {
        return DBERR;
    }    
    
    return OK;
}

int database::fileToDb::end()
{
    return OK;
}



int database::fileToDb::setArtist (const QString &s)
{
    QSqlQuery q(databs );

    q.prepare("CALL get_artist (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't set artist"<< q.lastError();
        return DBERR;

    }
        
    q.prepare( "update tracks SET artist=@i where path=?");
    q.addBindValue(_path);
    if (!q.exec() )
    {
        qDebug()<<"can't set artist"<< q.lastError();
        return DBERR;

    }
             
    if(_leadArtist.trimmed().isEmpty() )
    {
	    q.prepare("select artist from artist_album where id=?");
		q.addBindValue( _albumId );
		if (!q.exec())
		{
		  return DBERR;
		}
		
		if(q.value(0).toString().trimmed().isEmpty() )
		{
		    if (!setAlbumArtist(s,q) )
		    {
			   qDebug()<<"Can't update album artist";
			   return DBERR;
		    }
		    clearAlbum();
		}
    }
    
    clearArtist();

    return OK;
}

int database::fileToDb::setAlbum (const QString &s)
{ 
    QSqlQuery q(databs );

    q.prepare("select artist,image into @j,@k from artist_album where id=?");
    q.addBindValue( _albumId );

    if (!q.exec())
    {
        return DBERR;
    }

    q.prepare("CALL get_album (?,@j,@i) ");
    q.addBindValue( s );

    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }

    q.prepare( "update tracks SET album=@i where path=?");
    q.addBindValue(_path );       
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
         
    q.prepare( "update albums SET image=@k where id=@i");
    q.addBindValue(_path );       
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
    
     
    q.prepare( "select @i");      
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
    
    _albumId=q.value(0).toInt();

    clearAlbum();

    return OK;
}


int database::fileToDb::setGenre (const QString &s)
{
    QSqlQuery q(databs);

    q.prepare("CALL get_genre (?,@i) ");
    q.addBindValue( s );
    if (!q.exec() )
    {
        return DBERR;

    }

    q.prepare( "update tracks SET genre=@i where path=?");
    q.addBindValue(_path );

    if (!q.exec() )
    {
        return DBERR;
    }

    clearGenre();

    return OK;
}

int database::fileToDb::setLeadArtist (const QString &s)
{
    QSqlQuery q(databs );    

    q.prepare("CALL get_artist (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        return DBERR;
    }

    QString albumArtistS;
    if (s.isEmpty() )
    {
        albumArtistS=_artist;
    }
    else
    {
        albumArtistS=s;
    }

    q.prepare( "update tracks SET lead_artist=@i where path=?");
    q.addBindValue(_path);    

    if (!q.exec() )
    {
        qDebug()<<"Can't update album lead artist"<<q.lastError();
        return DBERR;
    }
         
    if (!setAlbumArtist(albumArtistS,q) )
    {
        return DBERR;
    }

    clearAlbum();
    clearArtist();
    
    
    return OK;
}

bool database::fileToDb::setAlbumArtist(const QString &artist,QSqlQuery &q)
{
    q.prepare( "CALL get_album(?,?,@k)");
    q.addBindValue(_album);
    q.addBindValue(artist);
       
    if (!q.exec() )
    {
        qDebug()<<"On setAlbumArtist";
        qDebug()<<"	can't set album artist"<< q.lastError();

        return false;
    }

    q.prepare( "update tracks SET album=@k where path=?");
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"On setAlbumArtist";
        qDebug()<<"	Can't update album lead artist"<<q.lastError();

        return false;
    }
            
    q.prepare("select image into @i from artist_album where id=?");
    q.addBindValue( _albumId );

    if (!q.exec())
    {
        return DBERR;
    }
        
    q.prepare( "update albums SET image=@i where id=@k");        
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
    
     
    q.prepare( "select @k");      
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }
    
    _albumId=q.value(0).toInt();

    clearAlbum();        
    
    return true;
}


int database::fileToDb::setComposer (const QString &s)
{
    QSqlQuery q(databs );

    q.prepare("CALL get_composer (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't call get_composer"<< q.lastError();
        return DBERR;
    }

    q.prepare( "update tracks SET composer=@i where path=?");
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"can't update track"<< q.lastError();
        return DBERR;
    }

    clearComposer();

    return OK;
}


int database::fileToDb::setTitle(const QString &s)
{
    QSqlQuery q(databs);

    q.prepare( "update tracks SET title=? where path=?");
    q.addBindValue(s);
    q.addBindValue(_path );

    if (!q.exec() )
    {
        q.prepare("select title from tracks where path=?");
        q.addBindValue(_path );
        q.exec();
        
	   if( !q.first() )
        {
            qDebug()<<"probably file not exist in library";
            return NOTINDB;
        }
        qDebug()<<"setting title error"<<q.lastError();
        return DBERR;
    }
    return OK;
}

int database::fileToDb::setComment (const QString &s)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET comment=? where path=?");
    q.addBindValue(s);
    q.addBindValue(_path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

int database::fileToDb::setYear (const unsigned int &year)
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
    return OK;
}

int database::fileToDb::setTrack (const unsigned int &track)
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
    return OK;
}

int database::fileToDb::setRating (const unsigned int &rating)
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
    return OK;
}

int database::fileToDb::setCounter(const unsigned int &num )
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
    return OK;
}

QSqlRecord database::fileToDb::record(const QString path,int &err)
{    
    QSqlDatabase databs=db()->getDatabase();

    if (!databs.isOpen() )
    {
         err=DBERR;
         db()->closeDatabase(databs);
         return QSqlRecord();
    }
    
    QSqlRecord r;
    
    {
	 QSqlQuery q(databs );

	 q.prepare("select * from trackView where path=?");
	 q.addBindValue(path);

	 if (!q.exec() )
	 {
		qDebug()<<"getting record error "<<q.lastError().text();
		err=DBERR;

		db()->closeDatabase(databs);
		r=QSqlRecord();
	 }
	 else
	 {
		if(q.first() )
		{		  
		    r=q.record();
		    err=OK;
		}
		else
		{  
		    r=QSqlRecord();
		    err=NOTINDB;
		}
	 }
    }
    
    db()->closeDatabase(databs);

    return r;
}


QString database::fileToDb::albumArt(const int albumId,int &err)
{
    QSqlQuery q(databs);
    q.prepare("select image from albums where id=?");
    q.addBindValue(albumId);

    if (!q.exec() )
    {
        qDebug()<<"getting albumArt error "<<q.lastError().text();
        err=DBERR;
        return QString();
    }

    q.first();
    err=OK;
    return q.value(0).toString();
}

int database::fileToDb::setAlbumArt(const int albumId,QString art)
{
    QSqlQuery q(databs );

    q.prepare("update albums SET image=? where id=?");
    q.addBindValue(art);
    q.addBindValue(albumId);

    if (!q.exec() )
    {
        qDebug()<<"setting albumArt error "<<q.lastError().text();
        return DBERR;
   }

    return OK;
}
