#ifndef TRACK_RECORD_H 
#define TRACK_RECORD_H
#include<QString>
namespace audiofiles
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

};

#endif
