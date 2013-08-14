#include"dbSelectionStrings.h"
#include<Basic/tagsTable.h>
#include<QDebug>
#include <QSet>
#include"queryProvider.h"



audioFiles::tagInfo database::infoFromQuery(int t, const QSqlQuery& q)
{
    using namespace Basic;

    switch (t)
    {
        case COMPOSER:        
        case TITLE:
        case GENRE:
        case COMMENT:
        case TRACK:
        case LENGTH:
        case YEAR:
        case BITRATE:
        case RATING:
        case PATH:
        case COUNTER:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(t,q.value(0));
            return info;
        }
        case ARTIST:
        case LEAD_ARTIST:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(t,q.value(0));
            info.setProperty(IMAGE,q.value(1));
            return info;
        }        
        case ALBUM_ARTIST:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(ALBUM_ARTIST,q.value(0));
            return info;
        }
        case ALBUM:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(ALBUM,q.value(0));
            info.setProperty(ALBUM_ARTIST,q.value(1));
            info.setProperty(IMAGE,q.value(2));
            return info;
        }
        case FILES:
        {
            audioFiles::tagInfo info(t,QVariant() );
            info.setProperty(TRACK,q.value(0));
            info.setProperty(TITLE,q.value(1));
            info.setProperty(ARTIST,q.value(2));
            info.setProperty(LEAD_ARTIST,q.value(3));
            info.setProperty(ALBUM,q.value(4));
            info.setProperty(ALBUM_ARTIST,q.value(5));
            info.setProperty(COMMENT,q.value(6));
            info.setProperty(GENRE,q.value(7));
            info.setProperty(COMPOSER,q.value(8));
            info.setProperty(LENGTH,q.value(9));
            info.setProperty(RATING,q.value(10));
            info.setProperty(YEAR,q.value(11));
            info.setProperty(BITRATE,q.value(12));
            info.setProperty(PATH,q.value(13));
            info.setProperty(COUNTER,q.value(14));
            return info;
        }
    }
    return audioFiles::tagInfo();
}


QString database::tagFromSql(QString table, int tag)
{
    if(table.compare("albumArtist")==0 )
    {
        if(tag==Basic::ALBUM_ARTIST)
            return table + QString(".artist ");
        
        if(tag==Basic::ALBUM)
            return table + QString(".album ");
    }

    if(table.isEmpty() || table.compare("trackView")==0 )
        return tagFromTrackView(tag);        
    
    
    return table +QString(".name");
}

QString database::tagFromTrackView(int t)
{
    using namespace Basic;

    switch (t)
    {
        case ARTIST:
        {
            return QString("trackView.artist " );
        }
        case ALBUM:
        {
            return QString("trackView.album " );
        }
        case TITLE:
        {
            return QString("trackView.title " );
        }
        case COMPOSER:
        {
            return QString("trackView.composer " );
        }
        case GENRE:
        {
            return QString("trackView.genre ");
        }
        case COMMENT:
        {
            return QString("trackView.comment ") ;
        }
        case TRACK:
        {
            return QString("trackView.tracknumber ");
        }
        case YEAR:
        {
            return QString("trackView.year ");
        }
        case LENGTH:
        {
            return QString("trackView.length ");
        }
        case RATING:
        {
            return QString("trackView.rating ");
        }
        case BITRATE:
        {
            return QString("trackView.bitrate ");
        }
        case LEAD_ARTIST:
        {
            return QString("trackView.leadArtist " );
        }
        case PATH:
        {
            return QString("trackView.path ");
        }
        case COUNTER:
        {
            return QString("trackView.count ");
        }
//         case ALBUM_ID:
//         {
//             return QString("album_id ");
//         }
        case ALBUM_ARTIST:
        {
            return QString("trackView.albumArtist ");
        }
    }
    return QString();
}

QString database::selectionStr(int tag,const abstractQuery *q,QString &table)
{
    using namespace Basic;
    
    QString join;
    QSet<int> filters;
    
    if(q!=0)
    {
        QList<int>tags=q->tags();
        foreach(int tag , tags)
        {
            filters.insert(tag);
        }
    }
    
    if(tag==ALBUM || tag==ALBUM_ARTIST )
    {
        table=QString("albumArtist");
        filters.remove(ALBUM);
        filters.remove(ALBUM_ARTIST);
        if(filters.size()!=0)
        {
            join=QString(" INNER JOIN trackView ON trackView.albumArtist=albumArtist.artist AND trackView.album=albumArtist.album ");
        }
        
    }
    else
    {
        filters.remove(tag);
        if(filters.size()==0)
        {
            table=tableName(tag);
        }
        else
        {
            table=QString("trackView");
        }
    }
    
    if(table.isEmpty())
        return QString();
    
//     if(q!=0)
//         q->setTable(table);
    
    QString selCol=selectionColumns(table,tag);
    
    if(selCol.isEmpty())
        return QString();
    
    QString ret="SELECT "+selCol+" FROM "+table;
    
    if(!join.isEmpty())
        ret+=join;

    return ret;
}

QString database::selectionColumns(QString table ,int tag)
{
    using namespace Basic;
    if(tag==ALBUM)
    {
        return QString("albumArtist.album,albumArtist.artist,albumArtist.image " );
    }
     
    if(tag==ALBUM_ARTIST)
    {
        return QString("albumArtist.artist " );
    }
    
    if(tag==FILES)
    {
        return QString("trackView.tracknumber, \
                            trackView.title, \
                            trackView.artist, \
                            trackView.leadArtist, \
                            trackView.album, \
                            trackView.albumArtist, \
                            trackView.comment, \
                            trackView.genre,  \
                            trackView.composer, \
                            trackView.length, \
                            trackView.rating, \
                            trackView.year, \
                            trackView.bitrate, \
                            trackView.path, \
                            trackView.count \
                          ");
    }
    
    if(table.compare("trackView")==0)    
        return tagFromTrackView(tag);
    
    return table +QString(".name");
    
    
}

QString database::tableName(int tag)
{
    using namespace Basic;
    switch (tag)
    {
        case ARTIST:
        {
            return QString("artists" );
        }
        case ALBUM:
        {
            return QString("albums" );
        }
        case TITLE:
        {
            return QString("trackView" );
        }
        case COMPOSER:
        {
            return QString("composers" );
        }
        case GENRE:
        {
            return QString("genres");
        }
        case COMMENT:
        {
            return QString("trackView") ;
        }
        case TRACK:
        {
            return QString("trackView");
        }
        case YEAR:
        {
            return QString("trackView");
        }
        case LENGTH:
        {
            return QString("trackView");
        }
        case RATING:
        {
            return QString("trackView");
        }
        case BITRATE:
        {
            return QString("trackView");
        }
        case LEAD_ARTIST:
        {
            return QString("trackView" );
        }
        case PATH:
        {
            return QString("trackView");
        }
        case COUNTER:
        {
            return QString("trackView");
        }
        case ALBUM_ARTIST:
        {
            return QString("albumArtist");
        }
    }
    return QString();
}