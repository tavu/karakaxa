#ifndef DATABASEEVENT_H
#define DATABASEEVENT_H
#include<QStringList>
#include<QSharedPointer>
#include <audioFile.h>
/*
 * Database events are classes inherits the dbEvent witch are be sending from dbConnection throw signals.
 * The purpose of these classes is to inform the resevers about any accion that occured in the database. 
 * This event are absolutely irrelevant to the  qt events
 */
namespace database
{

enum dbEvents
{
    FILES_INS=1,    //files inserted
    FILES_REM,      //files removed
    FILES_CHANG,     //some files have changed its tags.
    RESCAN_COMP,    //rescan completed
    UPDATE_COMP,    //update completed
    NEW_PL,         //new playlist added
    PL_REM,         //some playlists are removed from the library
    NEW_LF,         //a new folder has be inserted to the library
    LF_REM,         //a folder has removed from the library
    NEW_CONN,        //we connected to a new database
    ANY             //anything else
};

class dbEvent :public QObject
{
    Q_OBJECT
    public:
        dbEvent(int t) :QObject()
        {
                _type=t;
        };

        virtual ~dbEvent(){}
        
        int type()
        {
            return _type;
        }

        QStringList urls;

    private:
        int _type;
};

class dbEventAF :public dbEvent
{
    Q_OBJECT
    public:
        dbEventAF() :dbEvent(FILES_CHANG) {};        

        QLinkedList<audioFiles::audioFile> files;

};


typedef QSharedPointer<dbEvent> dbEventP;

}//namespace
#endif