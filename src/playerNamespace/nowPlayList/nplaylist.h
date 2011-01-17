#ifndef NPLAYLIST_H
#define NPLAYLIST_H

// #include"nplTrack.h"
#include<QList>
#include<player.h>
#include"nplClass.h"

#include<QThread>

#include<QSharedPointer>
#include"../myPointer.h"
#include"nplAbstractModel.h"
/*
This class creates a list tha saves the track that is about to be played.
Every track is represented by a nplTrack poinder.
nplaylist deletes tha poinder on removeTrack
NEVER delete it outside.
*/
// typedef QSharedPointer<nplTrack> nplPointer;

class nplAbstractModel;

typedef QList<nplPointer> nplList;
namespace player
{

class nplaylist :public QObject
{
    Q_OBJECT

    

    friend class soundEngine;
    friend class nplAbstractModel;

    public:
	const static int ADD;
	const static int REMOVE;
	const static int CLEAR;

	nplaylist();

	nplPointer getTrack(int pos);
	void addMediaList(const QList <QUrl> &urlList,int pos);
	void addMediaList(const QStringList &list,int pos);
	QString url(int n);
	bool isPlaying(const int pos);
	QStringList getList();
	int getLength();
	nplPointer getPlayingTrack();
	int size();
	inline void setModel(nplAbstractModel *model)
	{
	    this->model=model;
	}
	
    private:

	nplAbstractModel *model;
      
	int totalLength;
	nplList trackList;
	nplPointer playing;
	QMutex mutex;
	bool circle;

	QString next();
	QString playUrl(int n);
	QString previous();

	

    signals:
	void insertSig(nplList,int );
	void removeSig(const int);

    public slots:

	void insert(nplList list,int pos);
	void move(int from,int pos);
	void remove(const int);
	void clear();
	
	void duplicate(const int pos);
	void suffle();

    private slots:
	void insertSlot(nplList list,int pos);
	void removeSlot(const int);
};

};


#endif
