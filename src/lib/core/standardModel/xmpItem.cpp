#include"xmlItem.h"
#include<QDebug>
core::xmlItem::xmlItem(QDomDocument &doc,const QString &tagName)
  :standardItem(),
  columns(1)
{
    _attributeRole=Qt::DisplayRole;
    element=doc.createElement(tagName);
}

core::xmlItem::xmlItem()
    :standardItem(),
    columns(1)
{
    _attributeRole=Qt::DisplayRole;
}

core::xmlItem::xmlItem(const QDomElement &el)
   :standardItem(),
   element(el),
   columns(1)
{
    _attributeRole=Qt::DisplayRole;
}

QDomElement core::xmlItem::xml() const
{
    return element;
}

// bool core::xmlItem::appendRow ( standardItem * item )
// {
//     qDebug()<<"QQQ";
//     return insertRow(rowCount(),item); 
// }

bool core::xmlItem::insertRow(int row, standardItem* item)
{
    xmlItem *newItem=dynamic_cast<xmlItem*>(item);
    if(newItem==0 )
    {
	return false;
    }
    
    if(row<0||row>rowCount())
    {
	return false;
    }    
    
    if(row==rowCount() )
    {
	QDomNode n= element.appendChild(newItem->xml() );
	if(n.isNull() )
	{
	    qDebug()<<"Error inserting xml node";
	}
	
    }    
    else
    {
	xmlItem *previous=static_cast<xmlItem*>( child(row-1) );
	
	QDomNode n= 	element.insertBefore(newItem->xml(),previous->xml() );
	if(n.isNull() )
	{
	    qDebug()<<"Error inserting xml node";
	}

    }
    standardItem::insertRow(row,item);    
    
    return true;
}

bool core::xmlItem::insertRowWithNoElement(int row, standardItem* item)
{
    return standardItem::insertRow(row,item);  
}

bool core::xmlItem::insertRows( int row, const QList< standardItem* >& items )
{
    for(int i=row;i<row+items.size();i++)
    {
	insertRow(i,items[i]);
    }
    return true;
}

bool core::xmlItem::removeRow(int row)
{
    standardItem *i=child(row);
    
    if(i==0)
    {
	return false;
    }
    xmlItem *item=static_cast<xmlItem*>(i);
    QDomElement el=item->xml();
    element.removeChild(el);
    standardItem::removeRow(row);
    
    return true;
}

bool core::xmlItem::removeRows(int row ,int count)
{
    for(int i=0;i<count;i++)
    {
	removeRow(row);
    }
    return true;

}

bool core::xmlItem::setTagName(const QString &name)
{
    element.setTagName(name );
    return true;
}

QString core::xmlItem::tagName() const
{
    return element.tagName();
}

QVariant core::xmlItem::data ( int column, int role ) const
{
    if(role==_attributeRole)
    {
	if(column>=columns.size()||column<0 )
	{
	    return QVariant();
	}
	
	return QVariant( element.attribute(columns[column] ) );
    }
    
    if(role==attributeName)
    {
      	if(column>=columns.size()||column<0 )
	{
	    return QVariant();
	}
	return QVariant( columns[column] );
    }
    
    if(role==tagNameRole)
    {
	return QVariant(tagName() );
    }
    return QVariant();
}

bool core::xmlItem::setData (const QVariant &value,int column, int role )
{    
    //we treat the edit role and the display role the same
    if(role==Qt::EditRole)
    {
	role=Qt::DisplayRole;
    }
    
    if(role==attributeName)
    {
      	if(column>=columns.size()||column<0 )
	{
	    return false;
	}
	
	columns[column]=value.toString();
	return true;
    }
    
    if(role ==_attributeRole)
    {	
	if(column>=columns.size() || column<0 || columns[column].isEmpty())
	{
	    return false;
	}
	element.setAttribute(columns[column],value.toString() );
	return true;
    }
    
    if(role==tagNameRole)
    {
	return setTagName(value.toString() );	
    }
    
    return false;
}

bool core::xmlItem::insertColumns(int start,const QStringList &list)
{
    if(start>columnCount()  )
    {
	return false;
    }
    standardItem::beginInsertColumns(start,start+list.size() );
    columns.insert(start,list.size(),QString() );
    
    for(int i=0;i<list.size();i++)
    {
	columns[start+i]=list[0];
    }
    standardItem::endInsertColumns();
    
    return true;
}


int core::xmlItem::type()
{
    return XmlType;
}


const int core::xmlItem::XmlType=StandardType+1;
const int core::xmlItem::tagNameRole=Qt::UserRole+1;
const int core::xmlItem::attributeName=Qt::UserRole+2;