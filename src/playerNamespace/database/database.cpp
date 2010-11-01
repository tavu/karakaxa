#include"database.h"
// #include<player.h>
#include<player.h>
player::database::database()
        :QObject()
{
    createConnection();
}

bool player::database::createConnection()
{
    db.setHostName("localhost");
    db.setDatabaseName("karakaxa");
    db.setUserName("root");
    db.setPassword("mstn");

    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),db.lastError().text() );
        return false;
    }
    return true;
}

QSqlDatabase player::database::getDatabase()
{
    return db;
}

// QSqlQuery player::database::getLibraryFolders()
// {
//      return QSqlQuery("select path from library_folders",db);
// }

QStringList player::database::getLibraryFolders()
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


const QString player::database::error()
{
    return db.lastError().text();
}

const QSqlQuery player::database::artist()
{
//      return QSqlQuery("select distinct artist from artist_album order by artist asc;",db );
    return QSqlQuery("select distinct artist from artist_album order by artist asc",db);
}

const QSqlQuery player::database::artist(QString search)
{
//      return QSqlQuery("select distinct artist from artist_album order by artist asc;",db );
    toSqlSafe(search);
    QString ret= QString("select distinct name from trackView where name like '%%1%' OR title like '%%1%' OR album like '%%1%'").arg(search);

    return QSqlQuery(ret,db);


}


bool player::database::isConnected=false;

QSqlDatabase player::database::db=QSqlDatabase::addDatabase("QMYSQL");


void player::database::toSqlSafe(QString &s)
{
    s.replace('\\',"\\\\");
    s.replace('\'',"\\\'");
    s.replace('\"',"\\\"");
//      s.replace('%',"\'");
}

const QString player::database::trackTable()
{
    return QString("trackView");
}


QSqlDatabase player::database::clone(const QString &s)
{
    return db.cloneDatabase ( db, s );
}

player::database::~database()
{
    db.close();
    db=QSqlDatabase();
}

QSqlQuery player::database::albumQuery(QString artist)
{
    //creates a query with all the albums of tha artist_album

    QSqlQuery q(db);

    QString s("select albums.name,image from albums inner join artists on albums.artist=artists.id AND artists.name =?");
//      s=s.arg(artist);

    q.prepare(s);
    q.addBindValue(artist);
    return q;
}

QSqlQuery player::database::albumQuery(QString artist,QString search)
{
    //creates a query with all the albums of tha artist_album

    QSqlQuery q(db);
    QString s("select distinct album,image from trackView inner join albums on album_id=albums.id AND trackView.name='%1' AND(trackView.name like '%%2%' OR album  like '%%2%' OR title like '%%2%');");

//      q.prepare("select distinct album,image from trackView inner join albums on album_id=albums.id AND trackView.name='?' AND(album  like '%?%' OR title like '%?%'");

    toSqlSafe(artist);
    toSqlSafe(search);
    s=s.arg(artist);
    s=s.arg(search);
    q.prepare(s);

    return q;
}


QStringList player::database::getArtists(const QString &path)
{
    QSqlQuery q(db);
    QStringList l;
    q.prepare("select id from tracks where path=?");
    q.addBindValue(path);
    q.exec();
    q.next();

    int k=q.value(0).toInt();
    q.prepare("select artists.name from artists inner join track_artists on track_artists.artist=artists.id where track_artists.track=?");
    q.addBindValue(k);

    q.exec();

    if (!q.isValid() )
    {
        return l;
    }

    while (q.next())
    {
        l<<q.value(0).toString();
    }
    return l;
}

void player::database::update()
{
    emit(changed() );
}
