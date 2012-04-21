#include"abstractQuery.h"
#include<audioFiles.h>

QString database::abstractQuery::tagToSql(int t)
{
    using namespace audioFiles;

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
        case ALBUM_ID:
        {
            return QString("album_id ");
        }
    }
    return QString();
}