#include"folderProxyModel.h"
#include<core.h>
#include<QUrl>
#include<views.h>
#include<Basic/func.h>


bool folderProxyModel::filterAcceptsRow ( int row, const QModelIndex &parent ) const
{
    QModelIndex index=sourceModel()->index(row, 0, parent);
    QUrl u=index.data(URL_ROLE).toUrl();
    QString path=u.toString();

    if(Basic::isAudio(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if(Basic::isPlaylist(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if( Basic::isDirectory(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if(Basic::isStream(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    return false;
}

void folderProxyModel::sort(int column, Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(column, order);
}


bool folderProxyModel::lessThan ( const QModelIndex & left, const QModelIndex & right ) const
{
    QString pathL,pathR;
    pathL=left.data(URL_ROLE).toUrl().toLocalFile();
    pathR=right.data(URL_ROLE).toUrl().toLocalFile();

    int r=0,l=0;

    if(Basic::isDirectory(pathL) )
    {
        l=2;
    }
    else if(Basic::isPlaylist(pathL) )
    {
        l=1;
    }

    if(Basic::isDirectory(pathR) )
    {
        r=2;
    }
    else if(Basic::isPlaylist(pathR) )
    {
        r=1;
    }

    if(r==l)
    {
        return QSortFilterProxyModel::lessThan(left,right);
    }

    return l<r;
}

bool folderProxyModel::setData( const QModelIndex & index, const QVariant & value, int role)
{
    return QSortFilterProxyModel::setData(index,value,role);
}