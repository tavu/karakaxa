#include"xmlItem.h"

core::xmlItem::xmlItem(const QString &tagName)
  :standardItem(),
  columns(1)
{
    _attributeRole=Qt::DisplayRole;
    element.setTagName(tagName);
}

core::xmlItem::xmlItem()
    :standardItem(),
    columns(1)
{
    _attributeRole=Qt::DisplayRole;
}

QDomElement core::xmlItem::xml() const
{
    return element;
}

bool core::xmlItem::insertRow(int row,xmlItem * item)
{
    if(row<0||row>rowCount())
    {
	return false;
    }
    
    if(row>0)
    {
	standardItem *prev=child(row-1);
	xmlItem *previous=static_cast<xmlItem*>(prev);
	
	QDomElement el=previous->xml();
	element.insertAfter(item->xml(),el);
    }    
    else
    {

	standardItem *prev=child(1);
	xmlItem *previous=static_cast<xmlItem*>(prev);
	
	QDomElement el=previous->xml();
	element.insertBefore(item->xml(),el);

    }
    standardItem::insertRow(row,item);
    
    return true;
}

bool core::xmlItem::insertRows( int row, const QList< core::xmlItem* >& items )
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

QString core::xmlItem::tagName() const
{
    return element.tagName();
}

QVariant core::xmlItem::data ( int column, int role ) const
{
    if(role==_attributeRole)
    {
	return element.attribute(columns[column] );
    }
}
bool core::xmlItem::setData (const QVariant &value,int column, int role )
{
    if(role==Qt::EditRole)
    {
	columns[column]=value.toString();
	return true;
    }
    
    if(role==_attributeRole)
    {
	if(columns[column].isEmpty() )
	{
	    return false;
	}
	element.setAttribute(columns[column],value.toString() );
	return true;
    }
    return false;
}

void core::xmlItem::setColumnCount(int num)
{
    if(columns.size()<num)
    {
	standardItem::beginInsertColumns(columns.size(),num );
	columns.resize(num);
	endInsertColumns();
    }    
}

int core::xmlItem::type()
{
    return XmlType;
}


const int core::xmlItem::XmlType=StandardType+1;