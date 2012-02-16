#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<QObject>
#include"../nowPlayList/nplTrack.h"
#include <QEvent>

namespace core
{
    
class playlist :public QObject
{
    Q_OBJECT
    public:
        
        playlist(QObject *parent=0):QObject(parent){};
        virtual nplPointer item(int pos) const
        {
            if(pos<0 || pos>=trackList.size() )
            {
                return nplPointer();
            }
            
            return trackList[pos];                
        }

        virtual int size() const
        {
            return trackList.size();
        }

        
    public slots:
        void insert(int pos,nplPointer p);
        void insert(int pos,nplList l);
        void remove(int pos);
        void remove(int pos,int num);
        void move(int pos,int dest);
        void move(int pos,int num,int dest);
        void clear();

    protected:

        /*classes*/
        class insertEv;
        class removeEv;
        class moveEv;
        class clearEv;
        

        /*EVENTS*/
        virtual void insertEvent(insertEv *event);
        virtual void removeEvent(removeEv *event);
        virtual void moveEvent(moveEv *event);
        virtual void clearEvent(clearEv *event);

        virtual void customEvent (QEvent * event);


        nplList trackList;
        
    signals:
        //the first argument is tha possition and the second the number of new items.
        void aboutToInsertTracks(int,int);
        void tracksInserted(int,int);
        //the first argument is tha possition and the second the number of entries.
        void aboutToRemoveTracks(int,int);        
        void tracksRemoved(int,int);
         //the first argument is tha possition the second the number of entries and the thierd the destination.
        void aboutToMoveTrack(int,int,int);
        void tracksMoved(int ,int,int);

        void aboutToClear();
        void cleared();
        

    protected:

        enum plEvents
        {
            INSERT_EVENT=QEvent::User+1,
            REMOVE_EVENT,
            MOVE_EVENT,
            CLEAR_EVENT
        };
        
        class insertEv :public QEvent
        {
            public:                
                insertEv(int pos,nplList l)
                :QEvent( (QEvent::Type)INSERT_EVENT ),_pos(pos),_list(l)
                {}

                int pos()
                {
                    return _pos;
                }

                nplList list()
                {
                    return _list;
                }
            private:
                int _pos;
                nplList _list;
        };

        class removeEv :public QEvent
        {
            public:
                removeEv(int p,int n)
                :QEvent( (QEvent::Type)REMOVE_EVENT ),
                 _pos(p),_num(n)
                {}

                int pos()
                {
                    return _pos;
                }

                int num()
                {
                    return _num;
                }
            private:
                int _pos;
                int _num;
        };

        class moveEv :public QEvent
        {
            public:
                moveEv(int pos,int num,int dest)
                :QEvent( (QEvent::Type)MOVE_EVENT ),
                _pos(pos),_num(num),_dest(dest)
                {}

                int pos()
                {
                    return _pos;
                }

                int num()
                {
                    return _num;
                }

                int dest()
                {
                    return _dest;
                }
            private:                
                int _pos;
                int _num;
                int _dest;                
        };
        
        class clearEv :public QEvent
        {
            public:
                clearEv() :QEvent( (QEvent::Type)CLEAR_EVENT )
                {}
        };
};



}

#endif
