#ifndef FOLDERPROXYMODEL_H 
#define FOLDERPROXYMODEL_H

#include<QSortFilterProxyModel>

class folderProxyModel :public QSortFilterProxyModel
{
    public:
	folderProxyModel(QObject *parent=0)
	:QSortFilterProxyModel(parent)
	{}
	
    protected:
	bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;
	bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const;
};

#endif
