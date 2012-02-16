#ifndef FILEPLAYLISTMODEL_H
#define FILEPLAYLISTMODEL_H
#include "playlistModel.h"
#include<QThread>
#include"../../core/playlist/filePlaylist.h"

namespace views
{
class filePlaylistModel :public playlistModel
{
    Q_OBJECT
    public:
        filePlaylistModel(QObject *parent=0);
        virtual void setPlaylist(core::playlist *playlist);
        void setPlPath(const QString &s)
        {
            core::filePlaylist *pl=core::getPlaylist(s);
            setPlaylist(pl);
            pl->load();
        }
        bool dropMimeData ( const QMimeData * data,Qt::DropAction action,int row, int column, const QModelIndex &parent)
        {
            bool b=playlistModel::dropMimeData(data,action,row,column,parent);
            if(b)
            {
                qDebug()<<"save";
                static_cast<core::filePlaylist*>(pl)->save();
            }
            return b;
        }
        
    protected slots:
        void updateData(int,int);

    protected:
        class playlistThr :public QThread
        {
            public:
                playlistThr(QObject * parent = 0)
                    :QThread(parent)
                {}
                core::playlist *pl;
                void run();
                void cancel()
                {
                    canceled=true;
                }
                int row;
                int num;
                
                bool canceled;
        };

        playlistThr *thr;

};//class

}//namespace

#endif