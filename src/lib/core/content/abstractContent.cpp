#include"abstractContent.h"
#include"contentHandler.h"
#include<QHBoxLayout>
#include"contentHistory.h"
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
	if(!icon().isNull() )
	{
	    _item=new QStandardItem( icon(),name() );
	}
	else
	{
	   _item=new QStandardItem(name() );
	}
	
	_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
        _item->setEditable(false);
    }
    
    return _item;
}

void core::abstractContent::addSubmenu(const QString& s, QIcon icon)
{
    QStandardItem *it;
    it=new QStandardItem(icon,s);
    it->setEditable(false);
    item()->appendRow(it);
}

void core::abstractContent::addSubmenu(const int pos, const QString& s, QIcon icon)
{
    QStandardItem *it=new QStandardItem(s);
    it->setEditable(false);
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

void core::abstractContent::loaded()
{
}


void core::abstractContent::hiden()
{
}


bool core::abstractContent::isActive()
{
    return core::contentHdl->currentContent()==this;
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
    unloaded();
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
