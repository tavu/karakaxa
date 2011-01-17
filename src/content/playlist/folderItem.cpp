#include"folderItem.h"
#include"items.h"
#include"smplaylistItem.h"
#include<KIcon>
#include<QDebug>
folderItem::folderItem(const QString &text)
  :myStandardItem(text)
{
     setIcon(KIcon("folder"));
     QDomDocument doc;
     element=doc.createElement("folder");
     element.setAttribute("name",text );     
}

folderItem::folderItem(const QDomElement &el)
    :myStandardItem()
{ 
    setIcon(KIcon("folder"));
    element=el;
    QString s=element.attribute(QString("name"),"Unnamed");
    qDebug()<<s;
    setData(s,Qt::DisplayRole);
}

void folderItem::setData ( const QVariant & value, int role )
{    
      if(role==Qt::DisplayRole)
      {
	element.setAttribute("name",value.toString() );
      }
	
      myStandardItem::setData(value,role);	
}

int folderItem::type () const
{
    return FOLDER_ITEM;
}

QDomElement folderItem::xml() const
{
  return element;
}

bool folderItem::addRow (myStandardItem* item )
{
    QDomElement el=item->xml();
    
    if(!el.isNull() )
    {
      element.appendChild(el);
      appendRow(item);
    }
//     appendRow(item);
    return true;
}

bool folderItem::removeR (int row)
{
    qDebug()<<"Row "<<row;
    QStandardItem *i=child(row,0);
    
    if(i==0)
    {
	return false;
    }
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    
    QDomElement el=item->xml();
    element.removeChild(el);
    myStandardItem::takeRow(row);
    delete item;    
}

bool folderItem::hasChildr() const
{    
    bool ret;
    if(element.hasChildNodes() )
    {
	ret=true;
    }
    else
    {
      ret=false;
    }	
    
    return ret;
}

bool folderItem::canFetchMore() const
{
    if(rowCount()==0)
    {
      return true;
    }
    return false;
}

void folderItem::fetchMore()
{
    for(QDomElement el = element.firstChildElement(); !el.isNull(); el = el.nextSiblingElement())
    {
	if(el.tagName()==QString("smartPlaylist") )
	{
	    smplaylistItem *i=new smplaylistItem(el.attribute("name","Unnamed") );
	    i->setXmlElement(el);
	    appendRow(i);
	}
	else if(el.tagName()==QString("folder") )
	{
	    folderItem *i=new folderItem(el);
	    appendRow(i);
	}
    }
}
