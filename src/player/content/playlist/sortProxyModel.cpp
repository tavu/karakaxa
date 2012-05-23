#include"sortProxyModel.h"
#include"items.h"
#include<core.h>

bool sortProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{        
    QString leftS=left.data(Qt::DisplayRole).toString();
    QString rightS=right.data(Qt::DisplayRole).toString();
    
    int  leftT=left.data(standardItem::typeRole).toInt();
    int  rightT=right.data(standardItem::typeRole).toInt();
    
    if(leftT<rightT )
    {
        return true;
    }
    if(leftT>rightT )
    {
        return false;
    }
    if(QString::compare(leftS,rightS,Qt::CaseInsensitive ) <0 )
    {
        return true;
    }
    else
    {
        return false;
    }
//     return QSortFilterProxyModel::lessThan(left, right);
}

void sortProxyModel::fetchMore(const QModelIndex& parent)
{    
    QSortFilterProxyModel::fetchMore(parent);
    sort(0,Qt::AscendingOrder);
}

bool sortProxyModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(QSortFilterProxyModel::setData(index, value, role) )
    {
        sort(0,Qt::AscendingOrder);
        return true;
    }
    return false;
}
