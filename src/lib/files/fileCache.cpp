#include"fileCache.h"
#include<QDebug>
#include<QFileInfo>
#include<QFileInfoList>
#include<QDir>
#include<QFile>

#include<core/func.h>
#include"audioFiles.h"
#include<filesToDb/fileToDb.h>
#include<Basic/tagsTable.h>
#include <Basic/tagsTable.h>
#include"tagList.h"

Q_DECLARE_METATYPE ( audioFiles::tagChangesL )
using namespace Basic;


audioFiles::fileCache::fileCache ( QString path )
    :QObject(),
     tagTable ( 0 ),
     file ( 0 ),
     _exist ( true )
{
    _path=path;
    fdb=Basic::getFdb ( path );
}

audioFiles::fileCache::~fileCache()
{
    if ( tagTable!=0 )
    {
        delete []tagTable;
    }
    delete fdb;
}

int audioFiles::fileCache::loadTags(bool force)
{
    loadMutex.lock();
    if ( tagTable!=0 )
    {
        if ( force )
        {
            delete tagTable;
        }
        else
        {
            loadMutex.unlock();
            return OK;
        }
    }

    file=audioFiles::getFileTags ( _path );
    if ( !file->isValid() )
    {
        loadMutex.unlock();
        return file->error();
    }

    tagRecord *t=new tagRecord[FRAME_NUM];
    file->getTags ( t );
//     readMutex.lock();
    tagTable=t;
//     readMutex.unlock();
    int err=file->error();
    delete file;
    file=0;
    loadMutex.unlock();
    return err;
}

int audioFiles::fileCache::select ( bool force )
{
    loadMutex.lock();
    int ret=OK;
    
    if ( !fdb->isSelected() || force )
    {
        ret=fdb->select();
    }
    loadMutex.unlock();
    return ret;
}

QString audioFiles::fileCache::coverPath()
{
    return fdb->albumArt();
}

QString audioFiles::fileCache::findCoverPath ( int &err )
{
    loadMutex.lock();
    QString ret=fdb->albumArt ();
    err=fdb->error();
    if ( err==NOT_SELECTED )
    {
        fdb->select();
        QString ret=fdb->albumArt ();
        err=fdb->error();
    }
    loadMutex.unlock();
    return ret;
}


void audioFiles::fileCache::setRecord ( QSqlRecord &r, bool force )
{
    loadMutex.lock();
//     readMutex.lock();

    if ( !fdb->isSelected() || force )
    {
        fdb->updateRecord ( r );
    }

//     readMutex.unlock();
    loadMutex.unlock();
}


QVariant audioFiles::fileCache::tagFromFile ( int t, int &err )
{
    QVariant ret;
//     return QVariant();
    if ( tagTable!=0 )
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

QVariant audioFiles::fileCache::tagFromDb ( int t, int &err )
{
    QVariant ret;
    ret=fdb->tag ( t );
    err=fdb->error();
    return ret;

}

int audioFiles::fileCache::albumId ( int &err )
{
    QVariant v=fdb->tag ( ALBUM_ID );
    err=fdb->error();
    if ( v.isNull() )
    {
        return -1;
    }
    return v.toInt();
}

int audioFiles::fileCache::prepareToSave()
{
    loadMutex.lock();
    changes.clear();
    int err=OK;
    file=audioFiles::getFileTags ( path() );

    if ( ! file->isValid() )
    {
        return INVALID_FILE;
    }

    err=fdb->prepareToSave();

    return err;
}

void audioFiles::fileCache::setTag ( int t, QVariant var, int& err )
{
    file->setTag ( t,var );
    err=file->error();

    if ( err!=OK && err!=NS_TAG )
    {
        return ;
    }
    setTagFromFile ( t,var );
    if(fdb->inDb() && fdb->error()==Basic::OK)
    {
        err=fdb->setTag ( t,var );
        if ( err!=OK )
        {
            qDebug() <<err;
            return ;
        }
    }
    
    tagChanges change;
    change.tag=t;
    change.value=var;
    change.error=err;

    changes<<change;
}


void audioFiles::fileCache::setTagFromFile ( int t, QVariant var )
{
    if ( tagTable!=0 )
    {
//         readMutex.lock();
        tagTable[t].value=var;
        tagTable[t].status=OK;
//         readMutex.unlock();
    }
}

QList<audioFiles::tagChanges> audioFiles::fileCache::savingEnd()
{
    file->save();
    fdb->commit();
    delete file;
    file=0;

    loadMutex.unlock();

    emit changed ( changes );
    return changes;
}

bool audioFiles::fileCache::exist()
{
    loadMutex.lock();
    QFile f ( _path );
    bool b=f.exists();

    if ( _exist != b )
    {
        _exist=b;
        loadMutex.unlock();
        emit doesExist ( _exist );
        return _exist;
    }

    loadMutex.unlock();
    return _exist;
}
