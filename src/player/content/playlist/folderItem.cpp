#include"folderItem.h"
#include"items.h"
#include"smplaylistItem.h"
#include<KIcon>
#include<QDebug>

using namespace core;

folderItem::folderItem(QDomDocument &doc, const QString &text)
  :xmlItem(doc,"folder")
{
//      setIcon(KIcon("folder"));
     setData(QVariant("name"),0,attributeName);
     setData(QVariant(text), 0 ,attributeRole() );  
     
}

folderItem::folderItem(const QDomElement &el)
    :xmlItem()
{ 
    setXml(el);
    setData(QVariant("name"),0,attributeName);
}

int folderItem::type () const
{
    return FOLDER_ITEM;
}

bool folderItem::canFetchMore() const
{
    if(rowCount()==0 && hasChildren() )
    {
	return true;
    }
    return false;
}

void folderItem::fetchMore()
{
    int i=0;
    for(QDomElement el = element.firstChildElement(); !el.isNull(); el = el.nextSiblingElement())
    {
	if(el.tagName()==QString("smartPlaylist") )
	{
	    smplaylistItem *i=new smplaylistItem(el);
 	    insertRowWithNoElement(rowCount(),i);
	}
	else if(el.tagName()==QString("folder") )
	{
 	    folderItem *i=new folderItem(el);
  	    insertRowWithNoElement(rowCount(),i);
	}
	i++;
    }    
}

QVariant folderItem::data(int column, int role) const
{
    if(column!=0)
    {
	return QVariant();
    }
    if(role==Qt::DecorationRole)
    {
	return KIcon("folder");
    }
    if(role==Qt::SizeHintRole )
    {
	if(sizeHint.isEmpty() )
	{
	    return QVariant();
	}
	return sizeHint;
    }
    return core::xmlItem::data(column, role);
}

Qt::ItemFlags folderItem::flags(int column) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant smplalistHead::data(int column, int role) const
{
  if(column!=0)
  {
    return QVariant();
  }
  
  if(role==Qt::DisplayRole)
  {		
      return QVariant( tr("Smart Playlists") );	
  }
	
  return folderItem::data(column,role);
}

// const int folderItem::FOLDER_ITEM=core::xmlItem::XmlType+1;

Qt::ItemFlags smplalistHead::flags(int column) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}