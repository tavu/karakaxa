#include"libraryImporter.h"
#include<QSqlDatabase>
#include<QWidget>


using namespace player;
using namespace std;


libraryImporter::libraryImporter()
        :QObject(),
        name("importer")
{

//      connect(this,SIGNAL(error(QString) ),&player::errors,SLOT(setError(QString)),Qt::QueuedConnection);

    database=player::db.clone(name);

    isConnected=database.open();

    if (!isConnected)
    {
        qDebug()<<"Database Error: "<<database.lastError().text();
    }
}

bool libraryImporter::import(const QString path)
{

    audioFile *f=audioFile::getAudioFile(path);

    QString albumArtist;

    if ( ! f->tag(LEAD_ARTIST,audioFile::ONFILE).isNull() )
    {
        albumArtist=f->tag(LEAD_ARTIST).toString();
    }
    else
    {
        albumArtist=f->tag(ARTIST,audioFile::ONFILE).toString();
    }

    QSqlQuery query(database);

    database.transaction();
    query.prepare("call insert_track(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");


    query.addBindValue(albumArtist);

    for (int i=0;i<FRAME_NUM-1;i++)
    {
        query.addBindValue( f->tag( (tagsEnum)i,audioFile::ONFILE|audioFile::TITLEFP)  );

    }



    if (!query.exec() )
    {
// 	  std::cout<<query.lastError().text().toUtf8().data()<<std::endl;
        qDebug()<<"Importer error:Can't call insert_track";
        qDebug()<<query.lastError().text();

// 	  audioFile::releaseAudioFile(f);
// 	  return false;
    }

    qDebug()<<"Eeeeeeeeeeeeeeeeeeeeeki";

    if (!database.commit() )
    {
        qDebug()<<"Importer error: can't commit";
        qDebug()<<query.lastError().text();

// 	 audioFile::releaseAudioFile(f);
// 	 return false;
    }
    qDebug()<<"Eeeeeeeeeeeeeeeeeeeeeki";

    if (!f->cover().isEmpty() )
    {
        qDebug()<<"EEki";
        if (f->select())
        {
            qDebug()<<"EEDO";
        }
        int albumId=f->albumId();

        if (albumId>=0)
        {
            qDebug()<<"setting albumArt";
            player::fileToDb::setAlbumArt(albumId,f->cover());
        }
        else
        {
            qDebug()<<"null albumId";
        }

    }

    audioFile::releaseAudioFile(f);
    return true;
}

int libraryImporter::n=0;

QString libraryImporter::error()
{
    return database.lastError().text();
}

libraryImporter::~libraryImporter()
{
    database.close();
}

void libraryImporter::saveAlbumArt(const QString &albumArt)
{

    if (albumArt.isEmpty() )
    {
        albumList.clear();
        return ;
    }

    QMap<QString, QString>::const_iterator i = albumList.begin();

    QSqlQuery query(database);
    QSqlQuery query2(database);
    QSqlQuery query3(database);
    while ( i!=albumList.end() )
    {
        query.prepare("select albums.id from albums inner join artists on albums.name=? AND artists.name = ? AND albums.artist=artists.id");

        std::cout<<"edo "<<i.key().toUtf8().data()<<" "<<i.value().toUtf8().data()<<std::endl;
        query.addBindValue(i.key() );
        query.addBindValue(i.value() );
        if (!query.exec() )
        {
            std::cout<<"eerrr :"<<query.lastError().text().toUtf8().data()<<std::endl;
        }
        query.next();
        QVariant s=query.value(0);

        std::cout<<"value "<<albumArt.toUtf8().data()<<std::endl;
        query2.prepare("update albums set image = ? where id=?");
        query2.addBindValue(albumArt );
        query2.addBindValue(s );

        if (!query2.exec() )
        {
            std::cout<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeor"<<std::endl;
        }
        i++;
    }
//                test

    albumList.clear();
}
