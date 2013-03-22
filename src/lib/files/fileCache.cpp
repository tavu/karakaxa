#include"fileCache.h"
#include<QDebug>
#include<QFileInfo>
#include<QFileInfoList>
#include<QDir>
#include<QFile>

#include"../core/func.h"
#include"audioFiles.h"
#include<filesToDb/fileToDb.h>
#include"tagsTable.h"

Q_DECLARE_METATYPE(audioFiles::tagChangesL)
using namespace audioFiles;


audioFiles::fileCache::fileCache(QString path)
        :QObject(),
        tagTable(0),
        file(0),
        fdb(path)
{
    _path=path;
}

audioFiles::fileCache::~fileCache()
{
    if (tagTable!=0)
    {
        delete []tagTable;
    }
}

int audioFiles::fileCache::loadTags(bool force)
{
    loadMutex.lock();
    if (tagTable!=0)
    {
        if (force)
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
    if(!file->isValid() )
    {
        loadMutex.unlock();
        return file->error();
    }
    
    tagRecord *t=new tagRecord[FRAME_NUM];
    file->getTags(t);
//     readMutex.lock();
    tagTable=t;
//     readMutex.unlock();
    int err=file->error();
    delete file;
    file=0;
    loadMutex.unlock();
    return err;
}

int audioFiles::fileCache::select(bool force)
{
    loadMutex.lock();
    int ret=OK;
    if(fdb.recordError()==NOT_SELECTED ||force)
    {
        ret=fdb.select();
    }
    loadMutex.unlock();
    return ret;
}

QString fileCache::coverPath()
{
    int err;
    return fdb.albumArt(err);
}

QString fileCache::findCoverPath(int &err)
{
    loadMutex.lock();
    QString ret=fdb.albumArt (err);
    if(err==NOT_SELECTED)
    {
        fdb.selectAlbumArtist();
        QString ret=fdb.albumArt (err);
    }
    loadMutex.unlock();
    return ret;
}


void fileCache::setRecord(QSqlRecord &r, bool force)
{
    loadMutex.lock();
//     readMutex.lock();

    if(fdb.recordError()!=OK || force )
    {
        fdb.updateRecord(r);
    }

//     readMutex.unlock();
    loadMutex.unlock();
}


QVariant audioFiles::fileCache::tagFromFile(int t, int &err)
{
    QVariant ret;
//     readMutex.lock();

    if (tagTable!=0)
    {
        ret=tagTable[t].value;
        err=tagTable[t].status;
    }
    else
    {
        err=TAGS_NOT_LOADED;
    }

//     readMutex.unlock();    
    return ret;
}

QVariant audioFiles::fileCache::tagFromDb(int t, int &err)
{
    QVariant ret;
    
    ret=fdb.tag(t,err);

    return ret;

}

int audioFiles::fileCache::albumId(int &err)
{
    int ret=-1;
//     readMutex.lock();

    ret=fdb.albumId(err);
//     readMutex.unlock();
    return ret;

}

int audioFiles::fileCache::prepareToSave()
{
    loadMutex.lock();
    changes.clear();
    int err=OK;
    file=audioFiles::getFileTags(path());

    if (! file->isValid() )
    {
        return INVALID_FILE;
    }

    err=fdb.prepare();

    return err;
}

void fileCache::setTag(int t, QVariant var, int& err)
{
    file->setTag(t,var);
    err=file->error();

    if (err==OK)
    {
        setTagFromFile(t,var);
        err=fdb.setTag(t,var);

    }
    else if (err==NS_TAG)
    {
        err=fdb.setTag(t,var);
    }
    
    tagChanges change;
    change.tag=t;
    change.value=var;
    change.error=err;
    
    changes<<change;
}


void audioFiles::fileCache::setTagFromFile(int t, QVariant var)
{
    if (tagTable!=0 )
    {
//         readMutex.lock();
        tagTable[t].value=var;
        tagTable[t].status=OK;
//         readMutex.unlock();
    }
}

QList<tagChanges> fileCache::savingEnd()
{    
    file->save();
    fdb.end();
    delete file;
    file=0;

    loadMutex.unlock();

    emit changed(changes);
    return changes;
}

bool fileCache::exist()
{
    loadMutex.lock();
    QFile f(_path);
    bool b=f.exists();
    loadMutex.unlock();
    if(!b)
    {
        emit removed();
    }
    return b;
}