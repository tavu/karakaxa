#include"folderProxyModel.h"
#include<core.h>
#include<QUrl>
#include<views.h>
#define DIRCOLUMN 7
bool folderProxyModel::filterAcceptsRow ( int row, const QModelIndex &parent ) const
{
    QModelIndex index=sourceModel()->index(row, 0, parent);
    QUrl u=index.data(URL_ROLE).toUrl();
    QString path=u.toString();

    if(core::isAudio(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if(core::isPlaylist(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if( core::isDirectory(path) )
    {
        return QSortFilterProxyModel::filterAcceptsRow(row,parent);
    }
    if(core::isStream(path) )
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

    if(core::isDirectory(pathL) )
    {
        l=2;
    }
    else if(core::isPlaylist(pathL) )
    {
        l=1;
    }

    if(core::isDirectory(pathR) )
    {
        r=2;
    }
    else if(core::isPlaylist(pathR) )
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