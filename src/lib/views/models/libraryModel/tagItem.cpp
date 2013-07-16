#include"tagItem.h"
#include "tagItemHead.h"
#include<Basic/tagsTable.h>
#include "trackItem.h"

views::tagItem::tagItem(tagSelector *s) :standardItem(),_ts(s)
{
}

views::tagItem::tagItem() :standardItem(),_ts(0)
{

}

views::tagItem::~tagItem()
{
    clear();
}



bool views::tagItem::canFetchMore() const
{
    if(rowCount()!=0)
    {
        return false;
    }
    
    int t=nextData();
    if(t==Basic::INVALID)
    {
        return false;
    }
    
    return true;
}

void views::tagItem::fetchMore()
{
    if(rowCount()!=0)
    {
        return ;
    }
    qDebug()<<"FETCH";
    int t=nextData();
    if(t==Basic::INVALID)
    {
        return ;
    }
    
    _ts->populate(t);
    
    appendData(t);
}

views::tagItem* views::tagItem::head()
{
    return 0;
}


int views::tagItem::columnCount() const
{
    return 1;
}

QVariant views::tagItem::data(int column, int role) const
{
    if(column!=0)
    {
        return QVariant();
    }
    
    if(role==Qt::DisplayRole)
    {
        return _ts->data();
    }
    
    if(role==Qt::DecorationRole)
    {
        return _ts->icon();
    }
    return QVariant();
}

views::tagItem* views::tagItem::parentItem() const
{
    return qobject_cast<tagItem*>(QObject::parent() );
}


int views::tagItem::nextData() const
{
    int depth=0;
    const tagItem *i=this;

    while(i->parentItem()!=0)
    {
        
        i=i->parentItem();
        depth++;
    }    
    
    const tagItemHead *h= dynamic_cast<const tagItemHead*>(i);
    if(h==0)
    {
        return Basic::INVALID;
    }
    
    if(h->tagList().size() <depth )
    {
        return Basic::INVALID;
    }
   
    return h->tagList().value(depth);
    
    
}

void views::tagItem::appendData(int t)
{
    QList<standardItem*>l;
    
    QVector<views::tagSelector*>* v=_ts->tags(t);
    if(v==0)
    {
        qDebug()<<"tag selecto has no data of tag "<<t;
        return ;
    }
    
    for(int i=0;i<v->size();i++)
    {
        l<<newItemInstance(v->value(i));
    }
    
    insertRows(0,l);
    
}

void views::tagItem::update()
{
    clear();
    fetchMore();
}


standardItem* views::tagItem::newItemInstance(views::tagSelector* s)
{
    if(s->type()==Basic::FILES)
    {
        return new trackItem(s->tag());
    }
    else
    {
        return new tagItem(s);
    }
}


