#include"fileToDb.h"
#include<QtDebug>
#include<QFileInfoList>

#include<player.h>

using namespace player;

const int fileToDb::OK=0;
const int fileToDb::DBERR=1;
const int fileToDb::NOTINDB=2;


int player::fileToDb::setArtist (const QString path,const QString &s,const QString &album)
{

    QSqlDatabase databs;

    databs=player::db.clone(path);
    if (!databs.open() )
    {
        return DBERR;
    }

    databs.transaction();

    QSqlQuery q(databs );
    q.prepare("select artist,lead_artist,album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
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
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path);
        return DBERR;

    }
        
    q.prepare( "update tracks SET artist=@i where path=?");
    q.addBindValue(path);
    if (!q.exec() )
    {
        qDebug()<<"can't set artist"<< q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path);
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
            databs.close();
            databs=QSqlDatabase();
            QSqlDatabase::removeDatabase(path );
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


    if (!databs.commit() )
    {
        qDebug()<<"Seting artist error: "<<databs.lastError().text();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );

    return OK;
}

int player::fileToDb::setAlbum (const QString path,const QString &s)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);

    if (!databs.open() )
    {
        return DBERR;
    }


    databs.transaction();

    QSqlQuery q(databs );
    q.prepare("select album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
// 	  q.clear();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;
    }

    int albumId=q.value(0).toInt();

    q.prepare("select artist into @j from artist_album where id=?");
    q.addBindValue( albumId );

    if (!q.exec())
    {
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;
    }

    q.prepare("CALL get_album (?,@j,@i) ");
    q.addBindValue( s );
//      q.addBindValue( artistId );


    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;
    }

    q.prepare( "update tracks SET album=@i where path=?");

    q.addBindValue(path );       
    if (!q.exec())
    {
        qDebug()<<"Setting album error: "<<databs.lastError().text();

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;
    }

    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from albums where id=?");
    q.addBindValue( albumId );
    q.exec();

    if (!databs.commit() )
    {
        qDebug()<<"Seting album error: "<<databs.lastError().text();

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );


    return OK;
}


int player::fileToDb::setGenre (const QString path,const QString &s)
{

    QSqlDatabase databs;
    databs=player::db.clone(path);

    if (!databs.open() )
    {
        return DBERR;
    }

    databs.transaction();

    QSqlQuery q(databs );
    q.prepare("select genre from tracks where path=?");
    q.addBindValue(path);
    q.exec();
    q.next();

    if (!q.isValid())
    {
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path);
        return NOTINDB;
    }

    int albumId=q.value(0).toInt();

    q.prepare("CALL get_genre (?,@i) ");
    q.addBindValue( s );
    if (!q.exec() )
    {
        qDebug()<<"can't set genre"<< q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return DBERR;

    }

    q.prepare( "update tracks SET genre=@i where path=?");
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"Seting album error: "<<databs.lastError().text();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }

    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from genres where id=?");
    q.addBindValue( albumId );
    q.exec();


    if (!databs.commit() )
    {
        qDebug()<<"Seting genre error: "<<databs.lastError().text();

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );
    return OK;
}

int player::fileToDb::setLeadArtist (const QString path,const QString &s,const QString &artist,const QString &album)
{

    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {

        return DBERR;
    }


    databs.transaction();

    QSqlQuery q(databs );
    q.prepare("select lead_artist,album from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
        return NOTINDB;
    }

    int LartistId=q.value(0).toInt();
    int albumId=q.value(1).toInt();

    q.prepare("CALL get_artist (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't set lead artist"<< q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );
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
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path);
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
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }


    //if there are more thracks on that album the databs will cansel the delete
    q.prepare("delete from artists where id=?");
    q.addBindValue( LartistId );
    q.exec();

    if (!databs.commit() )
    {
        qDebug()<<"Seting lead artist error: "<<databs.lastError().text();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }
    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );

    return OK;
}

int player::fileToDb::setComposer (const QString path,const QString &s)
{

    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {
        return DBERR;
    }


    databs.transaction();

    QSqlQuery q(databs );
    q.prepare("select composer from tracks where path=?");
    q.addBindValue(path );
    q.exec();
    q.next();

    if (!q.isValid())
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    int composerId=q.value(0).toInt();

    q.prepare("CALL get_composer (?,@i) ");
    q.addBindValue( s );

    if (!q.exec() )
    {
        qDebug()<<"can't call get_composer"<< q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }

    q.prepare( "update tracks SET composer=@i where path=?");
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"can't update track"<< q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;

    }


    //if there are more thracks with that composer the databs will cansel the delete
    q.prepare("delete from composers where id=?");
    q.addBindValue( composerId );
    q.exec();


    if (!databs.commit() )
    {
        qDebug()<<"can't commint"<< q.lastError();

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }


    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );

    return OK;
}

bool player::fileToDb::setAlbumArtist(const QString &path,const QString &s,const QString &album,QSqlQuery &q)
{
    qDebug()<<album;
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
    qDebug()<<q.value(0);

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


int player::fileToDb::setTitle(const QString path,const QString &s)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {

        return DBERR;
    }


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
            databs.close();
            databs=QSqlDatabase();
            QSqlDatabase::removeDatabase(path );

            return NOTINDB;
        }
        qDebug()<<"setting title error"<<q.lastError();
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return DBERR;
    }

    databs.close();
    databs=QSqlDatabase();

    QSqlDatabase::removeDatabase(path );

    return OK;
}

int player::fileToDb::setComment (const QString path,const QString &s)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {

        return DBERR;
    }

    QSqlQuery q(databs );
    q.prepare( "update tracks SET comment=? where path=?");
    q.addBindValue(s);
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );

    return OK;
}

int player::fileToDb::setYear (const QString path, const unsigned int &year)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {

        return DBERR;
    }

    QSqlQuery q(databs );
    q.prepare( "update tracks SET year=? where path=?");
    q.addBindValue(QVariant(year) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path);

    return OK;
}

int player::fileToDb::setTrack (const QString path,const unsigned int &track)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {
        return DBERR;
    }

    QSqlQuery q(databs );
    q.prepare( "update tracks SET track=? where path=?");
    q.addBindValue(QVariant(track) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path);


    return OK;
}

int player::fileToDb::setRating (const QString path,const unsigned int &rating)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);
    if (!databs.open() )
    {
        return DBERR;
    }

    QSqlQuery q(databs );
    q.prepare( "update tracks SET rating=? where path=?");
    q.addBindValue(QVariant(rating) );
    q.addBindValue(path);

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path );

    return OK;
}

int player::fileToDb::setCounter(const QString path,const unsigned int &num )
{
    QSqlDatabase databs;
    databs=player::db.clone(path);

    if (!databs.open() )
    {
        return DBERR;
    }

    QSqlQuery q(databs );
    q.prepare( "update tracks SET counter=? where path=?");
    q.addBindValue(QVariant(num) );
    q.addBindValue(path );

    if (!q.exec() )
    {
        qDebug()<<"probably file not exist in library";
        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path );

        return NOTINDB;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path);

    return OK;
}

QSqlRecord player::fileToDb::record(const QString path,int &err)
{
    QSqlDatabase databs;
    databs=player::db.clone(path);

    if (!databs.open() )
    {
        err=DBERR;
        return QSqlRecord();
    }

    QSqlQuery q(databs );

    q.prepare("select * from trackView where path=?");
    q.addBindValue(path);

    if (!q.exec() )
    {
        qDebug()<<"getting record error "<<q.lastError().text();
        err=DBERR;

        databs.close();
        databs=QSqlDatabase();
        QSqlDatabase::removeDatabase(path);
        return QSqlRecord();
    }
    q.next();
    QSqlRecord r=q.record();

    if (r.isEmpty() ||q.value(PATH).isNull() )
    {
        qDebug()<<"empty record";
        err=NOTINDB;
        r=QSqlRecord();
    }
    else
    {
        err=OK;
    }

    databs.close();
    databs=QSqlDatabase();
    QSqlDatabase::removeDatabase(path);
    return r;
}

QString player::fileToDb::albumArt(const int albumId,int &err)
{
//      QSqlDatabase databs;
//      databs=player::db.clone(path);

//      if(!databs.open() )
//      {
// 	  err=DBERR;
// 	  return QString();
//      }

//      QSqlQuery q(databs );

    QSqlQuery q(db.getDatabase() );

    q.prepare("select image from albums where id=?");
    q.addBindValue(albumId);

    if (!q.exec() )
    {
        qDebug()<<"getting albumArt error "<<q.lastError().text();
        err=DBERR;

// 	  databs.close();
// 	  databs=QSqlDatabase();
// 	  QSqlDatabase::removeDatabase(path);
        return QString();
    }

    q.next();
    err=OK;

//      databs.close();
//      databs=QSqlDatabase();
//      QSqlDatabase::removeDatabase(path);
    return q.value(0).toString();
}

int player::fileToDb::setAlbumArt(const int albumId,QString art)
{
//      QSqlDatabase databs;
//      databs=player::db.clone(path);

//      if(!databs.open() )
//      {
// 	  err=DBERR;
// 	  return QString();
//      }

//      QSqlQuery q(databs );

    QSqlQuery q(db.getDatabase() );

    q.prepare("update albums SET image=? where id=?");
    q.addBindValue(art);
    q.addBindValue(albumId);

    if (!q.exec() )
    {
        qDebug()<<"setting albumArt error "<<q.lastError().text();
        return DBERR;

// 	  databs.close();
// 	  databs=QSqlDatabase();
// 	  QSqlDatabase::removeDatabase(path);
    }

    return OK;

//      databs.close();
//      databs=QSqlDatabase();
//      QSqlDatabase::removeDatabase(path);
}
