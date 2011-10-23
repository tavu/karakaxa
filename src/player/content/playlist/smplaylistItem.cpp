#include"smplaylistItem.h"
#include"items.h"
#include<core.h>
#include<views.h>

using namespace core;
smplaylistItem::smplaylistItem(QDomDocument &doc, const QString &text)
  :xmlItem(doc,QString("smartPlaylist") ),
  quer(0)
{
//      _query.clear();
     setData(QVariant("name"),0,attributeName);
     setData(QVariant(text), 0 ,attributeRole() ); 
//     setIcon(decor.tagIcon(-1));
}

smplaylistItem::smplaylistItem(const QDomElement &el)
  :xmlItem(el),
  quer(0)
{
//     _query.clear();
    setData(QVariant("name"),0,attributeName);
}    

void smplaylistItem::generateQuery() const
{        
    QDomElement el=element.firstChildElement();
    quer =group(el);
    /*
    for(QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSiblingElement("group"))
    {      
	for(QDomNode nod=n.firstChild(); !nod.isNull(); nod=n.nextSibling() )
	{	    
	    if(n.nodeName()==QString("group") )
	    {
		_query +=group(n);
	    }
	}
    }
    */
}

int smplaylistItem::type () const
{
    return SMARTPL_ITEM;
}

bool smplaylistItem::setData(const QVariant& value, int column, int role)
{
    if(value.isNull() )
    {
	return false;
    }
    return core::xmlItem::setData(value, column, role);
}


queryGrt::abstractQuery* smplaylistItem::group(QDomNode nod) const
{
    queryGrt::matchQuery *q;
  
    QDomElement e=nod.toElement();
    QString s=e.attribute("matchtype");
    
    if(s==QString("all") )
    {
	q=new queryGrt::matchQuery(queryGrt::AND);
    }
    else if(s==QString("any") )
    {
	q=new queryGrt::matchQuery(queryGrt::OR);
    }
    else
    {
	return 0;
    }
    

    for(QDomNode n=nod.firstChild(); !n.isNull(); n=n.nextSibling() )	
    {
	QString name=n.nodeName();
	
	if(name==QString("group") )
	{	  
// 	    q+=group(n);
	    q->append(group(n) );
	}
	else if(name==QString("field") )
	{
	    QString s;
	    bool invert;
	    int t;
	    queryGrt::equal comp;

	    QDomElement e=n.toElement();
	    s=e.attribute("tag");
	    
	    t=s.toInt();
	    
	    s=e.attribute("comparison");
	    comp=(queryGrt::equal)s.toInt();
	    
	    s=e.attribute("invert");
	    invert=(bool)s.toInt();
	    
	    s=e.attribute("value");
	    
	    q->append(new queryGrt::tagQuery(t,comp,s,invert) );
// 	    l<<queryGrt::query(t,comp,s,invert);
	}	
    }   
    
    return q;    
}


QVariant smplaylistItem::data (int column,int role  ) const
{
    if(column!=0)
    {
	return QVariant();
    }
    if(role==Qt::DecorationRole)
    {
	return views::decor->tagIcon(-1);
    }
    if(role==ITEM_ROLE)
    {
	return QVariant();
    }
    if(role ==typeRole)
    {
	return QVariant(type() );
    }
    return xmlItem::data(column,role);
}

core::queryGrt::abstractQuery* smplaylistItem::query() const
{	    

    if(quer==0 )
    {
	generateQuery();	
    }
	    
    return quer;
}

// const int smplaylistItem::SMARTPL_ITEM=core::xmlItem::XmlType+2;