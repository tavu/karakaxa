#include"folderProxyModel.h"
#include<core.h>
#include<QUrl>
#include<views.h>
bool folderProxyModel::filterAcceptsRow ( int row, const QModelIndex &parent ) const
{
    QModelIndex index=sourceModel()->index(row, 0, parent);
    QUrl u=index.data(URL_ROLE).toUrl();
    QString path=u.toLocalFile();
    
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
    return false;
}

bool folderProxyModel::lessThan ( const QModelIndex & left, const QModelIndex & right ) const
{
    QString pathL,pathR;
    pathL=left.data(URL_ROLE).toUrl().toLocalFile();
    pathR=right.data(URL_ROLE).toUrl().toLocalFile();
    
    bool isFolderL,isFolderR;
    isFolderL=core::isDirectory(pathL);
    isFolderR=core::isDirectory(pathR);
    
    if(isFolderL && isFolderR) //both are directories
    {
	return QSortFilterProxyModel::lessThan(left,right);
    }
    if( isFolderL && ~isFolderR ) //only the left are directory
    {
	return true;
    }
    if( ~isFolderL && isFolderR ) //only the righy are directory
    {
	return false;    
    }
    
    return QSortFilterProxyModel::lessThan(left,right);    
}