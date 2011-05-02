#ifndef NPLTREAD_H
#define NPLTREAD_H

#include<QThread>
#include<QUrl>
#include"nplaylist.h"
// #include<player.h>
// #include<playerNamespace.h>
#include<QProgressBar>
//this class have the porpose of finding the file info and appending the now playlist
using namespace core;
class nplTread :public  QThread//, public QObject
{
    Q_OBJECT
    public:
	nplTread();
	~nplTread();

	void setStringL(QStringList l);
	void setUrls(QList <QUrl> l);
	void setPos(int num);
	
	void addMedia(const QString &url);
	void addDirectory(const QString &url);
	void addPlaylist(const QString &url);
	void addSingleFile(const QString &url);
	void cleanUp();
	
    protected:
	void run();

    private:
	QList <QUrl> urlList;
	QStringList  sList;
	int pos;	


	
	QWidget *w;
	bool canceled;
	int size;
	
	nplList list;
	
    public slots:
	void cancel();
// 	void insert(int, nplTrack*);
// 	void added(int);

};

#endif
