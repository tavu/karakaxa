#include"audioFile.h"
#include<QtDebug>
#include<QFileInfoList>
#include<QDir>
#include<player.h>
#include"fileToDb.h"
#include"mp3Tags.h"

#define TRV_HIDE 1


using namespace player;



const short int audioFiles::audioFile::ONDATAB=0b00010000;
const short int audioFiles::audioFile::SELECT=0b00000001;
const short int audioFiles::audioFile::ONCACHE=0b00000010;
const short int audioFiles::audioFile::LOAD_FILE =0b00000100;
const short int audioFiles::audioFile::TITLEFP=0b00001000;
const short int audioFiles::audioFile::DEFAULTF=SELECT|ONDATAB|ONCACHE|LOAD_FILE|TITLEFP;

audioFiles::audioFile::audioFile(const QString url)
        :QObject(),
        recFlag(true),
        fileSize(0),
        saveFlag(false),
        _mutable(false)
{
    cache=audioFiles::fileCache::getFileCache(url);
//     flags[PATH]=true;
    
//     connect(&db,SIGNAL(changed()),this,SLOT(recordClean()) );
}

audioFiles::audioFile::audioFile(const audioFile& f)
        :QObject(),
        recFlag(true),
        fileSize(0),
        saveFlag(false)
{
     cache=audioFiles::fileCache::getFileCache(f.path() );
    _mutable=f.isMutable();
    
}



audioFiles::audioFile::~audioFile()
{
    audioFiles::fileCache::releaseFileCache(cache);
//     delete file;
}


QVariant audioFiles::audioFile::tag(int t, const short int f)
{
  
/*
    this function return the tag info from the file.
    it tags a flag as an argument witch specifies the place tha the tag would be red.
    we can take the tag from the database by executing a select query(ONDATAB).
    we can save the returned values from the query and using it without executing select again(DBCACHE).
    we can read the tag from the file(ONFILE).that proces also save the tag on a cache.
    at last we can use that cache to read the tag(ONCACHE).
    
    a flag can has a lot of values using bit OR '|'.
    the order tha we would search for the values is DBCACHE,ONCACHE,ONDATAB,ONFILE
    if you want another order use this function more than one with different flag.
    
*/
    QVariant ret;

    if(t>=FRAME_NUM)
    {
	err=UNOWN;
	stat=-1;
	return ret;
    }    
    if (t==PATH)
    {
	stat=-1;
        return path();
    }
    if (f & ONDATAB)
    {
	//the first field of the record conteins the albumId
	ret=cache->tagFromDb(t+1, err);
        if (err==OK)
        {
	    stat=ONDATAB;
	    return ret;
        }
    }
    if (f & ONCACHE)
    {
	ret=cache->tagFromFile((player::tagsEnum) t, err);
	
	//if we have loaded the tags information but there is no title frame and the TITLEFP is seted we return the file name.
	if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) && err!=TAGS_NOT_LOADED)
        {	    
	    stat= ONCACHE;
	    return titleFromPath(path());
        }
        if(err==OK )
	{
	    stat=ONCACHE;
	    QString s=ret.toString().trimmed();
	    return QVariant(s);
	} 
    }

    if (f & SELECT)
    {
       err=cache->select();
       if(err==OK)
       {
	  stat=SELECT;
	  QString s=cache->tagFromDb((player::tagsEnum) t, err).toString().trimmed();	  
	  ret=QVariant(s);
       }
    }

    if (f & LOAD_FILE)
    {
	cache->loadTags();
        ret=cache->tagFromFile((player::tagsEnum) t, err);
	
	//if we have loaded the tags information but there is no title frame and the TITLEFP is seted we return the file name.
	if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) && err!=TAGS_NOT_LOADED)
        {	    
	    stat= ONCACHE;
	    return titleFromPath(path());
        }
    }
    err=UNOWN;
    stat=-1;
    return ret;
}

bool audioFiles::audioFile::setTag(int t,QVariant var)
{    
    if(t>=FRAME_NUM )
    {
	err=UNOWN;
	qDebug()<<err;
	return false;
    }
  
    if(!prepareToSave())
    {
	qDebug()<<err;
	return false;
    } 
    int f=0;
    int dberr;
        
    
    switch (t)
    {
	case LEAD_ARTIST:
	{
	    file->setTag(LEAD_ARTIST,var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setLeadArtist(path(),var.toString(),tag(ARTIST,ONDATAB).toString(),tag(ALBUM,ONDATAB).toString() );
	    }
	    break ;
	}
	case RATING:
	{
	    file->setTag(RATING,var);
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setRating(path(),var.toInt() );
	    }
	    break ;
	}
	case COUNTER:
	{
	    file->setTag(COUNTER,var.toInt());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setCounter(path(),var.toInt() );
	    }
	    break ;
	}
	case COMPOSER:
	{
	    file->setTag(COMPOSER,var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setComposer(path(),var.toString());
	    }
	    break ;
	}
	case TITLE:
	{
	    file->setTitle(var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setTitle(path(),var.toString() );
	    }
	    break ;
	}
	case ALBUM:
	{
	    file->setAlbum(var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setAlbum(path(),var.toString());
	    }
	    break ;
	}
	case ARTIST:
	{
	    file->setArtist(var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setArtist(path(),var.toString(),tag(ALBUM,ONDATAB).toString() );
	    }
	    break ;
	}
	case GENRE:
	{
	    file->setGenre(var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setGenre(path(),var.toString() );
	    }
	    break ;
	}
	case COMMENT:
	{
	    file->setTag(COMMENT,var.toString());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setComment(path(),var.toString());
	    }
	    break ;
	}
	case TRACK:
	{
	    file->setTrack(var.toInt());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setTrack(path(),var.toInt() );
	    }
	    break ;
	}
	case YEAR:
	{
	    file->setTag(YEAR,var.toInt());
	    err=file->error();
	    if(err==OK || err==NS_TAG)
	    {
		dberr=fileToDb::setYear(path(),var.toInt() );
	    }
	    break ;
	}
	default:
	{
	    err=UNOWN;
	    return false;
	}
    }
    qDebug()<<err;
    
    if(err!=NS_TAG)
    {
	f=f|1;
    }
    if(dberr==OK)
    {
      f=f|2;
    }
    cache->setTag((player::tagsEnum)t,var,f);
    err=dberr;    
    
    if(!_mutable )
    {
	db.updateSig(t);
    }

    if(!saveFlag)
    {
	save();
    }

    qDebug()<<err;
    if(err==OK||err==NOTINDB)
    {
      return true;  
    }
    else
    {
	return false;
    }
}

void audioFiles::audioFile::setTags(QList<int> tags,QList<QVariant> values)
{
    if(tags.isEmpty() ||tags.size()!=values.size() )
    {
	err=UNOWN;
	return ;
    }
    if(!prepareToSave() )
    {
	return ;
    }
    saveFlag=true;
    for(int i=0;i<tags.size();i++ )
    {
	setTag(tags.at(i),values.at(i) );
    }
    
    save();
    saveFlag=false;    
}







QVariant  audioFiles::audioFile::albumArtist()
{
    QString s=tag(LEAD_ARTIST).toString();
    s.simplified();
    if ( !s.isEmpty() )
    {
        return QVariant(s);
    }

    return file->artist();
}

QString audioFiles::audioFile::cover()
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

int audioFiles::audioFile::size()
{
    if (fileSize==0)
    {
        QFile f(path() );
        fileSize=f.size();
    }
    return fileSize;
}

int audioFiles::audioFile::albumId()
{
    err=cache->select();
    
    if(err!=OK)
    {
	return -1;
    }
    return cache->tagFromDb(0,err).toInt();
}

bool audioFiles::audioFile::prepareToSave()
{
    if(saveFlag)
    {
      err=OK;
      return true;
    }
    
    file=audioFiles::getFileTags(path());    
    if(file->isValid() )
    {
      cache->lockForSaving();
      err=OK; 
      return true;
    }
    else
    {
	err=INVALID_FILE;
    }    
    return false;
}

void audioFiles::audioFile::save()
{
    file->save();
    cache->savingEnd();
    delete file;    
    file=0;
}

void audioFiles::audioFile::load()
{
    err=cache->select();
    if(err!=OK)
    {
	err=cache->loadTags();
    }
}

audioFile* audioFiles::audioFile::operator=(const audioFile &f)
{
    recFlag=true;
    fileSize=0;
    saveFlag=false;

    cache=audioFiles::fileCache::getFileCache(f.path() );
    _mutable=f.isMutable();   
    return this;
}
/*
void audioFiles::audioFile::recordClean()
{
//     recFlag=true;
//     record.clear();
}
*/
