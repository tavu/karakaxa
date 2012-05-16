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
#include"dbJobs/dbJob.h"
#include "databaseEvent.h"

namespace database
{

class dbEvent;
class databaseConection :public QObject
{
    Q_OBJECT
    friend void cleanup();

    public:
        databaseConection();
        ~databaseConection();

        static void init();
        static databaseConection* instance()
        {
            return db;
        }

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

        dbJobP currentJob()
        {
            return currJob;
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

        QLinkedList<dbJobP>  jobs;
        dbJobP currJob;

        void nextJob();


        QString apprName(QThread *thr);
        QMutex mutex;

    signals:
        void changed();
        void updated(audioFiles::audioFile);
        //state changed (dbState old,dbState new)
        void stateCanged(dbState ,dbState);
        void newEvent(database::dbEventP);
        void newJob(database::dbJobP);

    public slots:
        void addJob(dbJobP j);

        dbJobP rescan();
        dbJobP update();

        void emitEvent(dbEventP e)
        {
            emit newEvent(e);
        }


    private slots:
        void jobFinished();
        void emitUpdated(audioFiles::audioFile f);
        void editMultFilesStart();
        void editMultFilesStop();

    private:
        static databaseConection *db;



};//class

inline databaseConection* db()
{
    return databaseConection::instance();
}



}//namespace
#endif
