#include"myStandardModel.h"
#include<QDebug>

myStandardModel::myStandardModel(QObject* parent)
  :QStandardItemModel(parent)
{  
}

myStandardModel::~myStandardModel()
{
}

bool myStandardModel::removeRows ( int row, int count, const QModelIndex & parent )
{    
    if(!parent.isValid())
    {
	return QStandardItemModel::removeRows(row,count,parent);
    }
    else
    {	      
      QStandardItem *i=itemFromIndex(parent);
      myStandardItem *item=static_cast<myStandardItem*>(i);
	
      for(int i=row;i<row+count;i++)	
      {
	  item->removeR(i);
      }
    }
}


bool myStandardModel::canFetchMore ( const QModelIndex &parent ) const
{
    QStandardItem *i=itemFromIndex(parent);
    
    if(i==0)	return false;
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    
    return item->canFetchMore();
}

void myStandardModel::fetchMore(const QModelIndex &index)
{
    QStandardItem *i=itemFromIndex(index);
    if(i==0)	return ;
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    
    item->fetchMore();
}

bool myStandardModel::hasChildren(const QModelIndex& parent) const
{
    QStandardItem *i=itemFromIndex(parent);
    if(i==0)
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
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    
    return item->hasChildr();
}

myStandardItem* myStandardModel::head(QModelIndex index) const
{
    if(!index.isValid())
    {
	return 0;
    }
  
    while(index.parent().isValid() )
    {
	index=index.parent();	
    }
    
    QStandardItem *i=itemFromIndex(index);
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    return item;
}

/*==========MYSTANDARDITEM============*/

myStandardItem::myStandardItem(const QString& text)
  :QStandardItem(text)
{
}
myStandardItem::myStandardItem()
  :QStandardItem()
{

}


myStandardItem::myStandardItem(const QIcon& icon, const QString& text)
  :QStandardItem(icon, text)
{

}

bool myStandardItem::canFetchMore() const
{
    //reimplyment this function. by default return false
    return false;
}

void myStandardItem::fetchMore()
{
    //by default does nothing
}

bool myStandardItem::hasChildr() const
{
    if(rowCount()!=0)
    {
	return true;
    }
    return false;    
}

bool myStandardItem::save()
{
    //by default does nothing.
    return true;
}

QDomElement myStandardItem::xml() const
{
    return QDomElement();
}

bool myStandardItem::operator<(const QStandardItem& other) const
{
    int role=Qt::DisplayRole;
    if(type()==other.type() )
    {
	QStandardItemModel *m=model();
	if(m!=0)
	{
	    role=m->sortRole();
	}
	return QString::compare( data(role).toString(), other.data(role).toString(), Qt::CaseInsensitive);
    }
    else if( type() < other.type())
    {
	return true;
    }
    return false;
}

