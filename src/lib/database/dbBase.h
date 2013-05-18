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
        
        //returns the new appropriate id from the table acording the value of var;
        //it is possible to make some changes to value(as simplified the string)
        //after return the Qvarian var contains the actual value of that field of the table
        
        QVariant getId(QVariant &var,const QString &table,bool *inserted=0);

        QVariant getAlbumId(QVariant &album,int artistId,const QString &table,bool *inserted=0);
        
        void            cleanUp();
        void            clearArtist();
        void            clearAlbum();
        void            clearGenre();
        void            clearComposer();
        
//         static trackRecord* fromSqlRecord(const QSqlRecord &r);
        
    protected:
        QSqlDatabase    databs;
        
    private:
        static QMutex mutex;
};


};
#endif