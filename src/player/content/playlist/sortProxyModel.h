#ifndef SORTPROXYMODEL_H
#define SORTPROXYMODEL_H
#include<QSortFilterProxyModel>

class sortProxyModel :public QSortFilterProxyModel
{
  public:
    sortProxyModel(QObject *parent=0)
    :QSortFilterProxyModel(parent){}
    
    virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const;
    
    virtual void fetchMore ( const QModelIndex & parent );

};

#endif
