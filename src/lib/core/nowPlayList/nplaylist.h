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
#include"nplAbstractModel.h"
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
class nplAbstractModel;

class nplaylist :public playlist
{
    Q_OBJECT

    friend class soundEngine;
    friend class nplAbstractModel;

    public:
        const static int ADD;
        const static int REMOVE;
        const static int CLEAR;

        nplaylist();
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

        int         getPlayingPos() const
        {
            return trackList.indexOf(playing,0);
        }
        
        inline void setModel(core::nplAbstractModel *model)
        {
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

	
    private:

        int totalLength;
        nplPointer playing;
        nplPointer prevTrack;

        bool circle;
        bool rememberPl;
        
        QString next();
        QString playUrl(int n);
        QString previous();


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
	
};

    extern nplaylist *npList;
    
};


#endif
