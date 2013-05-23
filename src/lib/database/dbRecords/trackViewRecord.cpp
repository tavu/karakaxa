#include "trackViewRecord.h"
#include "trackRecord.h"

#include<Basic/tagsTable.h>
#include <QSqlRecord>

database::dbPrivate::trackViewRecord::trackViewRecord ( QString path ):abstractRecord(),_isSelected(false)
{
    track=new trackRecord(path);
}

database::dbPrivate::trackViewRecord::trackViewRecord ( int id ) :abstractRecord(),_isSelected(false)
{
    track=new trackRecord();
    track->setId(QVariant(id) );
}

database::dbPrivate::trackViewRecord::~trackViewRecord()
{
    delete track;
}

void database::dbPrivate::trackViewRecord::changeEntry ( int t, QVariant& v )
{
    using namespace Basic;
    switch (t)
    {
        case LEAD_ARTIST:
        case ARTIST:
        case ALBUM:
        case GENRE:
        case COMPOSER:
        {
            baseRecord *br=track->getRelated(t);
            br->changeEntry(0,v);
            break;
        }   
        case ALBUM_ARTIST:
        {
            dbPrivate::baseRecord *br=track->getRelated(ALBUM);
            br=br->getRelated(ALBUM_ARTIST);
            br->changeEntry(0,v);
            break;
        }
        default:
        {
            if(track->hasEntry(t) )
            {
                track->changeEntry(t,v);
            }
        }
    }
}

QVariant database::dbPrivate::trackViewRecord::getValue ( int t) const
{
    using namespace Basic;
    QVariant ret;
    
    switch (t)
    {
        case LEAD_ARTIST:
        case ARTIST:
        case ALBUM:
        case GENRE:
        case COMPOSER:
        {
            baseRecord *br=track->getRelated(t);
            ret= br->getValue(0);
            break;
        }   
        case ALBUM_ARTIST:
        {
            dbPrivate::baseRecord *br=track->getRelated(ALBUM);
            br=br->getRelated(ALBUM_ARTIST);
            ret= br->getValue(0);
            break;
        }
        default:
        {
            if(!track->hasEntry(t) )
            {
                return QVariant();
            }
            ret=track->getValue(t);
        }
    }

    return ret;
}
/***********ENTRIES*********************
 
          albums.artist         as artist_id    ,
          albums.id                     as album_id             ,
          tracknumber                                           ,
          title                                                         ,
          albums.name           as album                ,
          artists.name          as artist               ,
          leadArtists.name      as leadArtist   ,
          comment                                                       ,
          genres.name           as genre                ,
          composers.name        as composer             ,
          length                                                        ,
          rating                                                        ,
          year                                                          ,
          bitrate                                                       ,
          path                                                          ,
          count 
*/
bool database::dbPrivate::trackViewRecord::hasEntry ( int t ) const
{
    using namespace Basic;
    if(t==ALBUM_ID)
    {
        return true;
    }
    if(t==ALBUM_ARTIST_ID)
    {
        return true;
    }
    
    if(t<0 || t> Basic::FRAME_NUM )
    {
        return false;
    }
    return true;
        
}

int database::dbPrivate::trackViewRecord::save()
{
    return track->save();
}

int database::dbPrivate::trackViewRecord::select()
{
    int ret= track->selectAll();
    if(ret==Basic::OK)
    {
        _isSelected=true;
    }
    return ret;
}

void database::dbPrivate::trackViewRecord::setValue ( int t, QVariant v )
{
    using namespace Basic;
    switch (t)
    {
        case LEAD_ARTIST:
        case ARTIST:
        case ALBUM:
        case GENRE:
        case COMPOSER:
        {
            baseRecord *br=track->getRelated(t);
            br->setValue(0,v);
            break;
        }   
        case ALBUM_ID:
        {
            dbPrivate::baseRecord *br=track->getRelated(ALBUM);
            br->setId(v);
        }
        case ALBUM_ARTIST:
        {
            dbPrivate::baseRecord *br=track->getRelated(ALBUM);
            br=br->getRelated(ALBUM_ARTIST);
            br->setValue(0,v);
            break;
        }
        case ALBUM_ARTIST_ID:
        {
            dbPrivate::baseRecord *br=track->getRelated(ALBUM);
            br=br->getRelated(ALBUM_ARTIST);
            br->setId(v);
            break;
        }
        default:
        {
            if(track->hasEntry(t) )
            {
                track->setValue(t,v);
            }
        }
    }
}


bool database::dbPrivate::trackViewRecord::isSelected() const
{
    return _isSelected;
}

QSqlError database::dbPrivate::trackViewRecord::lastError()
{
    return track->lastError();
}

QString database::dbPrivate::trackViewRecord::lastErrorStr()
{
    return track->lastError().text();
}

void database::dbPrivate::trackViewRecord::setDatabase ( QSqlDatabase& d )
{
    track->setDatabase(d);
}

QString database::dbPrivate::trackViewRecord::table() const
{
    return QString("trackView");
}

database::dbPrivate::baseRecord* database::dbPrivate::trackViewRecord::getTrackRecord() const
{
    return track;
}

database::dbPrivate::baseRecord* database::dbPrivate::trackViewRecord::getAlbumRecord() const
{
    return track->getRelated(Basic::ALBUM);
}

void database::dbPrivate::trackViewRecord::clearNewValue()
{
    track->clearNewValue();
}

QString database::dbPrivate::trackViewRecord::path ( QSqlRecord& r )
{
    return r.value(Basic::PATH+2).toString();
}

int database::dbPrivate::trackViewRecord::updateRecord ( QSqlRecord& r )
{
    QString path=r.value(Basic::PATH+2).toString();
    {
        if(path.isEmpty())
        {
            return Basic::DBERR;
        }
    }
    
    track->clearData();
    
    setValue(Basic::ALBUM_ARTIST_ID,r.value(0) );
    setValue(Basic::ALBUM_ID,r.value(1) );
    
    for(int i=0;i<Basic::FRAME_NUM;i++)
    {
        setValue(i,r.value(i+2));
    }
    _isSelected=true;
    return Basic::OK;
    
}
