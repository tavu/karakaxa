#ifndef FILETODB
#define FILETODB

#include<fileTags.h>
#include<QSqlDatabase>
#include<QMutex>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

#include"../dbBase.h"
#include"records.h"

namespace database
{

    
class fileToDb :public dbBase
{
    public:
        static trackRecord* record ( const QString &path,int &err );

        fileToDb ( QString path );
        ~fileToDb();

        void updateRecord(const QSqlRecord &r);
        
        int prepare();
        int end();

        int setTag ( int t,QVariant value );

        int albumId(int &err);
        QString albumArt (int &err );
        int     setAlbumArt (const QString &art );
        int selectAlbumArtist ();

        //static trackRecord record(const QString path,int &err);
        static trackRecord* fromSqlRecord(const QSqlRecord &r);
        
        int select();
        
        QVariant tag(int tag,int &err);
        
        int recordError()
        {
            return _recordError;
        }
        
        int albumArtistError()
        {
            return _albumArtistError;
        }

    private:
        int     setTitle ( const QString &s );
        int     setArtist ( const QString &s );
        int     setAlbum ( const QString &s,int artistId);
        int     setAlbum ( int albumId,QString albumArt=QString());
        int     setComment ( const QString &s );
        int     setLeadArtist ( const QString &s );
        int     setComposer ( const QString &s );
        int     setGenre ( const QString &s );
        int     setYear ( const unsigned int year );
        int     setTrack ( const unsigned int i );
        int     setRating ( const unsigned int rating );
        int     setCounter ( const unsigned int num );

        int    setAlbumArtist ( const QString &artist );
        int    setAlbumArtist ( int id );
        
        albumArtistRecord* getAlbumId2(const QString &album ,int artistId);
        
        albumArtistRecord *albumArtistFromRecord(const QSqlRecord &r);
        
        QString _path;
        trackRecord *_record;
        int _recordError;
        
        albumArtistRecord *_albumArtist;
        int _albumArtistError;

};//class

};//namespace
#endif
