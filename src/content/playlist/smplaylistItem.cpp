#include"smplaylistItem.h"
#include"items.h"
#include<player.h>

smplaylistItem::smplaylistItem(const QString &text)
  :myStandardItem(text)
{
    setIcon(decor.tagIcon(-1));
}

void smplaylistItem::generateQuery() const
{
    QString q;
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
}

int smplaylistItem::type () const
{
    return SMARTPL_ITEM;
}


QString smplaylistItem::group(QDomNode nod) const
{
    QString q;
    QStringList l;
    for(QDomNode n=nod.firstChild(); !n.isNull(); n=n.nextSibling() )	
    {
	QString name=n.nodeName();
	
	if(name==QString("group") )
	{
	    q+=group(n);
	}
	else if(name==QString("field") )
	{
	    QString s, q;
	    bool invert;
	    player::tagsEnum t;
	    queryGrt::equal comp;

	    QDomElement e=n.toElement();
	    s=e.attribute("tag");
	    
	    t=(tagsEnum)s.toInt();
	    
	    s=e.attribute("comparison");
	    comp=(queryGrt::equal)s.toInt();
	    
	    s=e.attribute("invert");
	    invert=(bool)s.toInt();
	    
	    s=e.attribute("value");
	    
	    l<<queryGrt::query(t,comp,s,invert);
	    
	}		
    }
    
    QDomElement e=nod.toElement();
    QString s=e.attribute("matchtype");
    
    if(s==QString("all") )
    {
	q+=queryGrt::connectAnd(l);
    }
    else if(s==QString("any") )
    {
      q+=queryGrt::connectOr(l);
    }
    
    return q;    
}

QDomElement smplaylistItem::xml() const
{
    return element;
}

QVariant smplaylistItem::data ( int role  ) const 
{
    if(role==ITEM_ROLE)
    {
	return QVariant(query());
    }
    return myStandardItem::data(role);
}

QString smplaylistItem::query() const
{	    

    if(_query.isEmpty() )
    {		
	generateQuery();	
    }
	    
    return _query;    
}

void smplaylistItem::setXmlElement(QDomElement el)
{
    element=el;
}

bool smplaylistItem::addRow(myStandardItem* item)
{
    return false;
}

bool smplaylistItem::removeR(int )
{
    return false;
}
