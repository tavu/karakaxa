#include"fileCacheFactory.h"

#include"fileCache.h"
#include<QDebug>

audioFiles::fileCache* audioFiles::fileCacheFactory::getFileCache(QString path)
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

void audioFiles::fileCacheFactory::releaseFileCache(QString path)
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
    }
    gMutex.unlock();

}

void audioFiles::fileCacheFactory::releaseFileCache(audioFiles::fileCache *cache)
{
    if (cache==0)
    {
        qDebug()<<"can't release a null file";
        return;
    }
    QString path=cache->path();
    releaseFileCache(path);
}

QLinkedList<audioFiles::fileCache* > audioFiles::fileCacheFactory::getAllCache()
{
        QLinkedList<fileCache*> list;
        gMutex.lock();          
        
        foreach (fileCacheS* t, fileCacheMap)
        {
                 t->used++;
                 list<<t->p;
        }       
        gMutex.unlock();
        return list;
}

void audioFiles::checkAudioFilesExist()
{
        QLinkedList<fileCache*> list=fileCacheFactory::getAllCache();
        foreach(fileCache *c,list)
        {
                c->exist();
                fileCacheFactory::releaseFileCache(c);
        }
}

QHash<QString, audioFiles::fileCacheFactory::fileCacheS*> audioFiles::fileCacheFactory::fileCacheMap;
QMutex audioFiles::fileCacheFactory::gMutex;