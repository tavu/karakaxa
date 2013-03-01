#ifndef TABLES_H 
#define TABLES_H
#include<QString>
namespace database
{
    const QString albumTable = QString("albums");
    const QString trackTable = QString("tracks");
    const QString artistTable = QString ("artists");
    const QString genreTable = QString ("genres");
    const QString composerTable = QString("composers");
    const QString playlistTable = QString("playlists"); 
    const QString tracksViewTable= QString("trackView"); 
    const QString albumArtistTable= QString("artist_album"); 
}
#endif
