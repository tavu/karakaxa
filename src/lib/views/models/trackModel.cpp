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

}


QVariant views::trackItem::data(int column, int role) const
{
    if(!file.isValid())
    {
	return QVariant();
    }
    
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole)
    {
	   return views::pretyTag(file.tag(column),column );	   
    }
    if(role==URL_ROLE)
    {
	KUrl u( file.path() );
	return QVariant(u);
    }
    
    return QVariant();
}

bool views::trackItem::setData(const QVariant& value, int column, int role)
{
    file.setTag(column,value);
    dataChanged(column,column);
    
    return true;
}


views::trackModelItem::trackModelItem()
  :q(0)
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


void views::trackModelItem::setQueryG(core::queryGrt* qe)
{
    if(q!=0)
    {
	delete q;
    }
    q=qe;
    q->setParent(this);
    connect(q,SIGNAL(selectionMade() ),this,SLOT(addItems() ),Qt::QueuedConnection );
//     connect(q,SIGNAL(inserted(audioFiles::audioFile,int) ),this,SLOT(addItem(audioFile &,int) ),Qt::QueuedConnection );
//     connect(q,SIGNAL(removed(audioFiles::audioFile,int)),this,SLOT(removeItem(audioFiles::audioFile&,int)),Qt::QueuedConnection );
    
    if(q->needUpdate() )
    {
	q->select();
    }
}

void views::trackModelItem::addItems()
{
    clear();
    
    for(int i=0;i<q->size();i++)
    {
	audioFile *f=q->at(i);
	if(f!=0)
	{
	    standardItem *item=getItem(*f);
	    appendRow(item);
	} 	
    }    
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
