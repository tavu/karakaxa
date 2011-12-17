#include"trackModel.h"
#include"urlRole.h"
#include"../viewsFunc.h"
#include<KUrl>
#include<QDebug>
using namespace audioFiles;

views::trackItem::trackItem(audioFiles::audioFile f)
  :standardItem(),
  file(f)
{
    connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(changed(audioFiles::audioFile)) );
}


QVariant views::trackItem::data(int column, int role) const
{
    if(!file.isValid())
    {
        return QVariant();
    }
    
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole || role==Qt::EditRole)
    {
	   return views::pretyTag(file.tag(column),column );	   
    }
    if(role==URL_ROLE)
    {
        KUrl u( file.path() );
        return QVariant(u);
    }
    if(role == TAG_ROLE )
    {
        return QVariant(column);
    }

    return QVariant();
}

bool views::trackItem::setData(const QVariant& value, int column, int role)
{
    if(role==Qt::DisplayRole ||role==Qt::EditRole )
    {
	file.setTag(column,value);
	if(file.error()==OK)
	{
// 	    dataChanged(column,column);
	    return true;
	}
    }
    
    return false;
}


views::trackModelItem::trackModelItem()
  :standardItem(),
  q(0)
{   
}

QVariant views::trackModelItem::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
	if (section==TRACK)
	{
	    return QVariant(QString("#") );
	}
	return QVariant(tagName( (tagsEnum)section) );
    }
    if(role==Qt::DecorationRole)
    {
	return QVariant(decor->tagIcon( section) );
    }

    return standardItem::headerData(section,orientation,role);
}


void views::trackModelItem::setQueryG(core::filesQueryGrt* qe)
{
    if(q!=0)
    {
	delete q;
    }
    q=qe;
    q->setParent(this);
    connect(q,SIGNAL(selectionMade() ),this,SLOT(addItems() ) );
    connect(q,SIGNAL(selectionCalled()),this,SLOT(clearSlot()) );
//     connect(q,SIGNAL(newItems(QVector<audioFiles::audioFile>)),this,SLOT(addItems(QVector<audioFiles::audioFile>) ),Qt::QueuedConnection );
//     connect(q,SIGNAL(inserted(audioFiles::audioFile,int) ),this,SLOT(addItem(audioFile &,int) ),Qt::QueuedConnection );
//     connect(q,SIGNAL(removed(audioFiles::audioFile,int)),this,SLOT(removeItem(audioFiles::audioFile&,int)),Qt::QueuedConnection );
    
    if(q->needUpdate() )
    {
	q->select();
    }
}

void views::trackModelItem::addItems()
{
  
    prealocateChildren(q->size() );
    beginInsertRows(0,q->size()-1 );
    
    for(int i=0;i<q->size();i++)
    {        
	audioFiles::audioFile f=q->at(i);
	standardItem *item=getItem(f);
	insert(i,item);
    }
    
    endInsertRows();        
}


void views::trackModelItem::addItem(audioFile f, int pos)
{
    standardItem *item=getItem(f);
    insertRow(pos,item);
}

void views::trackModelItem::removeItem(audioFile, int pos)
{
      removeRow(pos);
}


standardItem* views::trackModelItem::getItem(audioFile& f)
{
    return new trackItem(f);
}
