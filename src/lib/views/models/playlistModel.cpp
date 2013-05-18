#include"playlistModel.h"
#include<views.h>
#include<core.h>
#include<Basic/tagsTable.h>
views::playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
    pl(0),
    _acceptDrops(true)
{
}
/*
QModelIndex views::playlistModel::index(int row, int column, const QModelIndex& parent) const
{
    if(row<0 || row>=rowCount() ||column<0|| column>=columnCount() || parent.isValid() )
    {
        return QModelIndex();
    }
    return createIndex(row,column);
}
*/

views::playlistModel::~playlistModel()
{
    if(pl!=0)
    {
        delete pl;
    }
}


int views::playlistModel::rowCount ( const QModelIndex & parent ) const
{
    if(parent.isValid() )
    {
        return 0;
    }

    if(pl==0)
    {
        return 0;
    }

    return pl->size();
}

int views::playlistModel::columnCount ( const QModelIndex & parent ) const
{
    Q_UNUSED(parent)
    return Basic::FRAME_NUM;
}

QModelIndex views::playlistModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}


QStringList views::playlistModel::mimeTypes() const
{
    QStringList l;
    if(_acceptDrops)
    {
        l<<"text/uri-list";
    }
    return l;
}


QVariant views::playlistModel::data(const QModelIndex & index, int role ) const
{
    if(!index.isValid() || pl==0)
    {
        return QVariant();
    }

    core::nplPointer p=pl->item(index.row());
    if(p.isNull() )
    {
        if(role ==DISABLE_ROLE)
        {
            return QVariant(true);
        }
        return QVariant();
    }

    if( role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant var=p->tag(index.column());
        return pretyTag(var,index.column() );
    }
    else if(role==URL_ROLE)
    {
        KUrl u(p->path() );
        return QVariant(u);
    }
    else if(role == TAG_ROLE)
    {
        return QVariant(index.column() );
    }
    else if(role ==DISABLE_ROLE)
    {
        if(!p->isValid() )
        {
            return QVariant(true);
        }

        return QVariant(false);
    }
    return QVariant();
}

bool views::playlistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(pl==0)
    {
        return false;
    }

    core::nplPointer f=pl->item(index.row() );
    if(f->type()==NPLAUDIOFILE)
    {
       audioFile file(f->path() );
       file.setTag(index.column(),value);

       if(file.error()==Basic::OK)
       {
          return true;
       }
    }

    return false;
}


QVariant views::playlistModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Vertical)
    {
        return QVariant();
    }
    if(role==Qt::DisplayRole)
    {
        return tagName(section);
    }
    if(role==Qt::DecorationRole)
    {
        return decor->tagIcon(section);
    }

    return QVariant();
}


void views::playlistModel::setPlaylist(core::playlist *playlist)
{
    beginResetModel();
    if(pl!=0)
    {
       delete pl;
    }

    pl=playlist;
    if(pl!=0)
    {
        connectPl();
    }
    endResetModel();
}

Qt::DropActions views::playlistModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction ;
}


Qt::ItemFlags views::playlistModel::flags(const QModelIndex &index) const
{
    static const Qt::ItemFlags ret=Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
    if(pl==0)
    {
        return Qt::NoItemFlags;
    }

    if(!index.isValid() )
    {
        return Qt::ItemIsDropEnabled;
    }

    core::nplPointer p=pl->item(index.row());
    if(p.isNull() )
    {
        return Qt::NoItemFlags;
    }
    if (index.column()==Basic::BITRATE ||index.column()==Basic::LENGTH || index.column()==Basic::COUNTER || p->type()==NPLSTREAM )
    {
         return ret & ~Qt::ItemIsEditable;
    }

    return ret;
}


void views::playlistModel::connectPl()
{
    connect(pl,SIGNAL(aboutToInsertTracks(int,int)),this,SLOT(beginInsertTracks(int,int)));
    connect(pl,SIGNAL(tracksInserted(int,int)),this,SLOT(endInsertTracks()));

    connect(pl,SIGNAL(aboutToMoveTrack(int,int,int)),this,SLOT(beginMoveTracks(int,int,int)));
    connect(pl,SIGNAL(tracksMoved(int,int,int)),this,SLOT(endMoveTracks()));

    connect(pl,SIGNAL(aboutToRemoveTracks(int,int)),this,SLOT(beginRemoveTracks(int,int)));
    connect(pl,SIGNAL(tracksRemoved(int,int)),this,SLOT(endRemoveTracks()));

    connect(pl,SIGNAL(aboutToClear()),this,SLOT(beginClear()));
    connect(pl,SIGNAL(cleared()),this,SLOT(endClear()));

    connect(pl,SIGNAL(aboutToShuffle()),this,SLOT(beginClear()));
    connect(pl,SIGNAL(shuffled()),this,SLOT(endClear()));
}

bool views::playlistModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    Q_UNUSED(action);
    Q_UNUSED(column);

    if(!data->hasUrls() )
    {
        return false;
    }

    if (views::reorderL.size()!=0 )
    {
        reorder(row,views::reorderL);
        return true;
    }

    core::nplList l;
    foreach(QUrl u,data->urls())
    {
        l<<core::nplTrack::getNplTrack(u);
    }

    pl->insert(row,l);
    return true;
}

void views::playlistModel::reorder(int r, const std::set< int >& rows)
{
//     disconnect(pl,SIGNAL(aboutToMoveTrack(int,int,int)),this,SLOT(beginMoveTracks(int,int,int)));
//     disconnect(pl,SIGNAL(tracksMoved(int,int,int)),this,SLOT(endMoveTracks()));

    if(r<0||r>=rowCount() )
    {
        r=rowCount();
    }
    std::set<int>::const_iterator it=rows.begin();

//I don't kwon what the fuck is going on but emitting the layoutAboutToBeChanged signals creates a lot of bugs on proxy models
//     beginResetModel ();

//      emit layoutAboutToBeChanged ();
    int n=0;
    int k=0;
    for(;it!=rows.end();it++)
    {
       if(*it<r )
       {
          pl->move(*it-n,r-1);
          n++;
       }
       else
       {
          pl->move(*it,r+k);
          k++;
       }
    }
//       endResetModel();
       reset();

//      emit layoutChanged ();

//     connect(pl,SIGNAL(aboutToMoveTrack(int,int,int)),this,SLOT(beginMoveTracks(int,int,int)));
//     connect(pl,SIGNAL(tracksMoved(int,int,int)),this,SLOT(endMoveTracks()));
}

void views::playlistModel::beginMoveTracks(int first,int size,int dest)
{
    int d,f,l;

    if(dest>first)//move down
    {
        f=first;
        d=dest+1;
        l=f+size-1;

    }
    else
    {
        d=first+1;
        f=dest+size-1;
        l=first-1;
    }
    beginMoveRows(QModelIndex(),f,l,QModelIndex(),d);
}

void views::playlistModel::remove(const QModelIndexList& list)
{
    std::set<int> rowL;
    foreach(QModelIndex index,list)
    {
        rowL.insert(index.row() );
    }
    int n=0;
    std::set<int>::iterator it;
    for(it=rowL.begin();it!=rowL.end();it++)
    {
        pl->remove(*it-n);
        n++;
    }
}

