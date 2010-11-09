#ifndef NPLAYLIST_H
#define NPLAYLIST_H

// #include"nplTrack.h"
#include<QList>
#include<player.h>
#include"nplClass.h"

#include<QThread>

#include<QSharedPointer>
#include"../myPointer.h"
/*
This class creates a list tha saves the track that is about to be played.
Every track is represented by a nplTrack poinder.
nplaylist deletes tha poinder on removeTrack
NEVER delete it outside.
*/
// typedef QSharedPointer<nplTrack> nplPointer;

namespace player
{

class nplaylist :public QObject
{
    Q_OBJECT

    

    friend class soundEngine;

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
	
    private:

    // 	  int playingTr;
	int totalLength;

	QList<nplPointer> trackList;

	nplPointer playing;
	QMutex mutex;

	bool circle;

	QString next();
	QString playUrl(int n);
	QString previous();


    signals:
	void changed(int);

	void aboutToInsert(int);
	void aboutToClear(int );
	void aboutToRemove(int);

    public slots:

	bool insert(int pos,nplPointer tr);
	void move(int from,int pos);
	bool remove(const int);
	void clear();
	int size();
	void duplicate(const int pos);



};

};


#endif
