#ifndef DBBASE_H
#define DBBASE_H
#include<QMutex>
#include<QObject>
#include<QSqlDatabase>
// #include"database.h"

namespace database
{

//this is tha basic class of the database classes.
//it provides some importand functions and lock possibilities

class dbBase :public QObject
{
    public:
        dbBase(QObject *parent=0) :QObject(parent){};
        virtual ~dbBase(){};
        
        static void lock()
        {
            mutex.lock();
        }
        static void unlock()
        {
            mutex.unlock();
        }
        
        void getDb();
		
        void closeDb();
        
        QVariant getId(QVariant var,const QString &table);
        /*variables: 
            album:the name of the album
            artist:the id of the artist
            table:the name of the database table of the albums
        */
        QVariant getAlbumId(QVariant album,int artistId,const QString &table);
        

        void            cleanUp();
        void            clearArtist();
        void            clearAlbum();
        void            clearGenre();
        void            clearComposer();
        
    protected:
        QSqlDatabase    databs;
        
    private:
        static QMutex mutex;
};


};
#endif