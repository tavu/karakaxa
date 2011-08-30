#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QMessageBox>
#include<QObject>

#include"../files/audioFile.h"

namespace core
{
// class editMultFiles;

class database :public QObject
{    
    Q_OBJECT
    public:
 	friend class audioFiles::audioFile;
// 	static int DBCHANGED;
      
	database();
	~database();
	QSqlDatabase getDatabase();
	void closeDatabase(QSqlDatabase& dbase);
	void closeDatabase();
	
	QStringList getLibraryFolders();


	const QString error();
// 	QSqlDatabase clone(const QString &s);
// 	QStringList getArtists(const QString &path);
		
	const QString trackTable();

	void addLibraryFolder(QString s);
	void removeLibraryFolder(QString s);		

	
	QSqlQuery playlists();
	
	
	inline void changedSig()
	{
	    emit(changed() );
	}
	
	inline void updateSig(audioFiles::audioFile f)
	{
	    emit updated(f) ;
	}
	
	inline bool isConnected()
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
	
	bool _isConnected;
	
	QString apprName(QThread *thr);
	QMutex mutex;

    signals:
	void changed();
	void updated(audioFiles::audioFile);
};

extern database *db;
}
#endif
