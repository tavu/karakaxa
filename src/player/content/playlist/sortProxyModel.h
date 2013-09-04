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
    bool setData (const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
};

#endif
