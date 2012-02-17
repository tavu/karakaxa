#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include<QAbstractListModel>
#include"../../core/playlist/playlist.h"

namespace views
{

class playlistModel :public  QAbstractListModel
{    
    Q_OBJECT
    public:
        playlistModel(QObject* parent = 0);
        ~playlistModel();
        QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
        int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
        int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
        virtual void setPlaylist(core::playlist *playlist);
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
        bool setData( const QModelIndex & index, const QVariant & value, int role);
        bool dropMimeData ( const QMimeData * data,Qt::DropAction action,int row, int column, const QModelIndex &parent);
        Qt::DropActions supportedDropActions () const;

        QStringList mimeTypes () const
        {
            QStringList l;
            l<<"text/uri-list";
            return l;
        }

    public slots:
        void updateData();

    protected:
        core::playlist *pl;
        void connectPl();

    protected slots:
        void beginInsertTracks(int first,int size)
        {
            beginInsertRows(QModelIndex(),first,first+size-1);
        }
        void endInsertTracks()
        {
            endInsertRows();
        }
        void beginRemoveTracks(int first,int size)
        {
            beginRemoveRows(QModelIndex(),first,first+size-1);
        }
        void endRemoveTracks()
        {
            endRemoveRows();
        }
        void beginMoveTracks(int first,int size,int dest)
        {
            beginMoveRows(QModelIndex(),first,first+size-1,QModelIndex(),dest);
        }
        void endMoveTracks()
        {
            endMoveRows();
        }
        void beginClear()
        {
            beginResetModel ();
        }
        void endClear()
        {
            endResetModel();
        }
};

}//namespace
#endif 