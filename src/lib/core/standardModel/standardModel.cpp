#include"standardModel.h"
#include<QDebug>

standardModel::standardModel(QObject* parent)
  :QAbstractItemModel(parent)
{ 
    head=new defaultHeadItem();
    head->_row=0;    
    head->_model=this;
}

void standardModel::setHeadItem(standardItem* h)
{
    if(head!=0)
    {
        delete head;
    }
      
    h->setParent(this);
    head=h;
    head->_row=0;    
    head->_model=this;

    emit headerDataChanged (Qt::Horizontal,0, columnCount()-1 );
    emit headerDataChanged (Qt::Vertical,0, columnCount()-1 );
}


standardModel::~standardModel()
{
  delete head;
}

QModelIndex standardModel::indexFromItem(const standardItem* item,int column) const
{
    if(item==head || item==0 ||column<0 || column >= item->columnCount() )
    {
	return QModelIndex();
    }    
    return createIndex(item->row(),column,(void*)item);
}


standardItem* standardModel::itemFromIndex(const QModelIndex& index) const
{
    if(!index.isValid() )
    {
	return 0;
    }
    return (standardItem*)index.internalPointer();
}

QModelIndex standardModel::index(int row, int column, const QModelIndex& parent) const
{
    standardItem *item=head;
    if(parent.isValid() )
    {
	item=(standardItem*)parent.internalPointer();
    }
    item=item->child(row);
    
    if(item==0)
    {
 	return QModelIndex();
    }
    
    return createIndex(row,column,item);
}


bool standardModel::removeRows (int row, int count, const QModelIndex & parent )
{    
    standardItem *father;
    if(parent.isValid())
    {
	father=itemFromIndex(parent);
    }
    else
    {
      father=head;
    }
    
    father->removeRows(row,count);
    
    return true;
}

bool standardModel::insertRow(int row, standardItem *item, const QModelIndex& parent)
{
    standardItem *father;
    father=itemFromIndex(parent);
    
    if(father==0)
    {
      father=head;
    }

    return father->insertRow(row,item);

}

bool standardModel::insertRows(int row, const QList< standardItem* >& items ,const QModelIndex& parent)
{
    standardItem *father;
    if(parent.isValid())
    {
	father=itemFromIndex(parent);
    }
    else
    {
      father=head;
    }
    return father->insertRows(row,items);
}

bool standardModel::appendRow(standardItem* item, const QModelIndex& parent)
{
    standardItem *father;
    if(parent.isValid())
    {
	father=itemFromIndex(parent);
    }
    else
    {
      father=head;
    }
    return father->appendRow(item);

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
    standardItem *item=head;
    if(parent.isValid() )
    {
        item=itemFromIndex(parent);
        if(item==0)
        {
            return false;
        }
    }
    
    return item->hasChildren();
}

QModelIndex standardModel::parent(const QModelIndex& index) const
{
    standardItem *item=itemFromIndex(index);    
    if(item==0)
    {
        return QModelIndex();
    }
    
    item=item->parent();
    if(item==head || item==0)
    {
        return QModelIndex();
    }
    return indexFromItem(item,0);
    
}


/*==========MYSTANDARDITEM============*/


standardItem::standardItem()
  :QObject(),
  _model(0),
  _parent(0),
  _childrenColumn(0)
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
    return canFetchMore();    
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
     return false;
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

bool standardModel::removeRow(int row, const QModelIndex& parent)
{
    standardItem *item=itemFromIndex(parent);
    if(item==0)
    {
        return false;
    }
    return item->removeRow(row);
   
}


bool standardModel::removeRow(standardItem* item)
{
    standardItem *parent=item->_parent;
    if(parent==0)
    {
	return false;
    }
    
    return parent->removeRow(item->row() );
}

void standardModel::emitDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    emit dataChanged( topLeft, bottomRight );
}


/*===============================model===================================*/

QVariant standardItem::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        return QString::number(section);	
    }
//     if (role == Qt::TextAlignmentRole)
//       return QVariant(Qt::AlignLeft|Qt::AlignTop );

    return QVariant();
}


QVariant standardModel::data(const QModelIndex& index, int role) const
{
    standardItem *item=itemFromIndex(index);
    if(item==0)
    {
        return QVariant();
    }
    return item->data(index.column(),role);
}

bool standardModel::setData( const QModelIndex & index,const QVariant& value, int role)
{
    standardItem *item=itemFromIndex(index);
    if(item==0)
    {
	return false;
    }
    
    return item->setData(value,index.column(),role);
}


int standardModel::columnCount(const QModelIndex &index ) const
{
    if(index.isValid() )
    {
        standardItem *item=itemFromIndex(index);
        if(item==0)
        {
            return 0;
        }
       return item->_childrenColumn;
    }  
    return head->columnCount();
}

int standardModel::rowCount(const QModelIndex &index ) const
{
    standardItem *item=head;
    if(index.isValid() )
    {
	item=itemFromIndex(index);
	if(item==0)
	{
	    return 0;
	}
    }    

    return item->rowCount();
}





/*===============STANDARD ITEM=====================*/

void standardItem::beginRemoveRows(int first, int last )
{
  if(_model)
  {
    QModelIndex i=_model->indexFromItem(this,0);
    _model->beginRemoveRows(i,first,last);	
  }  
}
      
void standardItem::endRemoveRows()
{
  if(_model)
  {	    
    _model->endRemoveRows();	
  }  
}


void standardItem::clear()
{    
    if(rowCount()==0)
    {
        return ;
    }
    
    beginRemoveRows(0,rowCount()-1 );
    standardItem **items=children.data();
    for(int i=0;i<children.size();i++)
    {
        delete items[i];
    }
    children.clear();
    endRemoveRows();
}


standardItem* standardItem::takeRow(int row)
{
    if(row<0||row>children.size() )
    {
        return 0;
    }
    standardItem *item=children[row];
    children.remove(row);
    return item;
}

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
    
    standardItem *item=children[row];
    children.remove(row);
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
	item=children.data()[row+i];
	children.remove(row+i);
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

    beginInsertRows(row,row+items.size()-1);
    
    for(int i=0;i<items.size();i++)
    {
	insert(row+i,items[i]);
    }

    endInsertRows();
    
    return true;
}

bool standardItem::insertRow(int row, standardItem* item)
{


    beginInsertRows(row,row ); 
    
    insert(row,item);
    
    endInsertRows();
    
    return true;
}

bool standardItem::appendRow ( standardItem * item )
{
    return insertRow(rowCount(),item); 
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
    if(row>children.size() )
    {
	return ;
    }
    children.insert(row,item);
    
    item->_row=row;
    item->_model=_model;
    item->_parent=this;    
    item->setParent(this);
    
    if(_childrenColumn<item->columnCount())
    {
        _childrenColumn=item->columnCount();
    }
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
    if(_model!=0 && _model->head==_parent)
    {
	return 0;
    }
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

      
void standardItem::beginInsertRows(int start,int end)
{
    if(_model!=0)	
    {	
      QModelIndex index=_model->indexFromItem(this,0);	
      _model->beginInsertRows(index,start,end );	
    }    
}
      

void standardItem::endInsertRows()
{	  
    if(_model!=0)	
    {	
      _model->endInsertRows();	
    }    
}


int standardItem::rowCount() const
{
    return children.size();
}

Qt::ItemFlags standardItem::flags(int column) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable |Qt::ItemIsDragEnabled;
}

void standardItem::dataChanged(const int first, const int last)
{    
    if(_model!=0)
    {
        QModelIndex a=_model->index(row(),first);
        QModelIndex b=_model->index(row(),last);
        _model->emitDataChanged(a,b);
    }
}

void standardItem::prealocateChildren(int n)
{
    if(children.size()<n)
    {
        children.reserve(n);
    }
}

Qt::ItemFlags standardModel::flags(const QModelIndex& index) const
{
    standardItem *item=itemFromIndex(index);
    
    if(item!=0)
    {
        return item->flags(index.column() );
    }
    return Qt::NoItemFlags;
}


const int standardItem::StandardType=QStandardItem::UserType;            
const int standardItem::typeRole=Qt::UserRole+2; 