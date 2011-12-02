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
typedef QList<nplPointer> nplList;
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
        ~nplaylist();

        nplPointer  getTrack(int pos);
        void        addMediaList(const QList <QUrl> &urlList,int pos);
        void        addMediaList(const QStringList &list,int pos);
        QString     url(int n);
        bool        isPlaying(const int pos);
        QStringList getList();
        int         getLength();
        nplPointer  getPlayingTrack();

        int         getPlayingPos()
        {
        return trackList.indexOf(playing,0);
        }

        int size();
        inline void setModel(core::nplAbstractModel *model)
        {
            this->model=model;
        }


        bool rememberPlaylist()
        {
            return rememberPl;
        }

        void setRememberPlaylist(bool b)
        {
            rememberPl=b;
            KSharedConfigPtr config=core::config->configFile();
            KConfigGroup group( config, "nowPlaylist" );
            group.writeEntry( "rememberPl", QVariant(rememberPl));
            group.config()->sync();
        }

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

        nplAbstractModel *model;

        int totalLength;
        nplList trackList;
        nplPointer playing;
        QMutex mutex;
        bool circle;

        QString next();
        QString playUrl(int n);
        QString previous();

        bool rememberPl;
	

    signals:
        void insertSig(nplList,int );
        void removeSig(const int);
        void cancelThreads();

        void inserted(int);
        void removed(int);
        void cleared();

        void repeatChanged(bool);

    public slots:
        void insert(nplList list,int pos);
        void move(int from,int pos);
        void remove(const int);
        void clear();

        void repeatToggle()
        {
            setRepeat(!circle);
        }
        void duplicate(const int pos);
        void suffle();

    private slots:
        void prepareToQuit();

        void insertSlot(nplList list,int pos);
        void removeSlot(const int);
        void informTrack();
	
};

    extern nplaylist *npList;
    
};


#endif
