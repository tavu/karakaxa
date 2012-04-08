#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QObject>
#include<QLinkedList>
#include<audioFile.h>
#include<QMutex>

#include"album.h"
#include"dbTypes.h"
#include"databaseScanner.h"
#include "databaseEvent.h"

namespace database 
{

class databaseConection :public QObject
{    
    Q_OBJECT    
    friend void init();
    friend databaseConection* db();

    public:
        databaseConection();
        ~databaseConection();
        
        QSqlDatabase getDatabase();
        void closeDatabase(QSqlDatabase& dbase);
        void closeDatabase();
        
        const QString error();

        void changedSig()
        {
            emit(changed() );
        }

        bool isConnected()
        {
            return dBase.isOpen();
        }

        bool createConnection();
        void readSettings();
        void writeSettings();

        QString dataBName()
        {
            return dbName;
        }

        QString dataBUser()
        {
            return dbUser;
        }

        QString dataBPass()
        {
            return dbPass;
        }
	
        bool dBConnect(QString n,QString u,QString p);
        void setUpDb();

        dbState state()
        {
            return _state;
        }

        //if its on the update or rescan state return the scanThread
        dbScanner scanner()
        {
            if(scanners.isEmpty() )
            {
                return dbScanner();
            }

            return scanners.first();
        }

    private:
        struct dBEntry
        {
            QString name;
            QThread *thr;
            int used;
        };
        QMap<QString,dBEntry*> dBMap;

        QSqlDatabase dBase;
        QString dbName;
        QString dbUser;
        QString dbPass;

        bool    _isConnected;
        bool    _isScanning;
        dbState    _state;
        dbEventP    editFiles;
        
        QLinkedList<dbScanner>  scanners;

        void nextState();
        

        QString apprName(QThread *thr);
        QMutex mutex;

    signals:
        void changed();
        void updated(audioFiles::audioFile);
        //state changed (dbState old,dbState new)
        void stateCanged(dbState ,dbState);
        void newEvent(database::dbEventP);

    public slots:
        void scan(databaseScanner *sc);
        void emitEvent(dbEventP e)
        {
            emit newEvent(e);
        }


    private slots:
        void scanFinished();
        void emitUpdated(audioFiles::audioFile f);
        void editMultFilesStart();
        void editMultFilesStop();

    private:
        static databaseConection *db;
        

    
};//class

inline databaseConection* db()
{
    return databaseConection::db;
}



}//namespace
#endif
