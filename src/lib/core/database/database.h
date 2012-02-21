#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QMessageBox>
#include<QObject>
#include"album.h"
#include"dbTypes.h"

#include"../files/audioFile.h"
#include"databaseScanner.h"
namespace core
{
class databaseScanner;

class database :public QObject
{    
    Q_OBJECT
    public:        
        friend class audioFiles::audioFile;
    
    
      
        database();
        ~database();
        
        QSqlDatabase getDatabase();
        void closeDatabase(QSqlDatabase& dbase);
        void closeDatabase();
        
        const QString error();
        const QString trackTable();

        
        QStringList getLibraryFolders();
        void addLibraryFolder(QString s);
        void removeLibraryFolder(QString s);

        QSqlQuery playlists();


        void changedSig()
        {
            emit(changed() );
        }

        void updateSig(audioFiles::audioFile f)
        {
            emit updated(f) ;
        }

        bool isConnected()
        {
            return db.isOpen();
        }		
	
	
        static void toSqlSafe(QString &s);	
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

        QSqlDatabase db;
        QString dbName;
        QString dbUser;
        QString dbPass;

        bool    _isConnected;
        bool    _isScanning;
        dbState    _state;

        QLinkedList<dbScanner>  scanners;

        void nextState();

        QString apprName(QThread *thr);
        QMutex mutex;

    signals:
        void changed();
        void updated(audioFiles::audioFile);
        //state changed (dbState old,dbState new)
        void stateCanged(dbState ,dbState);

    public slots:
        void scan(core::databaseScanner *sc);


    private slots:
        void scanFinished();
};

extern database *db;
}
#endif
