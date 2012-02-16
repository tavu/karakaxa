#include"playlistModel.h"
#include<views.h>
#include<core.h>
views::playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
    pl(0)
{
}

views::playlistModel::~playlistModel()
{
    if(pl!=0)
        delete pl;
}


int views::playlistModel::rowCount ( const QModelIndex & parent ) const
{
    if(pl==0)
        return 0;

    return pl->size();
}

int views::playlistModel::columnCount ( const QModelIndex & parent ) const
{
    return FRAME_NUM;
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
        return QVariant();
    }

    if( role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant var=p->tag(index.column());
        return pretyTag(var,(tagsEnum)index.column() );
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
    return QVariant();
}

bool views::playlistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(pl=0)
        return false;

    core::nplPointer f=pl->item(index.row() );
    if(f->type()==NPLAUDIOFILE)
    {
       audioFile file(f->path() );
       file.setTag(index.column(),value);

       if(file.error()==OK)
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
        pl->setParent(this);        
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
        return ret & ~Qt::ItemIsEnabled;
    }

    if(!index.isValid() )
    {
        return Qt::ItemIsDropEnabled;
    }

    core::nplPointer p=pl->item(index.row() );

    if(p.isNull() || !p->isValid() )
    {
        return ret & ~Qt::ItemIsEnabled;
    }

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER ||p->type()==NPLSTREAM )
    {
         return ret & ~Qt::ItemIsEditable;
    }

    return ret;
}

void views::playlistModel::updateData()
{
    QModelIndex topLeft ,bottomRight;
    topLeft=index(0,0);
    bottomRight=index(rowCount()-1,columnCount()-1 );

    emit dataChanged(topLeft,bottomRight);
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
}

bool views::playlistModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    Q_UNUSED(action);
    Q_UNUSED(column);

    if(!data->hasUrls() )
    {
        return false;
    }

    core::nplList l;
    foreach(QUrl u,data->urls())
    {
        l<<core::nplTrack::getNplTrack(u);
    }

    pl->insert(row,l);
    return true;
}

