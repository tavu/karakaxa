#ifndef TRACK_RECORD_H 
#define TRACK_RECORD_H
#include<QString>
namespace database
{

struct trackRecord
{
    int artistId;
    int albumId;
    int number;
    QString title;
    QString album;
    QString artist;
    QString leadArtist;
    QString comment;
    QString genre;
    QString composer;
    int lenght;
    int rating;
    int year;
    int bitrate;
    QString path;
    int count;
};

struct albumArtistRecord
{
    QString artist;
    QString album;
    QString albumArt;
    int albumId;
    int artistId;
    QString artistFoto;
};

};

#endif
