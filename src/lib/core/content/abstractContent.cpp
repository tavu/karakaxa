#include"abstractContent.h"
#include"contentHandler.h"
#include<QHBoxLayout>
// #include"../player.h"

core::abstractContent::abstractContent(QWidget *parent)
        :QWidget(parent),
        toolBar(0),
        _isLoaded(false),
        _item(0)
{
    
}

QIcon core::abstractContent::icon() const
{
    return QIcon();
}


core::abstractContent::~abstractContent()
{
}

QStandardItem* core::abstractContent::item()
{   
    if(_item==0)
    {
// 	_item=new QStandardItem( name() );
	if(!icon().isNull() )
	{
	    _item=new QStandardItem( icon(),name() );
	}
	else
	{
	   _item=new QStandardItem(name() );
	}
    }
    
    return _item;
}

void core::abstractContent::addSubmenu(const QString& s, QIcon icon)
{
    QStandardItem *it;
    if(!icon.isNull() )
    {      
	it=new QStandardItem(s);
    }
    else
    {
	it=new QStandardItem(icon,s);
    }
    item()->appendRow(it);
}

void core::abstractContent::addSubmenu(const int pos, const QString& s, QIcon icon)
{
//     QStandardItem *it=new QStandardItem(icon,s);
    QStandardItem *it=new QStandardItem(s);
    _item->insertRow(pos,it);
}

void core::abstractContent::removeSubmenu(const int pos)
{
    _item->removeRow(pos);
}


void core::abstractContent::updateContent(QStandardItem *i)
{
    if(toolBar!=0 )
    {
	toolBarAction->setVisible(true);
    }
    
    if( i->parent()==0 )
    {
	activated(-1);
    }
    else
    {
	activated(i->row() );
    }    
}

void core::abstractContent::activated(const int )
{
}

void core::abstractContent::hideContent()
{
    if(toolBar!=0 )
    {
	toolBarAction->setVisible(false);
    }
    hiden();
}

void core::abstractContent::loaded()
{
}


void core::abstractContent::hiden()
{
}


bool core::abstractContent::isActive()
{
//   return false;
  return core::contentHdl->isActive(this);
}


void core::abstractContent::showMenu(const QPoint p)
{
    if (!menu.isEmpty() )
    {
        menu.popup( p);
    }

}

void core::abstractContent::unloadContent()
{    
    _isLoaded=false;
}

void core::abstractContent::load()
{
    if(!isLoaded() )
    {
      contentHdl->addContent(this);    
    }
}

void core::abstractContent::loadContent()
{    
    _isLoaded=true;
    loaded();
}

void core::abstractContent::unload()
{
    contentHdl->removeContent(this);   
}
