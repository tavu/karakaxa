#include"audioFile.h"
#include<QtDebug>
#include<QFileInfoList>
#include<QDir>
#include<player.h>
#include"fileToDb.h"
#include"mp3Tags.h"

#define TRV_HIDE 1
using namespace player;



const short int player::audioFile::DBCACHE=0b00010000;
const short int player::audioFile::ONDATAB=0b00000001;
const short int player::audioFile::ONCACHE=0b00000010;
const short int player::audioFile::ONFILE =0b00000100;
const short int player::audioFile::TITLEFP=0b00001000;
const short int player::audioFile::DEFAULTF=ONDATAB|DBCACHE|ONCACHE|ONFILE|TITLEFP;

player::audioFile::audioFile(const QString url)
        :recFlag(true),
        fileSize(0)
{
//      record=QSqlRecord();
    table=new QVariant[FRAME_NUM];
    flags=new bool[FRAME_NUM];


    for (int i=0;i<FRAME_NUM;i++)	flags[i]=false;

    flags[PATH]=true;

    file=getFileTags(url);
}

QVariant player::audioFile::tag(tagsEnum t,short int f)
{
    if (t==PATH)
        return getPath();

    if (f & DBCACHE)
    {
        if (!record.isEmpty())
        {
            return record.value(t+TRV_HIDE);
        }
    }

    if (f & ONCACHE)
    {
        if (flags[t])
        {
            if (t==TITLE)
            {
                if (table[t].toString().isEmpty() && (f & TITLEFP) )
                {
                    return titleFromPath(getPath() );
                }
            }
            return table[t];
        }
    }

    if (f & ONDATAB)
    {
        //we use the recFlag as a flag to tell us if the file exist in database.
        //if i doesn't we don't need to make queries at the next searches
        //if you wan't to search again set the flag to true(setDBFLAG() )
        if (recFlag)
        {
            select();
        }
    }

    if (f & ONFILE)
    {
        if (t==TITLE)
        {
            table[t]=file->title();
            flags[t]=true;

            if (table[t].toString().isEmpty() &&(f & TITLEFP) )
            {
                return titleFromPath(getPath() );
            }
            return table[t];
        }

        table[t]=file->tag(t);
        flags[t]=true;
        return table[t];
    }
    return QVariant();
}

bool player::audioFile::setTag(tagsEnum t,QVariant var)
{
    switch (t)
    {
    case LEAD_ARTIST:
    {
        return setLeadArtist(var.toString() );
    }
    case RATING:
    {
        return setRating(var.toInt() );
    }
    case COUNTER:
    {
        return setCounter(var.toInt() );
    }
    case COMPOSER:
    {
        return setComposer(var.toString() );
    }
    case TITLE:
    {
        return setTitle(var.toString());
    }
    case ALBUM:
    {
        return setAlbum(var.toString());
    }
    case ARTIST:
    {
        return setArtist(var.toString());
    }
    case GENRE:
    {
        return setGenre(var.toString());
    }
    case COMMENT:
    {
        return setComment(var.toString());
    }
    case TRACK:
    {
        return setTrack(var.toInt());
    }
    case YEAR:
    {
        return setYear(var.toInt() );
    }

    default:
    {
        return false;
    }
    }
}
bool player::audioFile::setArtist (const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setArtist(s) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[ARTIST]=QVariant(s);
    flags[ARTIST]=true;

    if ( fileToDb::setArtist(file->getPath(),s,tag(ALBUM,ONDATAB).toString() )==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setAlbum(const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setAlbum(s) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[ALBUM]=QVariant(s);
    flags[ALBUM]=true;

    if ( fileToDb::setAlbum(file->getPath(),s)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}


bool player::audioFile::setGenre(const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setGenre(s) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[GENRE]=QVariant(s);
    flags[GENRE]=true;

    if ( fileToDb::setGenre(file->getPath(),s)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setLeadArtist(const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTag(LEAD_ARTIST,QVariant(s) ) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[ARTIST]=QVariant(s);
    flags[ARTIST]=true;

    if ( fileToDb::setLeadArtist(file->getPath(),s,tag(ARTIST,ONDATAB).toString(),tag(ALBUM,ONDATAB).toString() )==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setComposer (const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTag(COMPOSER, QVariant(s) ) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[COMPOSER]=QVariant(s);
    flags[COMPOSER]=true;

    if ( fileToDb::setComposer(file->getPath(),s)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setTitle (const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTitle(s) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[TITLE]=QVariant(s);
    flags[TITLE]=true;

    if ( fileToDb::setTitle(file->getPath(),s)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setComment (const QString &s)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setComment(s) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[COMMENT]=QVariant(s);
    flags[COMMENT]=true;

    if ( fileToDb::setComment(file->getPath(),s)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setYear (const unsigned int &year)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setYear(year) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[YEAR]=QVariant(year);
    flags[YEAR]=true;

    if ( fileToDb::setYear(file->getPath(),year)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setTrack (const unsigned int &track)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTrack(track) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[TRACK]=QVariant(track);
    flags[TRACK]=true;

    if ( fileToDb::setTrack(file->getPath(),track)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setRating (const unsigned int &rating)
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTag(RATING,QVariant(rating) ) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[RATING]=QVariant(rating);
    flags[RATING]=true;

    if ( fileToDb::setRating(file->getPath(),rating)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

bool player::audioFile::setCounter(const unsigned int &num )
{
    mutex.lock();

    //if the file is not supportes(fileTags::NSTAG) we stil update the information on database
    //at any other error we return
    if (!file->setTag(COUNTER,QVariant(num) ) && file->error()!=fileTags::NSTAG)
    {
        mutex.unlock();
        return false;
    }

    table[COUNTER]=QVariant(num);
    flags[COUNTER]=true;

    if ( fileToDb::setCounter(file->getPath(),num)==fileToDb::DBERR)
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

QVariant  player::audioFile::albumArtist()
{
    QVariant v=tag(LEAD_ARTIST);
    if ( ! (v.isNull() ) && !( v.toString().isEmpty() ) )
    {
        return QVariant(tag(LEAD_ARTIST) );
    }
    else
    {
        QString s=file->artist().toString();
        if (s.isNull() )
        {
            return QVariant();
        }

// 	  test
        return s;
    }
}

QString player::audioFile::cover()
{
    //if albumArt is null we haven't search for covers yet.
    if (!albumArt.isNull() )
    {
        return albumArt;
    }

    QDir dir(folder() );
    QFileInfoList infoList=dir.entryInfoList( player::config.imagefiles());

    //first list all image files
    infoList=dir.entryInfoList( player::config.imagefiles());

    QString tmp;
    //for every image file
    for (int i=0;i<infoList.size();i++)
    {
        albumArt=infoList.at(i).absoluteFilePath();
        tmp=player::titleFromPath(albumArt);
        //if the file named folder we use tha image
        //else we use just a random one(at the last place of the list)
        if (tmp.compare("FOLDER",Qt::CaseInsensitive)==0 )
        {
            break;
        }

    }
    //if there is not cover we set albumArt to empty to avoid search again
    if (albumArt.isNull())
    {
        albumArt=QString("");
    }
    return albumArt;
}

void player::audioFile::clear()
{
    albumArt=QString();

    for (int i=0;i<FRAME_NUM;i++)	flags[i]=false;

    fileSize=0;
}

int player::audioFile::size()
{
    if (fileSize==0)
    {
        QFile f(getPath() );
        fileSize=f.size();
    }
    return fileSize;
}

bool player::audioFile::onCache(tagsEnum t)
{
    return flags[t];
}

QString player::audioFile::getPath()
{
    return file->getPath();
}

int player::audioFile::albumId()
{

    if (record.isEmpty() && recFlag)
    {
        select();
    }

    if (record.isEmpty() )
    {
        return -1;
    }

    return record.value(0).toInt();

}

fileTags* player::audioFile::getFileTags(const QString path)
{
    fileTags *ret;

    QString f=player::format(path);
    if (QString::compare(QString("mp3"),f,Qt::CaseInsensitive )==0)
    {
        ret=new mp3Tags(path);
    }
    else
    {
        ret=new fileTags(path);
    }
    return ret;
}

bool player::audioFile::select()
{
    int err;
    record=fileToDb::record(getPath(),err );

    if (err==fileToDb::NOTINDB)
    {
        recFlag=false;
        return false;
    }

    recFlag=true;
    return true;

}

player::audioFile* player::audioFile::getAudioFile(QString path)
{
    gMutex.lock();
    audioFileS *t=fileMap.value(path );

    if (t==0)
    {
// 	  qDebug()<<"file "<<path<<"not fount";

        audioFile *f=new audioFile(path);
        t=new audioFileS;
        t->p=f;

        if (t->p==0)
        {
            qDebug()<<"error malloc audioFile";
            delete t;
            gMutex.unlock();
            return 0;
        }
        t->used=1;

        fileMap.insert(path,t);

        gMutex.unlock();
        return t->p;
    }
    t->used++;
    gMutex.unlock();
    return t->p;
}

void player::audioFile::releaseAudioFile(QString path)
{
    gMutex.lock();
    audioFileS *t=fileMap.value(path );

    if (t==0)
    {
        qDebug()<<"file: "<<path<<"not fount"<<"at release";
        gMutex.unlock();
        return ;
    }
    t->used--;
    if (t->used==0)
    {
        fileMap.remove(path);
        delete t->p;
        delete t;

        qDebug()<<"audiofile deleted ";
    }
    gMutex.unlock();

}

void player::audioFile::releaseAudioFile(audioFile *file)
{
    if (file==0)
    {
        qDebug()<<"can't release a null file";
        return;
    }
    QString s=file->getPath();
    releaseAudioFile(s);
}

QMap<QString, player::audioFile::audioFileS*> player::audioFile::fileMap;
QMutex player::audioFile::gMutex;
