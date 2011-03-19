#include"contentHandler.h"
#include<QModelIndex>
#include<QHBoxLayout>
#include<QFont>
#include <QPluginLoader>
#include<QDebug>
#include<content/defaultContent.h>
#define MAX_HS 20
player::contentHandler::contentHandler()
        :QObject()
{
}

void player::contentHandler::loadDefault()
{

    library *l=new library();
    configureContent *c=new configureContent();
    folderContent *f=new folderContent();
    playlistContent *pl=new playlistContent();

     addContent(l);
     addContent(f);
     addContent(pl);
     addContent(c);
    
     loadPlugins();
}

void player::contentHandler::loadPlugins()
{
  //this is a test
  QString s("/home/tavu/player/trunk/plugin/libplugin.so" );
  QPluginLoader loader(s);
  
  QObject *b=loader.instance();
  qDebug()<<"B "<<b;
  abstractContent *plugin=dynamic_cast<abstractContent *>(b);
  if(plugin)
  {
      addContent(plugin);
  }
  
}

void player::contentHandler::init(QTreeWidget *tree , QStackedWidget *stack)
{

    this->tree=tree;
    this->stack=stack;
    connect( tree, SIGNAL( activated ( const QModelIndex & ) ) ,this, SLOT( itemChanger (const QModelIndex &) ) );

    QFont f=item.font(0);

    f.setPixelSize(14);
//      f.setBold(true);
    item.setFont(0,f);

}


abstractContent* player::contentHandler::content(const QModelIndex &index) const
{
    if(!index.isValid() )
    {
	return 0;
    }    
    abstractContent *c=0;
    QModelIndex in;

    if (index.parent().isValid() )
    {
        in=index.parent();
    }
    
    if(in.row()<contentList.size() )
    {
        c=contentList.at(index.row() );
    }
    return c;
}

bool player::contentHandler::isActive(QWidget *w)
{
    if(w==stack->currentWidget() )
    { 
      return true;
    }
    
    return false;
}


void player::contentHandler::itemChanger(const QModelIndex &index)
{
    abstractContent *parent;
    QModelIndex parentItem=index.parent();

    if (parentItem.isValid() )
    {
        parent=contentList.at(parentItem.row() );     
	stack->setCurrentWidget(parent);
        parent->update(index.row() );
    }
    else
    {
        parent=contentList.at(index.row() );
        stack->setCurrentWidget(parent);
	parent->update(-1);
    }

    history.append(parent);
    if (history.size()>MAX_HS)
    {
        history.removeLast();
    }
}

void player::contentHandler::addContent(abstractContent *content, bool activate)
{
    QTreeWidgetItem *i=content->item();
    contentList.append(content);
    
    
    stack->addWidget(content);
    tree->addTopLevelItem(i);
    
    if (activate)
    {
        tree->setCurrentItem(i);
        stack->setCurrentWidget(content);
    }
}

void player::contentHandler::removeContent(abstractContent *content)
{
    history.removeAll(content);
    int pos=contentList.indexOf(content);
    if (stack->currentWidget()==content)
    {
        QTreeWidgetItem *item;
	abstractContent *c;
        if (! history.isEmpty() )
        {
            item=tree->itemAt(contentList.indexOf(history.last()),0);
	    c=history.last();
        }
        else
        {
            item=tree->itemAt(0,0 );
	    c=contentList.at(0);
        }
        tree->setCurrentItem(item);
        stack->setCurrentWidget(c);
	c->update(-1);
    }

    tree->takeTopLevelItem(pos);
    contentList.removeAt(pos);
    content->deleteLater();
}

void player::contentHandler::addWidget(QWidget *w, bool activate)
{
    genericContent *g=new genericContent(w);
    addContent(g,activate);

}

//=================genericContent================
player::contentHandler::genericContent::genericContent(QWidget *parent)
        :abstractContent()
{
    widget=parent;
    QHBoxLayout *hlayout = new QHBoxLayout();

    hlayout->addWidget(widget);
    this->setLayout(hlayout);
}

QString player::contentHandler::genericContent::genericContent::name() const
{
    if ( widget->windowTitle().isEmpty() )
        return "Unnamed";

    return widget->windowTitle();
}
