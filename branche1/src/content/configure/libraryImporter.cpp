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
	return;
    }
    
    createTmpTable();
    
}

bool libraryImporter::import(const QString path)
{

    audioFile *f=audioFile::getAudioFile(path);
   
    QSqlQuery q(database);

    database.transaction();            

    QVariant var[FRAME_NUM];
    
    for(int i=TAGS_START;i<=TAGS_END;++i)
    {
	var[i]=f->tag((tagsEnum)i,audioFile::ONFILE|audioFile::TITLEFP);
	
	if(f->error()==fileTags::NSTAG)
	{
	    var[i]=f->tag((tagsEnum)i,audioFile::ONDATAB|audioFile::DBCACHE);
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
      
    
    var[ARTIST]=getId(var[ARTIST],"artistsTmp");
    var[LEAD_ARTIST]=getId(var[LEAD_ARTIST],"artistsTmp");
    var[GENRE]=getId(var[GENRE],"genresTmp");
    var[COMPOSER]=getId(var[COMPOSER],"composersTmp");
    var[ALBUM]= getAlbumId(var[ALBUM],*v);

    
    q.prepare("INSERT INTO tracksTmp (tracknumber,title,album,artist,lead_artist,comment,genre,composer,length,rating,year,bitrate,path,count)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    for (int i=0;i<FRAME_NUM;i++)
    {
        q.addBindValue( var[i] );

    }

    qDebug()<<"Executing import";
    if (!q.exec() )
    {
        qDebug()<<"Importer error:";
        qDebug()<<q.lastError().text();
    }

    if (!database.commit() )
    {
	qDebug()<<"Importer error: can't commit";
        qDebug()<<q.lastError().text();
    }

//     if (!f->cover().isEmpty() )
//     {
//         if (f->select())
//         {
//             qDebug()<<"EEDO";
//         }
//         int albumId=f->albumId();
// 
//         if (albumId>=0)
//         {
//             qDebug()<<"setting albumArt";
//             player::fileToDb::setAlbumArt(albumId,f->cover());
//         }
//         else
//         {
//             qDebug()<<"null albumId";
//         }
// 
//     }

    audioFile::releaseAudioFile(f);
    return true;
}


/*
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
*/

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
        }
        i++;
    }

    albumList.clear();
}

QVariant libraryImporter::getId(QVariant var,QString table)
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
    
    qDebug()<<"about to go next";
    if(q.next() )      
    {
	qDebug()<<"we went next";
        return q.value(0);
    }
    qDebug()<<"we went next";
	
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
    qDebug()<<"about to go next";
    q.next();
    qDebug()<<"we went next";
           
    return q.value(0);    
}

QVariant libraryImporter::getAlbumId(QVariant album,QVariant artist)
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

void libraryImporter::createTmpTable()
{
    QSqlQuery q(database);
    
    
    q.exec("CREATE TEMPORARY TABLE tracksTmp 	LIKE tracks");
    q.exec("CREATE TEMPORARY TABLE genresTmp 	LIKE genres");
    q.exec("CREATE TEMPORARY TABLE artistsTmp 	LIKE artists");
    q.exec("CREATE TEMPORARY TABLE albumsTmp 	LIKE albums");
    q.exec("CREATE TEMPORARY TABLE composersTmp LIKE composers");    
}

void libraryImporter::save()
{
    qDebug()<<"Saving new data";
    database.transaction();
    
    QSqlQuery q(database);
    
    q.exec("delete  from tracks");
    q.exec("delete  from genres");
    q.exec("delete  from albums");
    q.exec("delete  from artists");    
    q.exec("delete  from composers");
    
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
        
    
    if (!database.commit() )
    {
	qDebug()<<"Importer error: can't commit";
        qDebug()<<q.lastError().text();
    }
}




