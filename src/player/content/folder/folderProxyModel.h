#ifndef FOLDERPROXYMODEL_H 
#define FOLDERPROXYMODEL_H

#include<QSortFilterProxyModel>

class folderProxyModel :public QSortFilterProxyModel
{
    public:
        folderProxyModel(QObject *parent=0)
        :QSortFilterProxyModel(parent)
        {}

        void setSourceModel(QAbstractItemModel *m)
        {
            QSortFilterProxyModel::setSourceModel(m);
            reset();
        }

    protected:
        bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;
        bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const;
        bool setData( const QModelIndex & index, const QVariant & value, int role);
};

#endif
