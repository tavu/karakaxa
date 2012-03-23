#ifndef FILETODB
#define FILETODB

#include<fileTags.h>
#include<QSqlDatabase>
#include<QMutex>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
// #include"../core/database/database.h"
// #include<player.h>
// #include"playerNamespace.h"

// class audioFile;

#include<dbBase.h>

namespace database
{

class fileToDb :public dbBase
{
    public:
        fileToDb(QString path);
        ~fileToDb();

        int commit();

        int prepare();

        void setAlbumC(const QString &s)
        {
            _album=s;
        }

        void setArtistC(const QString &s)
        {
            _artist=s;
        }

        void setLeadArtistC(const QString &s)
        {
            _leadArtist=s;
        }

        void setAlbumIdC(const int id)
        {
            _albumId=id;
        }

        int setTag(int t,QVariant var);

    // 	void save();
        static QSqlRecord 	record(const QString path,int &err);
        QString			albumArt(const int albumId,int &err);



        int 			setAlbumArt(const int albumId,QString art);

        int 			end();

    private:
        int 	setTitle (const QString &s);
        int 	setArtist (const QString &s);
        int 	setAlbum (const QString &s);
        int 	setComment (const QString &s);
        int 	setLeadArtist(const QString &s);
        int	    setComposer(const QString &s);
        int 	setGenre (const QString &s);
        int 	setYear (const unsigned int &year);
        int 	setTrack (const unsigned int &i);
        int 	setRating(const unsigned int &rating);
        int 	setCounter(const unsigned int &num);

        bool    setAlbumArtist(const QString& artist, QSqlQuery& q);
    
        QString     _path;
        QString     _album;
        QString     _artist;
        QString     _leadArtist;
        int 	    _albumId;
        int         tag;
        QVariant    value;

        QSqlDatabase    databs;

        static QMutex 	mutex;
      
        
};//class

};//namespace
#endif
