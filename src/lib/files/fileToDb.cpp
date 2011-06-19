#include"fileToDb.h"
#include"../database/database.h"
#include<QtDebug>
#include<QFileInfoList>

#include<core.h>

// using namespace player;
using namespace core;

audioFiles::fileToDb::fileToDb(QString path)
{
  _path=path;
  databs=core::db->getDatabase();
}


audioFiles::fileToDb::~fileToDb()
{
    core::db->closeDatabase(databs);
}


int audioFiles::fileToDb::setTag(int t, QVariant var)
{
    tag=t;
    value=var;
    
    int err;  
    switch (tag)
    {
	case LEAD_ARTIST:
	{	  
	    err=setLeadArtist(_path,value.toString(),_artist,_album);
	    break ;
	}
	case RATING:
	{
	    err=setRating(_path,value.toInt() );
	    break ;
	}
	case COUNTER:
	{
	  err=setCounter(_path,value.toInt() );
	    break ;
	}
	case COMPOSER:
	{
	    err=setComposer(_path,value.toString());	 
	    break ;
	}
	case TITLE:
	{
	    err=setTitle(_path,value.toString() );	  
	    break ;
	}
	case ALBUM:
	{
	    err=setAlbum(_path,value.toString());
	    if(err==OK)
	    {
		_album=value.toString();
	    }
	    break ;
	}
	case ARTIST:
	{
	    err=setArtist(_path,value.toString(),_album );	    
	    if(err==OK)
	    {
		_artist=value.toString();
	    }
	    break ;
	}
	case GENRE:
	{
	    err=setGenre(_path,value.toString() );	    
	    break ;
	}
	case COMMENT:
	{
	    err=setComment(_path,value.toString());	    
	    break ;
	}
	case TRACK:
	{
	    err=setTrack(_path,value.toInt() );	    
	    break ;
	}
	case YEAR:
	{
	    err=setYear(_path,value.toInt() );
	    break ;
	}
	default:
	{
	    err=UNOWN;
	}
    }

    return err;
    
}

int audioFiles::fileToDb::commit()
{
    if (!databs.commit() )
    {
        qDebug()<<"Seting genre error: "<<databs.lastError().text();
        return DBERR;
    }
    return OK;

}

int fileToDb::prepare()
{
    if (!databs.open() )
    {
        return DBERR;
    }
    
    databs.transaction();
    
    return OK;
}


int audioFiles::fileToDb::setArtist (const QString path,const QString &s,const QString &album)
{
    QSqlQuery q(databs );
    q.prepare("select artist,lead_artist,album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        return NOTINDB;
    }

    int artistId=q.value(0).toInt();
    int LartistId=q.value(1).toInt();
    int albumId=q.value(2).toInt();
    int nullArtistId=-1;
    q.prepare("CALL get_artist (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't set artist"<< q.lastError();
        return DBERR;

    }
        
    q.prepare( "update tracks SET artist=@i where path=?");
    q.addBindValue(path);
    if (!q.exec() )
    {
        qDebug()<<"can't set artist"<< q.lastError();
        return DBERR;

    }
        
    q.prepare( "select id from leadArtists where name='' ");
    q.exec();
    q.next();
    if(q.isValid())
    {
	nullArtistId=q.value(0).toInt();
    }
    
    if(nullArtistId==LartistId)
    {
        if (!setAlbumArtist(path,s,album,q) )
        {
            qDebug()<<"Can't update album artist";
            return DBERR;
        }
        q.prepare("delete from albums where id=?");
        q.addBindValue( albumId );
        q.exec();

    }

    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from artists where id=?");
    q.addBindValue( artistId );
    q.exec();

    return OK;
}

int audioFiles::fileToDb::setAlbum (const QString path,const QString &s)
{ 
    QSqlQuery q(databs );
    q.prepare("select album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        return DBERR;
    }

    int albumId=q.value(0).toInt();

    q.prepare("select artist into @j from artist_album where id=?");
    q.addBindValue( albumId );

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
    q.addBindValue(path );       
    
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();
        return DBERR;
    }

    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from albums where id=?");
    q.addBindValue( albumId );
    q.exec();

    return OK;
}


int audioFiles::fileToDb::setGenre (const QString path,const QString &s)
{
    QSqlQuery q(databs );
    q.prepare("select genre from tracks where path=?");
    q.addBindValue(path);
    q.exec();
    q.next();

    if (!q.isValid())
    {
        return NOTINDB;
    }

    int albumId=q.value(0).toInt();

    q.prepare("CALL get_genre (?,@i) ");
    q.addBindValue( s );
    if (!q.exec() )
    {
        return DBERR;

    }

    q.prepare( "update tracks SET genre=@i where path=?");
    q.addBindValue(path );

    if (!q.exec() )
    {
        return DBERR;
    }

    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from genres where id=?");
    q.addBindValue( albumId );
    q.exec();

    return OK;
}

int audioFiles::fileToDb::setLeadArtist (const QString path,const QString &s,const QString &artist,const QString &album)
{
    QSqlQuery q(databs );
    q.prepare("select lead_artist,album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        return NOTINDB;
    }

    int LartistId=q.value(0).toInt();
    int albumId=q.value(1).toInt();

    q.prepare("CALL get_artist (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        return DBERR;
    }

    QString k;
    if (s.isEmpty() )
    {
        k=artist;
    }
    else
    {
        k=s;
    }

    if (!setAlbumArtist(path,k,album,q) )
    {
        return DBERR;
    }
    q.prepare("delete from albums where id=?");
    q.addBindValue( albumId );
    q.exec();

    q.prepare( "update tracks SET lead_artist=@i where path=?");
    q.addBindValue(path);


    if (!q.exec() )
    {
        qDebug()<<"Can't update album lead artist"<<q.lastError();
        return DBERR;
    }


    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from artists where id=?");
    q.addBindValue( LartistId );
    q.exec();

    return OK;
}

int audioFiles::fileToDb::setComposer (const QString path,const QString &s)
{
    QSqlQuery q(databs );
    q.prepare("select composer from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }

    int composerId=q.value(0).toInt();

    q.prepare("CALL get_composer (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't call get_composer"<< q.lastError();
        return DBERR;
    }

    q.prepare( "update tracks SET composer=@i where path=?");
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"can't update track"<< q.lastError();
        return DBERR;
    }

    //if there are more thracks with that composer the databs will cansel the delete
    q.prepare("delete from composers where id=?");
    q.addBindValue( composerId );
    q.exec();

    return OK;
}

bool audioFiles::fileToDb::setAlbumArtist(const QString &path,const QString &s,const QString &album,QSqlQuery &q)
{
    q.prepare( "CALL get_album(?,?,@k)");
    q.addBindValue(album);
    q.addBindValue(s);

    if (!q.exec() )
    {
        qDebug()<<"On setAlbumArtist";
        qDebug()<<"	can't set lead artist"<< q.lastError();

        return false;
    }
    q.exec("select @k");
    q.next();
//     qDebug()<<q.value(0);

    q.prepare( "update tracks SET album=@k where path=?");
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"On setAlbumArtist";
        qDebug()<<"	Can't update album lead artist"<<q.lastError();

        return false;
    }
    return true;
}


int audioFiles::fileToDb::setTitle(const QString path,const QString &s)
{
    QSqlQuery q(databs );

    q.prepare( "update tracks SET title=? where path=?");
    q.addBindValue(s);
    q.addBindValue(path );

    if (!q.exec() )
    {
        q.prepare("select title from tracks where path=?");
        q.addBindValue(path );
        q.exec();
        q.next();

        if (!q.isValid())
        {
            qDebug()<<"probably file not exist in library";
            return NOTINDB;
        }
        qDebug()<<"setting title error"<<q.lastError();
        return DBERR;
    }
    return OK;
}

int audioFiles::fileToDb::setComment (const QString path,const QString &s)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET comment=? where path=?");
    q.addBindValue(s);
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

int audioFiles::fileToDb::setYear (const QString path, const unsigned int &year)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET year=? where path=?");
    q.addBindValue(QVariant(year) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

int audioFiles::fileToDb::setTrack (const QString path,const unsigned int &track)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET tracknumber=? where path=?");
    q.addBindValue(QVariant(track) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

int audioFiles::fileToDb::setRating (const QString path,const unsigned int &rating)
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET rating=? where path=?");
    q.addBindValue(QVariant(rating) );
    q.addBindValue(path);

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

int audioFiles::fileToDb::setCounter(const QString path,const unsigned int &num )
{
    QSqlQuery q(databs );
    q.prepare( "update tracks SET count=? where path=?");
    q.addBindValue(QVariant(num) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        return NOTINDB;
    }
    return OK;
}

QSqlRecord audioFiles::fileToDb::record(const QString path,int &err)
{    
    QSqlDatabase databs=db->getDatabase();

    if (!databs.open() )
    {
         err=DBERR;
	 core::db->closeDatabase(databs);
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

	    core::db->closeDatabase(databs);
 	    r=QSqlRecord();
	}
	else
	{	
	    q.next();
	    r=q.record();

	    if (r.isEmpty() ||q.value(PATH).isNull() )
	    {
		err=NOTINDB;
		r=QSqlRecord();
	    }
	    else
	    {
		err=OK;
	    }
	}
    }
    
    core::db->closeDatabase(databs);

    return r;
}

QString audioFiles::fileToDb::albumArt(const int albumId,int &err)
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

    q.next();
    err=OK;
    return q.value(0).toString();
}

int audioFiles::fileToDb::setAlbumArt(const int albumId,QString art)
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
