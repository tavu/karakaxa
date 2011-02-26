#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include<QDirIterator>
#include<QSqlQuery>
#include<QFileInfoList>
#include"libraryImporter.h"
#include<QThread>
#include <player.h>
#include<QDir>
#include <kdirlister.h>
#include"albumEntry.h"
class scanTread :public  QThread//, public QObject
{
    Q_OBJECT
    public:
	scanTread();

	int importedItemNum();
	inline bool isStoped()
	{
	    return stopped;
	}
	inline int importedNum()
	{
	    return filesImported;
	}
	QByteArray albumKey(albumEntry e);

    protected:
	void run();
	
	QMap<QString,QString> images;
	QMap<int, albumEntry> albums;
	QString image(albumEntry &al);
	
	QHash<int,int> allAlbums;
	
	
    private:
	libraryImporter importer;
	bool scanFolder(KUrl url);

	void findItemN(QString);
	int itemNumber;
	int num;
	int filesImported;
	bool stopped;
	
	
    signals:
	void done(int);
	void itemsNum(const int);
	void imported(const int);
	void canceled(int);
	void error(QString);
    // 	  void item(const int);
    public slots:
	void stop();
};

#endif
