#include"audioFile.h"
#include<QtDebug>
#include<QFileInfoList>
#include<QDir>
// #include<player.h>
// #include"fileToDb.h"
#include"mp3Tags.h"
#include"../core/func.h"
#define TRV_HIDE 1
#include"fileCache.h"
#include"audioFilesSelf.h"

// using namespace player;



const short int audioFiles::audioFile::ONDATAB=   0b00010000;
const short int audioFiles::audioFile::SELECT =   0b00000001;
const short int audioFiles::audioFile::ONCACHE=   0b00000010;
const short int audioFiles::audioFile::LOAD_FILE =0b00000100;
const short int audioFiles::audioFile::TITLEFP=   0b00001000;
const short int audioFiles::audioFile::DEFAULTF=SELECT|ONDATAB|ONCACHE|LOAD_FILE|TITLEFP;

audioFiles::audioFile::audioFile()
        :QObject(),
        fileSize(0),
        saveFlag(true),
        cache(0),
        _exist(false)
{    
}

audioFiles::audioFile::audioFile(QUrl u)
        :QObject(),
        fileSize(0),
        saveFlag(true),
        _exist(true)
{
    cache=audioFiles::fileCache::getFileCache(u.toLocalFile());
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
	connect(cache,SIGNAL(removed()),this,SLOT(invalidSlot() ),Qt::QueuedConnection );
}



audioFiles::audioFile::audioFile(const QString url)
        :QObject(),
        fileSize(0),
        saveFlag(true),
        _exist(true)
{
    cache=audioFiles::fileCache::getFileCache(url);    
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
	connect(cache,SIGNAL(removed()),this,SLOT(invalidSlot() ),Qt::QueuedConnection );
}

audioFiles::audioFile::audioFile(QSqlRecord r, bool force)
    :QObject(),
     fileSize(0),
     saveFlag(true),
     _exist(true)
{
    cache=audioFiles::fileCache::getFileCache(r.value(PATH+2).toString() );
    connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
	connect(cache,SIGNAL(removed()),this,SLOT(invalidSlot() ),Qt::QueuedConnection );
    cache->setRecord(r,force);    
}


audioFiles::audioFile::audioFile(const audioFile &f)
        :QObject(),
        saveFlag(true)
{
     if( !f.path().isEmpty() )
     {
        cache=audioFiles::fileCache::getFileCache(f.path() );
        connect(cache,SIGNAL(changed(audioFiles::tagChangesL) ),this,SLOT(emitChanged(audioFiles::tagChangesL) ),Qt::QueuedConnection );
		connect(cache,SIGNAL(removed()),this,SLOT(invalidSlot() ),Qt::QueuedConnection );
     }
     _exist=f._exist;
     changes.append(f.changes);
     fileSize=f.fileSize;
}



audioFiles::audioFile::~audioFile()
{
    audioFiles::fileCache::releaseFileCache(cache);
}

bool audioFiles::audioFile::isValid() const
{

	if(cache==0)
	{
		err=INVALID_FILE;
		return false;
	}			

	if(!_exist)
	{
		err=NULL_FILE;
		return false;
	}
	
	err=OK;
	return true;
}

bool audioFiles::audioFile::exist(bool force)
{
	if(cache==0)
	{
		err=INVALID_FILE;
		return false;
	}
	
	if(force)
	{
		_exist=cache->exist();
	}
	err=OK;
	return _exist;
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
	   ret=cache->tagFromDb(t, err);
	   stat=ONDATAB;
    }
    if ( err!=OK  && (f & ONCACHE) )
    {	      
        stat=ONCACHE;
        ret=cache->tagFromFile((tagsEnum) t, err);
    }
    if ( err!=OK && (f & SELECT) )
    {
        err=cache->select();
        stat=SELECT;	
        ret=cache->tagFromDb((tagsEnum) t, err);
    }
    if ( err!=OK && (f & LOAD_FILE) )
    {
        cache->loadTags();
        ret=cache->tagFromFile((tagsEnum) t, err);
        stat=ONCACHE;
    }
    
    if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) )
	{
	    stat= TITLEFP;
 	    ret=core::titleFromPath(path());        	  
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
  
    cache->select(true);
    cache->loadTags();
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
    
    cache->setTag((tagsEnum)t,var,err);
    
    tagChanges change;
    change.tag=t;
    change.value=var;
    change.error=err;
    
    changes<<change;
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
    
    cache->select(true);
    cache->loadTags();
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
    QString ret=cache->coverPath();
    if(ret.isEmpty() )
    {
        ret=cache->findCoverPath(err);
    }
    return ret;
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
    cache->savingEnd(changes);    
    audioFile f(*this);
    self()->emitChanged(f);
//     core::db->updateSig(f);        
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


void audioFiles::audioFile::setRecord(QSqlRecord r,bool force)
{
    if(cache==0)
    {
        cache=audioFiles::fileCache::getFileCache(r.value(PATH+1).toString() );
    }
    cache->setRecord(r,force);
}

audioFiles::audioFile* audioFiles::audioFile::operator=(const audioFile &f)
{
    saveFlag=true;

    if(f.cache!=0)
    {
		cache=audioFiles::fileCache::getFileCache(f.path() );
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
    
    return core::folder(path() );
}

QString audioFiles::audioFile::format()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return QString();
    }
      
    return core::format(path() );
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


/*
void audioFiles::audioFile::recordClean()
{
//     recFlag=true;
//     record.clear();
}
*/
