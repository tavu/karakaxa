#include"smplaylistItem.h"
#include"items.h"
#include<core.h>
#include<views.h>

using namespace core;
smplaylistItem::smplaylistItem(QDomDocument &doc, const QString &text)
  :xmlItem(doc,QString("smartPlaylist") )
{
     _query.clear();
     setData(QVariant("name"),0,attributeName);
     setData(QVariant(text), 0 ,attributeRole() ); 
//     setIcon(decor.tagIcon(-1));
}

smplaylistItem::smplaylistItem(const QDomElement &el)
  :xmlItem(el)
{
    _query.clear();
    setData(QVariant("name"),0,attributeName);
}    

void smplaylistItem::generateQuery() const
{  
    QString q;
    QDomElement el=element.firstChildElement();
    _query =group(el);
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


QString smplaylistItem::group(QDomNode nod) const
{
    qDebug()<<"QQ ";
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
    qDebug()<<"QQ "<<q;
    
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
	return QVariant(query());
    }
    return xmlItem::data(column,role);
}

QString smplaylistItem::query() const
{	    

    if(_query.isEmpty() )
    {		
	generateQuery();	
    }
	    
    return _query;    
}

// const int smplaylistItem::SMARTPL_ITEM=core::xmlItem::XmlType+2;