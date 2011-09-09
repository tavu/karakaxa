#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include<QDirIterator>
#include<QSqlQuery>
#include<QFileInfoList>
#include"libraryImporter.h"
#include<QThread>
#include<QProgressBar>
#include<QDir>
#include <kdirlister.h>
#include "database.h"
#include"album.h"
#include <QLabel>

namespace core
{
class scanThread :public  QThread//, public QObject
{
    Q_OBJECT
    public:
	scanThread(QObject *parent);

	int importedItemNum();
	inline bool isStoped()
	{
	    return stopped;
	}
	inline int importedNum()
	{
	    return filesImported;
	}
		
	void scan()
	{
	    start();
	}
	
	QWidget *widget();

	void setDirs(const QStringList &l);
	
    protected:
	void run();

	QLinkedList<KUrl> dirs;
	
	QHash<int,int> allAlbums;
	QLinkedList<QString> errors;
	int _step;	
	
    private:
	libraryImporter importer;
	bool scanFolder(KUrl url);

	void findItemN(KUrl);

	void initWidget();
	
	int itemNumber;
	int num;
	int filesImported;
	bool stopped;
	
	QWidget *w;
	QLabel *label;
	QProgressBar *progressBar;
	
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

};

#endif
