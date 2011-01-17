#ifndef SORTPROXYMODEL_H
#define SORTPROXYMODEL_H
#include<QSortFilterProxyModel>

class sortProxyModel :public QSortFilterProxyModel
{
    sortProxyModel(QObject *parent=0);
    
    virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const;
};

#endif
