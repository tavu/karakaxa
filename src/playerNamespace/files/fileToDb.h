#ifndef FILETODB
#define FILETODB

#include"fileTags.h"
#include<QSqlDatabase>
#include<QMutex>
#include<QSqlQuery>
#include<QSqlError>
// #include<player.h>
#include"playerNamespace.h"

namespace player
{

class fileToDb
{
public:

    const static int OK;
    const static int DBERR;
    const static int NOTINDB;


    static int 	setTitle (const QString path,const QString &s);
    static int 	setArtist (const QString path,const QString &s,const QString &album);
    static int 	setAlbum (const QString path,const QString &s);
    static int 	setComment (const QString path,const QString &s);
    static int 	setLeadArtist (const QString path,const QString &s,const QString &artist,const QString &album);
    static int	setComposer(const QString path,const QString &s);
    static int 	setGenre (const QString path,const QString &s);
    static int 	setYear (const QString path,const unsigned int &year);
    static int 	setTrack (const QString path,const unsigned int &i);
    static int 	setRating(const QString path,const unsigned int &rating);
    static int 	setCounter(const QString path,const unsigned int &num);
    static int 	setAlbumArt(const int albumId,QString art);

    static QSqlRecord 	record(const QString path,int &err);
    static QString	 albumArt(const int albumId,int &err);
private:
    static bool setAlbumArtist(const QString &path,const QString &s,const QString &album,QSqlQuery &q);
};//class

};//namespace
#endif
