#include"nplaylistModel.h"
#include<QList>
#include<QUrl>
#include<QMimeData>
#include<QStringList>
#include<KIcon>
// #include "myUrl.h"
using namespace player;


nplModel::nplModel( QObject * parent)
        :QAbstractListModel(parent),
        size(0)
{
    connect(&npList,SIGNAL(aboutToInsert(int)),this,SLOT(beginInsert(int) ), Qt::QueuedConnection );
// 	  removeColumn(3);
// 	  connect(&npList,SIGNAL(insertFinish() ),this,SLOT(endInsert() ), Qt::QueuedConnection);

    connect(&npList,SIGNAL(aboutToRemove(int) ),this,SLOT(beginRemove(int ) ), Qt::QueuedConnection);

    connect(&npList,SIGNAL(changed(int) ),this,SLOT(end(int) ) , Qt::QueuedConnection);

    connect(&npList,SIGNAL(aboutToClear(int) ),this,SLOT(beginClear(int ) ), Qt::QueuedConnection);

// 	  connect(&npList,SIGNAL(clearFinished() ),this,SLOT(endRemove() ) , Qt::QueuedConnection);
}

QVariant nplModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid() )
    {
        return QVariant();
    }

    if (role==Qt::DisplayRole)
    {
        nplTrack *t=npList.getTrack(index.row() );

        if (t==0)	return QVariant();

        QString ret;
        if (t->path().isEmpty() )
        {
            return QVariant();
        }

        if (t->trackN()==0)
        {
            ret.append("    ");
        }
        else
        {
            ret.append( QString::number(t->trackN())+" - " );

            if (ret.size()==4)
            {
                ret.prepend(" " );
            }
        }

        ret.append(t->title() );
        return ret;
    }
    return QVariant();
}

int nplModel::rowCount ( const QModelIndex & parent ) const
{
//      return npList.size();
    return size;
}

bool nplModel::dropMimeData ( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (row<0)
        row=npList.size();

    if (reorderL.isEmpty() )
    {
        npList.addMediaList( data->urls(),row );
    }
    else
    {
        reorder(row);
    }
    return true;
}

void nplModel::setReorder(QList<int> &l)
{
    reorderL=l;
}

void nplModel::clearReorder()
{
    reorderL.clear();
}

void nplModel::reorder(int r)
{
    QList<int>::const_iterator it=reorderL.begin();

    int n=0;
    while (it!=reorderL.end() )
    {
        if (*it<r)
        {
            npList.move(*it-n,r-1);
            n++;
        }
        else
        {
            npList.move(*it,r);
        }
        it++;
    }
}


Qt::DropActions nplModel::supportedDropActions () const
{
    return Qt::CopyAction|Qt:: MoveAction|Qt::IgnoreAction;
}

QStringList nplModel::mimeTypes () const
{
    QStringList qstrList;
    qstrList.append("text/uri-list");
    return qstrList;
}

Qt::ItemFlags nplModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled  | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

void nplModel::beginInsert(int pos)
{
    QAbstractItemModel::beginInsertRows(QModelIndex(),pos,pos);
}

void nplModel::end(int flag)
{
    if (flag==nplaylist::ADD)
    {
        QAbstractItemModel::endInsertRows();
        size++;
    }
    else if (flag==nplaylist::REMOVE)
    {
        QAbstractItemModel::endRemoveRows();
        size--;
    }
    else if (flag==nplaylist::CLEAR)
    {
        QAbstractItemModel::endRemoveRows();
        size=0;
    }
}

void nplModel::beginRemove(int pos)
{

    QAbstractItemModel::beginRemoveRows( QModelIndex(),pos,pos);
}

void nplModel::beginClear(int size)
{
    QAbstractItemModel::beginRemoveRows( QModelIndex(),0,size);
}
