#include"tagItem.h"
#include "tagItemHead.h"
#include<Basic/tagsTable.h>
#include "trackItem.h"
#include "headerItem.h"
#include<files/tagInfo.h>
#include<database/queries/queryTypes.h>
#include<database/queries/provider/queryProvider.h>
#include<database/queries/matchQuery.h>
#include<database/queries/tagQuery.h>

views::tagItem::tagItem(audioFiles::tagInfo &info) :standardItem(),_info(info)
{
    _sort=-1;
    _sortOrder=Qt::AscendingOrder;
}

views::tagItem::tagItem() :standardItem()
{
    _sort=-1;
    _sortOrder=Qt::AscendingOrder;
}

views::tagItem::~tagItem()
{
    clear();
}

void views::tagItem::sort(int column, Qt::SortOrder order)
{

//     _sort=headItem()->headerData(column,Qt::Horizontal,TAG_ROLE).toInt();
    _sort=column;
    _sortOrder=order;

    if(rowCount()==0)
        return;

    
    int d=nextData();
        
    if(d==Basic::FILES && rowCount()!=0)
    {
        clear();     
        populate();
    }
    else   
    {   
        foreach(standardItem *item, children)
        {
            item->sort(column,order);
        }
    }
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

    
    populate();
//     
//     appendData(t);
}

bool views::tagItem::populate()
{
    int type=nextData();
    if(type==Basic::INVALID)
    {
        return false;
    }
    
    if(type<0||type>Basic::FILES)
    {
        qDebug()<<"invalid type:"<<type;
        return false;
    }
    
    database::queryProvider *pr=new database::queryProvider(type);
    database::abstractQuery *f=filter();
    /*
    tagItem* parent=parentItem();
    if(parent!=0)
    {
        f=parent->filter();
    }
    else
    {
        //this is the head item
        f=filter();
    }
      */  
    int sort;
    if(type==Basic::FILES)
    {
        sort=headItem()->headerData(_sort,Qt::Horizontal,TAG_ROLE).toInt();
        if(sort==Basic::INVALID)
        {
            sort=Basic::TRACK;
        }
    }
    else
    {
        sort=type;
    }
    
    if(pr->select(f,sort,_sortOrder) !=Basic::OK )
    {
        qDebug()<<"query data provider returned false";
        qDebug()<<pr->lastErrorStr();
        delete pr;
        return false;
    }
        
    QList<audioFiles::tagInfo> results=pr->results();    
    QList<standardItem*>l;            
        
    foreach(audioFiles::tagInfo info,results)
    {
        l<<newItemInstance(info);
    }

    insertRows(0,l);
    _isDirty=false;
    return true;    
}

views::tagItem* views::tagItem::parentItem() const
{
    return dynamic_cast<tagItem*>(QObject::parent() );
}


database::abstractQuery* views::tagItem::filter() const
{
    tagItem *parent=parentItem();
    
    database::abstractQuery *parentQ=0;
    if(parent!=0)
    {
        parentQ=parent->filter();
    }
    
    database::matchQuery *match=new database::matchQuery(database::AND);
    if(parentQ!=0)
    {
        match->append(parentQ);
    }
    
    if(_info.type()!=Basic::INVALID && _info.type()!=Basic::FILES )
    {
        database::abstractQuery *q;
        q=new database::tagQuery( _info.type(),database::EQUAL,_info.data() );
        match->append(q);
    }
    return match;
}


int views::tagItem::columnCount() const
{
    return 1;
}

QVariant views::tagItem::data(int column, int role) const
{
    if(role==TAG_ROLE)
    {
        if(column==0)
        {
            return QVariant(_info.type());
        }
        else
        {
            return QVariant(Basic::INVALID);
        }
    }
    
    if(role==ID_ROLE)
    {
        return QVariant(_info.property(Basic::ID) );
    }
    
    if(column!=0)
    {
        return QVariant();
    }
    
    if(role==Qt::DisplayRole)
    {
        return views::pretyTag(_info.data(),_info.type() );
    }
    
    if(role==Qt::DecorationRole)
    {
        QString s=_info.property(Basic::IMAGE).toString();
        
        if(!s.isEmpty())
        {
            return QPixmap(s);
        }
        return views::decor->tagIcon(_info.type());
    }
    
    
    return QVariant();
}

int views::tagItem::nextData() const
{
    tagItemHead *head=static_cast<tagItemHead*>(headItem());
        
    if(head->tagList().size() <= depth() +1 )
    {
        return Basic::INVALID;
    }
   
    return head->tagList().value(depth()+1 );
}

void views::tagItem::update()
{
    clear();
    fetchMore();
}


standardItem* views::tagItem::newItemInstance(audioFiles::tagInfo &info)
{
    if(info.type()==Basic::FILES)
    {
        return new trackItem(info);
    }
    else
    {
        return new tagItem(info);
    }
}

Qt::ItemFlags views::tagItem::flags(int column) const
{
    return standardItem::flags(column)& ~Qt::ItemIsEditable;
}

void views::tagItem::insert(int row, standardItem* item)
{
    standardItem::insert(row, item);
    item->sort(_sort,_sortOrder);
}

