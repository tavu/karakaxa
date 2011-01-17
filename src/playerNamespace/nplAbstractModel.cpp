#include"nplAbstractModel.h"
#include<player.h>

nplAbstractModel::nplAbstractModel(QObject *parent)
  :QAbstractItemModel(parent)
{
    player::npList.setModel(this);
}

QModelIndex nplAbstractModel::index(int row,int column,const QModelIndex &parent) const
{
    if(parent.isValid() )
    {
	return QModelIndex();
    }
    return createIndex(row,column);
}

QModelIndex nplAbstractModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int nplAbstractModel::rowCount ( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return npList.size();
}