#ifndef NPLAYLIST_H
#define NPLAYLIST_H

// #include"nplTrack.h"
#include<QList>
// #include<player.h>
#include"nplClass.h"

#include<QThread>
#include<QMutex>
#include"nplTrack.h"

#include<QSharedPointer>
#include"../engine/engine.h"
#include"../config/config.h"
#include"../playlist/playlist.h"
/*
This class creates a list tha saves the track that is about to be played.
Every track is represented by a nplTrack poinder.
nplaylist deletes tha poinder on removeTrack
NEVER delete it outside.
*/
// typedef QSharedPointer<nplTrack> nplPointer;




namespace core
{
void cleanUp();

class nplaylist :public playlist
{
    Q_OBJECT
    friend void core::cleanUp();
    friend class soundEngine;

    public:
        const static int ADD;
        const static int REMOVE;
        const static int CLEAR;
        
        ~nplaylist();

        nplPointer  getTrack(int pos) const
        {
            return item(pos);
        }

        void        addMediaList(const QList <QUrl> &urlList,int pos);
        void        addMediaList(const QStringList &list,int pos);
        QString     url(int n) const;
        bool        isPlaying(const int pos) const;
        QStringList getList() const;
        int         getLength() const;
        nplPointer  getPlayingTrack() const;
        void        clearEvent(clearEv *event);
        
        int         getPlayingPos() const
        {
            return trackList.indexOf(playing,0);
        }

        bool rememberPlaylist() const
        {
            return rememberPl;
        }

        void setRememberPlaylist(bool b);


        void loadSavedPlaylist();

        void setRepeat(bool repeat)
        {
            circle=repeat;
            emit repeatChanged(circle);
        }

        bool repeat()
        {
            return circle;
        }

        static void init()
        {
            if(npList==0)
            {
                npList=new nplaylist;
            }
        }

        static nplaylist* instance()
        {
            return npList;
        }

    private:

        nplaylist();

        int totalLength;
        nplPointer playing;
        nplPointer prevTrack;

        bool circle;
        bool rememberPl;
        
        QString next();
        QString playUrl(int n);
        QString previous();

        static nplaylist* npList;
        static void cleanUp()
        {
            delete npList;
        }

    signals:
        void cancelThreads();
        void repeatChanged(bool);

    public slots:

        void repeatToggle()
        {
            setRepeat(!circle);
        }

        void duplicate(const int pos);
        void suffle();

    private slots:
        void prepareToQuit();
        void informTrack();
        void updateLengthInsert(int,int);
        void updateLengthRemove(int,int);
	
};

inline nplaylist* npList()
{
    return nplaylist::instance();
}
    
};


#endif
