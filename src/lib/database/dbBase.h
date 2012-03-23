#ifndef DBBASE_H
#define DBBASE_H
#include<QMutex>
#include<QObject>
#include<QSqlDatabase>

namespace database
{

//this is tha basic class of the database classes.
//it provides some importand functions and lock possibilities

class dbBase :public QObject
{
    protected:
        dbBase(QObject *parent=0) :QObject(parent){};
        
        static void lock()
        {
            mutex.lock();
        }
        static void unlock()
        {
            mutex.unlock();
        }

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