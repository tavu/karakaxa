#include"standardModel.h"
#include<QDebug>

standardModel::standardModel(QObject* parent)
  :QAbstractItemModel(parent)
{ 
  
}

standardModel::~standardModel()
{
}

QModelIndex standardModel::indexFromItem(const standardItem* item,int column) const
{
    return createIndex(item->row(),column,(void*)item);
}


standardItem* standardModel::itemFromIndex(const QModelIndex& index) const
{
    return (standardItem*)index.internalPointer();
}

QModelIndex standardModel::index(int row, int column, const QModelIndex& parent) const
{
    standardItem *item;
    if(!parent.isValid() )
    {
	item=head;
    }
    else
    {
	item=(standardItem*)parent.internalPointer();
    }
    item=item->child(row);
    return createIndex(row,column,item);
}


bool standardModel::removeRows (int row, int count, const QModelIndex & parent )
{    
    if(!parent.isValid())
    {
	return false;
    }
    
    standardItem *father=itemFromIndex(parent);
    father->removeRows(row,count);
    
    return true;
}


bool standardModel::canFetchMore ( const QModelIndex &parent ) const
{
    if(!parent.isValid() )
    {
	return false;
    }
    standardItem *item=(standardItem*)parent.internalPointer();
    
    return item->canFetchMore();
}

void standardModel::fetchMore(const QModelIndex &index)
{
    if(!index.isValid() )
    {
	return ;
    }
    standardItem *item=(standardItem*)index.internalPointer();
    
    item->fetchMore();
}

bool standardModel::hasChildren(const QModelIndex& parent) const
{
    standardItem *item=(standardItem*)parent.internalPointer();
    if(item==0)
    {
	if(rowCount()==0)
	{
	  return false;
	}
	else
	{
	  return true;
	}
    }    
    
    return item->hasChildren();
}

QModelIndex standardModel::parent(const QModelIndex& index) const
{
    standardItem *item=itemFromIndex(index);    
    item=item->parent();
    if(item==head)
    {
	return QModelIndex();
    }
    return indexFromItem(item,0);
    
}


/*==========MYSTANDARDITEM============*/


standardItem::standardItem()
  :QObject(),
  _model(0),
  _parent(0)
{

}

bool standardItem::canFetchMore() const
{
    //reimplyment this function. by default return false
    return false;
}

void standardItem::fetchMore()
{
    //by default does nothing
}

bool standardItem::hasChildren() const
{
    if(rowCount()!=0)
    {
	return true;
    }
    return false;    
}

bool standardItem::save()
{
    //by default does nothing.
    return true;
}


bool standardItem::operator<(const standardItem& other) const
{
//     int role=Qt::DisplayRole;
//     
//     if(_model!=0)
//     {	
// //       role=_model->sortRole();	
//     }
//     
//     int c=QString::compare( data(role).toString(), other.data(role).toString(), Qt::CaseInsensitive);
//     
//     if(c<0)
//     {
// 	return true;
//     }
//     if(c==0)
//     {
// 	c=QString::compare( data(Qt::DisplayRole).toString(), other.data(Qt::DisplayRole).toString(), Qt::CaseInsensitive);
// 	if(c<0)
// 	{
// 	    return true;
// 	}
//     }
//     return false;
}

int standardItem::type() const
{
    return StandardType;
}

// QVariant standardItem::data(int role,int column) const
// {
//     if(role==typeRole)
//     {
// 	return QVariant(type() );
//     }
//     if(role==Qt::DisplayRole||Qt::EditRole)
//     {
// 	if(column>=0 && column<columns.size() )
// 	{
// 	    return columns[column];
// 	}
// 	return QVariant();
//     }
//     return QStandardItem::data(role);
// }

bool standardItem::removeRow(int row)
{
    if(row<0||row>children.size() )
    {
	return false;
    }
    
    if(_model!=0)
    {
	QModelIndex index=_model->indexFromItem(this,0);
	_model->beginRemoveRows(index,row,row );
    }
    
    standardItem *item=children.takeAt(row)	;
    delete item;
    
    if(_model!=0)
    {
	_model->endRemoveRows();
    }
    return true;
}

bool standardItem::removeRows(int row, int count)
{    
    if(row<0||row+count>children.size() )
    {
	return false;
    }
    
    if(_model!=0)
    {
	QModelIndex index=_model->indexFromItem(this,0);
	_model->beginRemoveRows(index,row,row+count );
    }
    standardItem *item;
    for(int i=0;i<count;i++)
    {
	item=children.takeAt(row+i);
	delete item;
    }
    
    if(_model!=0)
    {
	_model->endRemoveRows();
    }
    
    return true;
}


bool standardItem::insertRows(int row, const QList< standardItem* >& items)
{
    if(items.isEmpty() )
    {
	return true;
    }
    
    if(_model!=0)
    {
 	QModelIndex index=_model->indexFromItem(this,0);
	_model->beginInsertRows(index,row,row+items.size() );
    }
    
    for(int i=0;i<items.size();i++)
    {
	insert(row+i,items[i]);
    }
    if(_model!=0)
    {
	_model->endInsertRows();
    }
    
    return true;
}

bool standardItem::insertRow(int row, standardItem* item)
{
    if(_model!=0)
    {
 	QModelIndex index=_model->indexFromItem(this,0);
	_model->beginInsertRows(index,row,row );
    }
    
    children.insert(row,item);
    item->_row=row;
    item->_model=_model;
    item->_parent=this;
    
    if(_model!=0)
    {
	_model->endInsertRows();
    }
    
    
    return true;
}

standardItem* standardItem::child(int row) const
{    
    if(row<0||row>=children.size() )
    {
	return 0;
    }
    return children[row];
}

void standardItem::insert(int row, standardItem *item)
{  
    children.insert(row,item);
    item->_row=row;
    item->_model=_model;
    item->_parent=this;   
}

standardModel* standardItem::model() const
{
    return _model;
}

int standardItem::row() const
{
    return _row;    
}

standardItem* standardItem::parent() const
{
    return _parent;
}

bool standardItem::setData(const QVariant& value, int column, int role)
{
    return true;
}

void standardItem::beginInsertColumns(int first, int last)
{
    if(_model!=0)
    {
	QModelIndex index=_model->indexFromItem(this,0);
	_model->beginInsertColumns(index,first,last );
    }
}

void standardItem::endInsertColumns()
{
    if(_model!=0)
    {
	_model->endInsertColumns();
    }
}

int standardItem::rowCount() const
{
    return children.size();
}


const int standardItem::StandardType=QStandardItem::UserType;            
const int standardItem::typeRole=Qt::UserRole+2; 