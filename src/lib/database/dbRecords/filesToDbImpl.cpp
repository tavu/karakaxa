#include"filesToDbImpl.h"
#include <Basic/tagsTable.h>
#include "baseRecord.h"
#include <database.h>
#include<QDebug>
using namespace Basic;

database::filesToDbImpl::filesToDbImpl ( QString path,QObject *parent) :filesToDb(),dbBase()
{
    track=new dbPrivate::trackViewRecord(path);
    _error=OK;
    _inDb=Basic::UNOWN;
}

database::filesToDbImpl::filesToDbImpl ( int id,QObject *parent) :filesToDb(),dbBase()
{
    track=new dbPrivate::trackViewRecord(id);
    _error=OK;
    _inDb=Basic::UNOWN;
}


QString database::filesToDbImpl::albumArt()
{
    if(_inDb==NOTINDB)
    {
        _error=NOTINDB;
        return QString();
    }
    
    dbPrivate::baseRecord *br=track->getAlbumRecord();
    
    if(!br->hasData(Basic::IMAGE) )
    {
        _error=OK;
        return br->getValue(Basic::IMAGE).toString();
    }
    _error=Basic::NOT_SELECTED;
    return QString();
}


QVariant database::filesToDbImpl::tag ( int t )
{
    
    if(_inDb==NOTINDB )
    {
        _error=Basic::NOTINDB;
        return QVariant();
    }
    
    if(!track->hasData(t) )
    {
        _error=Basic::NOT_SELECTED;
        return QVariant();
    }        
    
    _error=OK;
    return track->getValue(t);
}

int database::filesToDbImpl::setTag ( int t, QVariant& value )
{    
    qDebug()<<"set TAg";
    if(!track->hasEntry(t) )
    {
        _error=Basic::UNOWN;        
    }
     
    track->changeEntry(t,value);
    if ( t==LEAD_ARTIST )
    {
        qDebug() <<"set album artist";
        track->changeEntry( ALBUM_ARTIST,value );
    }
    else if(t==Basic::ARTIST)
    {
        QVariant leadArt=track->getValue(Basic::LEAD_ARTIST);
        if(leadArt.isNull() )
        {
            qDebug()<<"null lead artist";
            _error=Basic::DBERR;
            track->clearNewValue();
            return _error;
        }
        else if(leadArt.toString().trimmed().isEmpty() )
        {
            track->changeEntry( ALBUM_ARTIST,value );
        }
    }
    _error=Basic::OK;
    return _error;
}

int database::filesToDbImpl::select()
{
    databs=db()->getDatabase();
 
    track->setDatabase(databs);
    _error=track->select();
    db()->closeDatabase(databs);
    if(_error==Basic::OK)
    {
        _inDb=Basic::OK;
    }
    else if(_error==Basic::NOTINDB)
    {
        _inDb=Basic::NOTINDB;
    }
    
    return _error;
}

int database::filesToDbImpl::error()
{
    return _error;
}

int database::filesToDbImpl::id()
{
    QVariant v=track->getTrackRecord()->id();
    
    if(v.isNull() )
    {    
         
        if(_inDb==NOTINDB )
        {
            _error=Basic::NOTINDB;
        }
        
        if(!track->isSelected() )
        {
            _error=Basic::NOT_SELECTED;
        }
    }
    return v.toInt();
}

int database::filesToDbImpl::inDb()
{
    return _inDb;
}

QString database::filesToDbImpl::path()
{
    return track->getValue(Basic::PATH).toString();
}

int database::filesToDbImpl::prepareToSave()
{
    databs=db()->getDatabase();
    if (!databs.isOpen())
    {
        _error=Basic::DBERR;
    }  
    else
    {
        track->setDatabase(databs);
    }
    lock();
    _error= track->select();
     
    if(_error==Basic::OK)
    {
        _inDb=Basic::OK;
    }
    else if(_error==Basic::NOTINDB)
    {
        _inDb=Basic::NOTINDB;
    }
    
    return _error;
}

int database::filesToDbImpl::commit()
{
    _error=track->save();
    unlock();
    db()->closeDatabase(databs);
    return _error;
}

int database::filesToDbImpl::updateRecord ( QSqlRecord& r )
{
    return track->updateRecord(r);
}

bool database::filesToDbImpl::isSelected()
{
    return track->isSelected();
}
