// #include"audioFiles.h"
#include"fileCache.h"
#include<QDebug>
#include"fileToDb.h"
// 
// #define DATAB 1
// #define FILE  2

using namespace audioFiles;
// using namespace player;

audioFiles::fileCache::fileCache(QString path)
  :notInDb(false),
  tagsFlag(false),
  tagTable(0)
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
    
    fileTags *file=audioFiles::getFileTags(_path);
    tagRecord *t=new tagRecord[FRAME_NUM];
    file->getTags(t);
    lock.lockForWrite();
    tagTable=t;
    lock.unlock();   
    loadMutex.unlock();
    int err=file->error();
    delete file;
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
    //if record is Empty and notInDb is false we have not select
    if(!record.isEmpty() && !force )
    {
	loadMutex.unlock();
	return OK;
    }
    
    int err;
    qDebug()<<"DBdsr";
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
    qDebug()<<"DB "<<err;
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
	ret=record.value(t);
	err=OK;
    }
    else
    {
	err=EMPTY_RECORD;
    }
    lock.unlock();
    return ret;
  
}

void audioFiles::fileCache::setTag(tagsEnum t, QVariant var,int f)
{
    if(tagTable!=0 && (f & 1) )
    {
      lock.lockForWrite();
      tagTable[t].value=var;
      tagTable[t].status=OK;
      lock.unlock();
    }
    if(! record.isEmpty() && (f& 2) )
    {
	lock.lockForRead();
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
    fileCacheS *t=fileCacheMap.value(path );

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

void fileCache::lockForSaving()
{
    loadMutex.lock();
}

void fileCache::savingEnd()
{
    loadMutex.unlock();
}


QHash<QString, audioFiles::fileCache::fileCacheS*> audioFiles::fileCache::fileCacheMap;
QMutex audioFiles::fileCache::gMutex;