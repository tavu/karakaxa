// #include"audioFiles.h"
#include"fileCache.h"
#include<QDebug>
#include"fileToDb.h"
#include"../core/func.h"
#include"audioFiles.h"
// #define DATAB 1
// #define FILE  2

using namespace audioFiles;
// using namespace player;

audioFiles::fileCache::fileCache(QString path)
  :notInDb(false),
  tagsFlag(false),
  tagTable(0),
  file(0),
  fdb(0)
{
    _path=path;    
}

audioFiles::fileCache::~fileCache()
{
    if(tagTable!=0)
    {
 	delete []tagTable;
    }
}

int audioFiles::fileCache::loadTags(bool force)
{
    loadMutex.lock();
    if(tagTable!=0)
    {
	   if(force)
	   {
		  delete tagTable;
	   }
	   else
	   {
		  loadMutex.unlock();
		  return OK;
	   }
    }
    
    file=audioFiles::getFileTags(_path);
    tagRecord *t=new tagRecord[FRAME_NUM];
    file->getTags(t);
    lock.lockForWrite();
    tagTable=t;
    lock.unlock();       
    int err=file->error();
    delete file;
    file=0;
    loadMutex.unlock();
    return err;
}

int audioFiles::fileCache::select(bool force)
{       
    loadMutex.lock();
    //if notInDb, a previous select have occurred and we know tha the file does not exist on database
    if(notInDb && !force)
    {
	loadMutex.unlock();
	return NOTINDB;
    }
    //if the record is not empty we have alredy make a selection
    if(!record.isEmpty() && !force )
    {
	loadMutex.unlock();
	return OK;
    }
    
    int err;
    QSqlRecord rec=fileToDb::record(path(),err );
    lock.lockForWrite();
    record=rec;
    lock.unlock();

    if (err==NOTINDB)
    {      
        notInDb=true;
    }
    else
    {
	notInDb=false;
    }

    loadMutex.unlock();
    return err;
}

void fileCache::setRecord(QSqlRecord &r, bool force)
{
    loadMutex.lock();
    lock.lockForWrite();
    
    if(record.isEmpty() || force )
    {
	record=r;
	notInDb=r.isEmpty();
    }
    
    lock.unlock();
    loadMutex.unlock();
}


QVariant audioFiles::fileCache::tagFromFile(tagsEnum t, int &err)
{
    QVariant ret;
    lock.lockForRead();
    
    if(tagTable!=0)
    {
	ret=tagTable[t].value;
	err=tagTable[t].status;
    }
    else
    {
	err=TAGS_NOT_LOADED;
    }
    lock.unlock();
    return ret;
}

QVariant audioFiles::fileCache::tagFromDb(int t, int &err)
{
    QVariant ret;
    lock.lockForRead();
    
    if(!record.isEmpty())
    {
	ret=record.value(t+1);
	err=OK;
    }
    else
    {
	err=EMPTY_RECORD;
    }
    lock.unlock();
    return ret;
  
}

int audioFiles::fileCache::albumId(int &err)
{
    int ret=-1;
    lock.lockForRead();
    if(notInDb)
    {
	 err=NOTINDB;
    }    
    else if(!record.isEmpty())
    {
	ret=record.value(1).toInt();
	err=OK;
    }
    else
    {
	err=EMPTY_RECORD;
    }
    lock.unlock();
    return ret;
  
}

void fileCache::setTag(tagsEnum t, QVariant var, int& err)
{    
    if(!file->setTag(t,var) )
    {
	 qDebug()<<"edf "<<err;
    }
    err=file->error();
    
    qDebug()<<"ERrR "<<err;
    
    if(err==OK)
    {
	 tagTable[t].value=var;
      tagTable[t].status=OK;
	 if(fdb!=0 )
	 {
		err=fdb->setTag(t,var);
		if(err!=OK)
		{
		    fdb->cleanUp();
		}
		else
		{
		    record.setValue(t+1,var);
		}
	 }
    }
    else if(err==NS_TAG)
    {
	 if(fdb!=0)
	 {
		err=fdb->setTag(t,var);
		if(err!=OK)
		{	
		    fdb->cleanUp();
		}		
		else
		{
		    record.setValue(t+1,var);
		}
	 }
    }
}


void audioFiles::fileCache::setTagFromFile(tagsEnum t, QVariant var)
{    
    if(tagTable!=0 )
    {
      lock.lockForWrite();
      tagTable[t].value=var;
      tagTable[t].status=OK;
      lock.unlock();
    }
}

void audioFiles::fileCache::setTagFromDb(tagsEnum t, QVariant var)
{    
    if(! record.isEmpty() )
    {
	 lock.lockForWrite();
	 record.setValue(t+1,var);
	 lock.unlock();
    }
}

audioFiles::fileCache* audioFiles::fileCache::getFileCache(QString path)
{
    gMutex.lock();
    fileCacheS *t=fileCacheMap.value(path);

    if (t==0)
    {
        fileCache *f=new fileCache(path);
        t=new fileCacheS;
        t->p=f;

        if (t->p==0)
        {
            qDebug()<<"error malloc file cache";
            delete t;
            gMutex.unlock();
            return 0;
        }
        t->used=1;

        fileCacheMap.insert(path,t);

        gMutex.unlock();
        return t->p;
    }
    t->used++;
    gMutex.unlock();
    return t->p;
}

void audioFiles::fileCache::releaseFileCache(QString path)
{
    gMutex.lock();
    fileCacheS *t=fileCacheMap.value(path);

    if (t==0)
    {
        qDebug()<<"file cache for "<<path<<"not fount"<<"at release";
        gMutex.unlock();
        return ;
    }
    t->used--;
    if (t->used==0)
    {
         fileCacheMap.remove(path);
         delete t->p;
         delete t;

//          qDebug()<<"file cache deleted ";
    }
    gMutex.unlock();

}

void audioFiles::fileCache::releaseFileCache(audioFiles::fileCache *cache)
{
    if (cache==0)
    {
        qDebug()<<"can't release a null file";
        return;
    }
    QString path=cache->path();
    releaseFileCache(path);
}

int audioFiles::fileCache::prepareToSave()
{
    int err=OK;
    file=audioFiles::getFileTags(path()); 
    if(!notInDb)
    {
	   fdb=new fileToDb(path() );
    }
    
    if(file->isValid() )
    {
	   fdb->setAlbumC(record.value(ALBUM+1).toString() );
	   fdb->setArtistC(record.value(ARTIST+1).toString());
	   fdb->setLeadArtistC(record.value(LEAD_ARTIST+1).toString());
	   fdb->setAlbumIdC(record.value(0).toInt());
	   err=fdb->prepare();
    }
    else
    {
	   err=INVALID_FILE;
    }        
    
    return err;
}

void fileCache::savingEnd()
{
    file->save();
    delete file;
    file=0;
    
    if(fdb!=0)
    {
	 fdb->end();
	 delete fdb;
	 fdb=0;
    }
    
  
    loadMutex.unlock();
}


QHash<QString, audioFiles::fileCache::fileCacheS*> audioFiles::fileCache::fileCacheMap;
QMutex audioFiles::fileCache::gMutex;