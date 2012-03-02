#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include<QAbstractListModel>
#include<QAbstractItemModel>
#include<set>
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

        core::playlist* playlist()
        {
            return pl;
        }
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
        bool setData( const QModelIndex & index, const QVariant & value, int role);
        bool dropMimeData ( const QMimeData * data,Qt::DropAction action,int row, int column, const QModelIndex &parent);
        Qt::DropActions supportedDropActions () const;

        QStringList mimeTypes () const;
//         QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
        QModelIndex parent ( const QModelIndex & index ) const;


    protected:
        core::playlist *pl;
        void connectPl();
        virtual void reorder(int r,const std::set<int> &rows);

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
        void beginMoveTracks(int first,int size,int dest);
        
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

        bool acceptDrops () const
        {
            return _acceptDrops;
        }
        void setAcceptDrops ( bool on )
        {
            _acceptDrops=on;
        }

    private:
        bool _acceptDrops;

};

}//namespace
#endif 
