#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<QObject>
#include"../nowPlayList/nplTrack.h"

namespace core
{
    
class playlist :public QObject
{
    Q_OBJECT
    public:
        
        playlist(QObject *parent=0):QObject(parent){};

    public slots:
        virtual void insert(int pos,nplPointer p);
        virtual void insert(int pos,nplList l);
        virtual void remove(int pos);
        virtual void move(int from,int to);
        virtual void clear();

    public:
        virtual nplPointer item(int pos) const
        {
            if(pos>0 || pos<trackList.size() )
                return trackList[pos];
            else
                return nplPointer();
        }

        virtual int size() const
        {
            return trackList.size();
        }


    private:
        bool _emitSignals;
    protected:
        nplList trackList;

        bool emitSignals()
        {
                return _emitSignals;
        }

        void setEmitSignals(bool b)
        {
                _emitSignals=b;
        }

    signals:
        void aboutToInsertTrack(int);
        //the first argument is tha possition and the second the number of new items.
        void aboutToInsertTracks(int,int);
        void tracksInserted(int,int);
        void trackInserted(int);
        void aboutToRemoveTrack(int);
        void trackRemoved(int );
        void aboutToMoveTrack(int,int);
        void trackMoved(int ,int);

        void aboutToClear();
        void cleared();
};

}

#endif
