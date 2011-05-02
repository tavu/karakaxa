#include"nplAbstractModel.h"
#include"../core.h"

core::nplAbstractModel::nplAbstractModel(QObject *parent)
  :QAbstractItemModel(parent)
{
    core::npList->setModel(this);
}

QModelIndex core::nplAbstractModel::index(int row,int column,const QModelIndex &parent) const
{
    if(parent.isValid() )
    {
	return QModelIndex();
    }
    return createIndex(row,column);
}

QModelIndex core::nplAbstractModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int core::nplAbstractModel::rowCount ( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return npList->size();
}
