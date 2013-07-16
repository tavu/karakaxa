#include"dbSelectionStrings.h"
#include<Basic/tagsTable.h>
#include<QDebug>
QString database::selectionStr(int t)
{
  using namespace Basic;

    switch (t)
    {
        case ARTIST:
        case LEAD_ARTIST:
        case ALBUM_ARTIST:
        {
            return QString("artists.name,artists.image" );
        }        
        case ALBUM:
        {
            return QString("albumArtist.album,albumArtist.artist,albumArtist.image,albumArtist.artistImage " );
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
        case PATH:
        {
            return QString("trackView.path ");
        }
        case COUNTER:
        {
            return QString("trackView.count ");
        }        
        case FILES:
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
    }
    return QString();
}

QString database::viewsNames(int t)
{
  using namespace Basic;

    switch (t)
    {
        case FILES:
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
            return QString("trackView" );
        }
        case ARTIST:
        case LEAD_ARTIST:
        case ALBUM_ARTIST:
        {
            return QString("artists" );
        }
        case ALBUM:
        {
            return QString("albumArtist" );
        }        
    }
    return QString();
}

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
        case ALBUM_ARTIST:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(t,q.value(0));
            info.setProperty(IMAGE,q.value(1));
            return info;
        }        
        case ALBUM:
        {
            audioFiles::tagInfo info(t,q.value(0) );
            info.setProperty(ALBUM,q.value(0));
            info.setProperty(ALBUM_ARTIST,q.value(1));
            info.setProperty(IMAGE,q.value(2));
            info.setProperty(ARTIST_IMAGE,q.value(3));
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

QString database::joins(int t)
{
    using namespace Basic;
    switch (t)
    {
        case ARTIST:
        {
            return QString(" INNER JOIN trackView ON trackView.artists=artists.name ");
        }
        case ALBUM_ARTIST:
        {
            return QString(" INNER JOIN trackView ON trackView.albumArtist=artists.name ");
        }
        case LEAD_ARTIST:
        {
            return QString(" INNER JOIN trackView ON trackView.leadArtist=artists.name ");
        }
        case ALBUM:
        {
            return QString(" INNER JOIN trackView ON trackView.albumArtist=albumArtist.artist AND trackView.album=albumArtist.album ");
        }
        default:
        {
            return QString();
        }
    }
}

