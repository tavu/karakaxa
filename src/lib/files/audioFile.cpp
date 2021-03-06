#include"audioFile.h"
#include<QtDebug>
#include<QFileInfoList>
#include<QDir>
#include"mp3Tags.h"
#include<Basic/func.h>
#define TRV_HIDE 1
#include"fileCache.h"
#include"audioFilesSelf.h"
#include"fileCacheFactory.h"

#include<Basic/tagsTable.h>

#include<QApplication>

using namespace Basic;



const short int audioFiles::audioFile::ONDATAB=   0b00010000;
const short int audioFiles::audioFile::SELECT =   0b00000001;
const short int audioFiles::audioFile::ONCACHE=   0b00000010;
const short int audioFiles::audioFile::LOAD_FILE =0b00000100;
const short int audioFiles::audioFile::TITLEFP=   0b00001000;
const short int audioFiles::audioFile::DEFAULTF=SELECT|ONDATAB|ONCACHE|LOAD_FILE|TITLEFP;

audioFiles::audioFile::audioFile()
        :QObject(),
        fileSize(0),
        cache(0)
{    
}

audioFiles::audioFile::audioFile(QUrl u)
        :QObject(),
        fileSize(0)
{
    cache=fileCacheFactory::getFileCache(u.toLocalFile());
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
    connect(cache,SIGNAL(doesExist(bool)),this,SLOT(invalidSlot(bool) ),Qt::QueuedConnection );
}



audioFiles::audioFile::audioFile(const QString url)
        :QObject(),
        fileSize(0)
{
    cache=fileCacheFactory::getFileCache(url);    
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
    connect(cache,SIGNAL(doesExist(bool)),this,SLOT(invalidSlot(bool) ),Qt::QueuedConnection );
}

audioFiles::audioFile::audioFile(tagInfo &info, bool force)
    :QObject(),
     fileSize(0)
{
    cache=fileCacheFactory::getFileCache(info.property(PATH).toString() );
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
    connect(cache,SIGNAL(doesExist(bool)),this,SLOT(invalidSlot(bool) ),Qt::QueuedConnection );
    cache->setRecord(info,force);    
}


audioFiles::audioFile::audioFile(const audioFile &f)
        :QObject()
{
     if( !f.path().isEmpty() )
     {
        cache=fileCacheFactory::getFileCache(f.path() );
        connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
        connect(cache,SIGNAL(doesExist(bool)),this,SLOT(invalidSlot(bool) ),Qt::QueuedConnection );
     }
     else
     {
         cache=0;
     }
         

     changes.append(f.changes);
     fileSize=f.fileSize;
}

void audioFiles::audioFile::invalidSlot(bool b)
{
    if(!b)
    {
        emit invalided();
    }
}


audioFiles::audioFile::~audioFile()
{
    if(cache!=0)
    {
        fileCacheFactory::releaseFileCache(cache);
    }
}

bool audioFiles::audioFile::isValid() const
{

	if(cache==0)
	{
		err=INVALID_FILE;
		return false;
	}			

	if(!cache->exist())
	{
		err=NULL_FILE;
		return false;
	}
	
	err=OK;
	return true;
}


//deprecated
bool audioFiles::audioFile::exist(bool force)
{
	return isValid();
}

QVariant audioFiles::audioFile::tag(int t, const short int f) const
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
    stat=-1;  
    err=UNOWN;
    
    if(cache==0)
    {
        err=INVALID_FILE;
        return ret;
    }

    if(t<0 || t>=FRAME_NUM)
    {
        err=UNOWN;
        stat=-1;
        return ret;
    }    

    if (t==PATH)
    {
        stat=PATH;
        err=OK;
        return path();
    }
        
    if (f & ONDATAB)
    {
	   ret=cache->tagFromDb(t, err);
	   stat=ONDATAB;
           
           if(err==OK)
           {
                if(t!=TITLE || !ret.toString().isEmpty() || !(f & TITLEFP))
                {
                    return ret;
                }
           }
    }
    
    if ( f & ONCACHE )
    {	      
        stat=ONCACHE;
        ret=cache->tagFromFile(t, err);
            
        if(err==OK)
        {
            if(t!=TITLE || !ret.toString().isEmpty()|| !(f & TITLEFP))
            {
                return ret;
            }
        }
    }

    if ( f & SELECT)
    {
        err=cache->select();
        stat=SELECT;	
        ret=cache->tagFromDb(t, err);
        if(err==OK)
        {
            if(t!=TITLE || !ret.toString().isEmpty()|| !(f & TITLEFP))
            {
                return ret;
            }
        }
    }
    
    if (f & LOAD_FILE)
    {
        cache->loadTags();
        ret=cache->tagFromFile(t, err);
        stat=LOAD_FILE;
        
        if(t!=TITLE || !ret.toString().isEmpty() || !(f & TITLEFP))
        {
            return ret;
        }
    }
    
    if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) )
        {
                stat= TITLEFP;
                return Basic::titleFromPath(path());
        }
    


    return ret;        
}

bool audioFiles::audioFile::setTag(int t, QVariant var)
{
    if(cache==0)
    {
	   err=INVALID_FILE;
	   return false;
    }
         
    if(t>=FRAME_NUM || t<0)
    {
	   err=UNOWN;
	   return false;
    }
  
    err=cache->prepareToSave();        

    setTagPrivate(t,var);
        
    save();

    if(err==OK||err==NOTINDB)
    {
        return true;  
    }

    return false;   
}


bool audioFiles::audioFile::setTagPrivate(int t,QVariant var)
{            
  
    if(t>=FRAME_NUM || t<0)
    {
	   err=UNOWN;
	   return false;
    }    
    
    cache->setTag(t,var,err);

    return true;
}

void audioFiles::audioFile::setTags(QList<int> tags,QList<QVariant> values)
{
    if(cache==0)
    {
        err=INVALID_FILE;
        return ;
    }
    
    if(tags.isEmpty() ||tags.size()!=values.size() )
    {
        err=UNOWN;
        return ;
    }

    cache->prepareToSave();
    
    for(int i=0;i<tags.size();i++ )
    {
        setTagPrivate(tags.at(i),values.at(i) );
    }
    
    save();
}

QVariant  audioFiles::audioFile::albumArtist()
{     
    if(cache==0)
    {
        err=INVALID_FILE;
        return QVariant();
    }
    
    QString s=tag(LEAD_ARTIST).toString();
    s=s.simplified();
    if ( !s.isEmpty() )
    {
        return QVariant(s);
    }

    return tag(ARTIST);
}

QString audioFiles::audioFile::cover()
{
    if(cache==0)
    {
        err=INVALID_FILE;
        return QString();
    }
    cache->findCoverPath(err);
    QString s=cache->coverPath(err);
    return s;
}

int audioFiles::audioFile::size()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return 0;
    }
    
    if (fileSize==0)
    {
        QFile f(path() );
        fileSize=f.size();
    }
    return fileSize;
}

int audioFiles::audioFile::albumId()
{
    if(cache==0)
    {
        err=INVALID_FILE;
        return -1;
    }
    
    err=cache->select();
    
    if(err!=OK)
    {
        return -1;
    }
    return cache->albumId(err);
}

void audioFiles::audioFile::save()
{
    changes=cache->savingEnd();    
    audioFile f(*this);
    self()->emitChanged(f);
}

void audioFiles::audioFile::load(const short int f)
{
    if(cache==0)
    {
        err=INVALID_FILE;
        return ;
    }
  
    if(f & SELECT)
    {
	 stat=SELECT;
	 err=cache->select();
	 if(err==OK)
	 {
            return ;
	 }
    }
    
    if(f & LOAD_FILE)
    {
	 stat=LOAD_FILE;
	 err=cache->loadTags();
    }
    else
    {    
        stat=UNOWN;
        err=UNOWN;
    }
}

QString audioFiles::audioFile::path() const
{
    if(cache==0)
    {
        return QString();
    }
    return cache->path();
}


void audioFiles::audioFile::setRecord(tagInfo &info,bool force)
{
    if(cache==0)
    {
        cache=fileCacheFactory::getFileCache(info.property(PATH).toString() );
    }
    cache->setRecord(info,force);
}

audioFiles::audioFile* audioFiles::audioFile::operator=(const audioFile &f)
{
    if(f.cache!=0)
    {
	cache=fileCacheFactory::getFileCache(f.path() );
    }
    
    changes.append(f.changes);
    fileSize=f.fileSize;
    return this;
}

QString audioFiles::audioFile::folder()
{
    if(cache==0)
    {
	err=INVALID_FILE;
	return QString();
    }
    
    return Basic::folder(path() );
}

QString audioFiles::audioFile::format()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return QString();
    }
      
    return Basic::format(path() );
}

bool audioFiles::audioFile::inDataBase(bool force)
{
    if( cache==0)
    {
        err=INVALID_FILE;
        return false;
    }
    
    err=cache->select(force);
    
    if(err==OK)
    {
	   return true;
    }
    
    return false;
}

void audioFiles::audioFile::emitChanged(audioFiles::tagChangesL l)
{
    emit changed ( l );
}


/*
void audioFiles::audioFile::recordClean()
{
//     recFlag=true;
//     record.clear();
}
*/
