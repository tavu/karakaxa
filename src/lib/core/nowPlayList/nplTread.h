#ifndef NPLTREAD_H
#define NPLTREAD_H

#include<QThread>
#include<QUrl>
#include"nplaylist.h"
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
	
	void addMedia(const QUrl &url);
	void addDirectory(const QUrl &url);
	void addPlaylist(const QUrl &url);
	void addSingleFile(const QUrl &url);
    void addSingleFile(nplPointer tr);
	void cleanUp();
	static bool trackLessThan(nplPointer a,nplPointer b);
	
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
