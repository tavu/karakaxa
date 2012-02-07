#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include<QAbstractListModel>
#include<core.h>
#include<QThread>
// #include"../trackUrl.h"
using namespace core;
class playlistModel :public  QAbstractListModel
{      
    Q_OBJECT
    public:
        playlistModel(QObject* parent = 0);
        ~playlistModel();
        QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
        int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
        int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
        void setPlPath(const QString &s);
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        void contextMenuEvent(QContextMenuEvent *e);
    
        virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
        bool setData( const QModelIndex & index, const QVariant & value, int role);
        bool dropMimeData ( const QMimeData * data,Qt::DropAction action,int row, int column, const QModelIndex &parent);
        Qt::DropActions supportedDropActions ();

    public slots:
        void updateData();

    private:
        core::filePlaylist *pl;
	

    class playlistThr :public QThread
    {
        public:
            playlistThr(QObject * parent = 0)
                :QThread(parent)
            {}
            core::filePlaylist *pl;
            void run();
            void cancel()
            {
                canceled=true;
            }
            bool canceled;
    };

  playlistThr *thr;
};
#endif