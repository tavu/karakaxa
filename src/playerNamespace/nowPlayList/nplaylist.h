#ifndef NPLAYLIST_H
#define NPLAYLIST_H

// #include"nplTrack.h"
#include<QList>
#include<player.h>
#include<nplTrack.h>

#include<QThread>

#include<QSharedPointer>
#include"../myPointer.h"
/*
This class creates a list tha saves the track that is about to be played.
Every track is represented by a nplTrack poinder.
nplaylist deletes tha poinder on removeTrack
NEVER delete it outside.
*/


namespace player
{

class nplaylist :public QObject
{
    Q_OBJECT

    typedef QSharedPointer<nplTrack> nplPointer;

    friend class soundEngine;

public:
    const static int ADD;
    const static int REMOVE;
    const static int CLEAR;

    nplaylist();
    bool append(nplTrack *tr);


    nplTrack* getTrack(int);

    void addMediaList(const QList <QUrl> &urlList,int pos);

    void addMediaList(const QStringList &list,int pos);

    QString url(int n);

    bool isPlaying(const int pos);

    bool isAudio(const QString &url);

    QStringList getList();
    int getLength();
private:

// 	  int playingTr;
    int totalLength;

    QList<nplPointer *> trackList;

    nplPointer* playing;
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


    bool addAudio(const QString &url,const uint pos);


    bool insert(int pos,nplTrack *tr);
    void move(int from,int pos);
    bool remove(const int);
// 	  bool remove(QList<int> &l);
    void clear();
    int size();
    void duplicate(const int pos);

//      private slots:

    //this class have the porpose of finding the file info and appending the now playlist



};

};


#endif
