#ifndef DATABASE_H
#define DATABASE_H
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QMessageBox>
#include<QObject>
#include "playerNamespace.h"
// #include"../nowPlayList/nplTrack.h"
namespace player
{
class database :public QObject
{
    Q_OBJECT
    public:
	database();
	~database();
	QSqlDatabase getDatabase();
	QStringList getLibraryFolders();


	const QString error();
	QSqlDatabase clone(const QString &s);
	QStringList getArtists(const QString &path);
		

	int trackViewHideValues();
	const QSqlQuery artist();
	const QSqlQuery artist(QString search);
	const QString trackTable();

	void addLibraryFolder(QString s);
	void removeLibraryFolder(QString s);
	
	
	QSqlQuery albumQuery(QString artist);
	QSqlQuery albumQuery(QString artist,QString search);

	inline void changedSig()
	{
	    emit(changed() );
	}
	
	inline void updateSig(tagsEnum t)
	{
	    emit(updated(t) );
	}
	
	
	static void toSqlSafe(QString &s);	
	bool createConnection();
	void readSettings();
	void writeSettings();
	
// 	
	inline QString dataBName()
	{
	    return dbName;
	}
	
	inline QString dataBUser()
	{
	    return dbUser;
	}
	
	inline QString dataBPass()
	{
	    return dbPass;
	}
	void init();
	bool dBConnect(QString n,QString u,QString p);
	
  private:

	QSqlDatabase db;
	QString dbName;
	QString dbUser;
	QString dbPass;
	
	bool isConnected;


    signals:
	void changed();
	void updated(tagsEnum);
};

}
#endif
