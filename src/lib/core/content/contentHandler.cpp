#include"contentHandler.h"
#include<QModelIndex>
#include<QVBoxLayout>
#include<QFont>
#include <QPluginLoader>
#include<QDebug>
#include"abstractContent.h"
#include<QApplication>
#define MAX_HS 20

core::contentHandler::contentHandler()
        :QObject()
{
    model=new QStandardItemModel(this);
    stack=new QStackedWidget();
    stack->setMinimumSize(QSize(0,0) );
    _toolBar=new KToolBar( 0,true,false );
    _toolBar->setStyleSheet("QToolBar {background-color: transparent; }");
    _toolBar->setAutoFillBackground(true);
}

QFrame* core::contentHandler::contentView() const
{
    QFrame *f=new QFrame();
    QVBoxLayout *layout=new QVBoxLayout(f);
    layout->addWidget(_toolBar);
    layout->addWidget(stack);
    f->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    return f;
}

core::contentHandler::~contentHandler()
{
    delete stack;
}


void core::contentHandler::loadPlugins()
{
  //this is a test
  QString s("/home/tavu/player/trunk/plugin/libplugin.so" );
  QPluginLoader loader(s);
  
  QObject *b=loader.instance();

  abstractContent *plugin=dynamic_cast<abstractContent *>(b);
  if(plugin)
  {
      addContent(plugin);
  }
  
}

core::abstractContent* core::contentHandler::content(const QModelIndex &index) const
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
        c=contentList[index.row() ];
    }
    return c;
}

bool core::contentHandler::isActive(QWidget *w)
{
    if(w==stack->currentWidget() )
    { 
      return true;
    }
    
    return false;
}


void core::contentHandler::itemChanger(const QModelIndex &index)
{
    if(!index.isValid() )
    {
	 return;
    }
    
    abstractContent *content;
    if(index.parent().isValid() )
    {
	content=contentList.at(index.parent().row());
    }
    else
    {
	content=contentList.at(index.row());
    }
    
    if(currentContent()==content && view->isExpanded(index) )
    {
	   view->collapse(index);
    }
    else
    {    
	   view->expand(index);
    }

    activateContent(content,true);
    content->updateContent(model->itemFromIndex(index) );
}

core::abstractContent* core::contentHandler::currentContent() const
{
    QWidget *w=stack->currentWidget();
    
    if(w!=0)
    {
	return static_cast<abstractContent*>(w);
    }
    return 0;
}

void core::contentHandler::activateContent(abstractContent *content ,bool save)
{
    abstractContent *c=currentContent();
    
    if(c!=0)
    {
	c->hideContent();
    }    
    
    stack->setCurrentWidget(content);
    
    if(save)
    {
	history.append(content);
	if (history.size()>MAX_HS)
	{
	    history.removeLast();
	}
    }
}

void core::contentHandler::setCurrentContent(abstractContent *content)
{
     view->setCurrentIndex( model->indexFromItem(content->item()) );
     activateContent(content,true);	
     content->updateContent(content->item() );
}


void core::contentHandler::addContent(abstractContent *content, bool activate)
{
    contentList.append(content);
        
    stack->addWidget(content);
    model->appendRow( content->item() );
    content->setParent(stack);
    content->setPalette(stack->palette() );
    content->setMinimumSize(QSize(0,0) );
    content->loaded();
    
    
    if(content->toolBar!=0)
    {
	   content->toolBar->setVisible(false);
	   content->toolBar->setAutoFillBackground(true);
// 	   content->toolBar->setStyleSheet("QToolBar {background-color: transparent; }");
	   QAction *a=_toolBar->addWidget(content->toolBar);
	   content->toolBarAction=a;
	   a->setVisible(false);
	   content->toolBar->setVisible(true);
    }
    
    if (activate)
    {
        view->setCurrentIndex( model->indexFromItem(content->item()) );
        activateContent(content,true);
	   content->updateContent(content->item() );
    }
}

void core::contentHandler::removeContent(abstractContent *content)
{    
    history.removeAll(content);
    if (isActive(content) )
    {
	abstractContent *c=0;
        if (! history.isEmpty() )
        {
	    c=history.last();
        }
        else
        {
	    if(!contentList.isEmpty() )
	    {
		c=contentList.at(0);
	    }
        }        
        if(c!=0)
	{	  
	  activateContent(c,false);
	  view->setCurrentIndex( model->indexFromItem(c->item()) );
	  c->updateContent(c->item() );
	}
    }

    content->unloadContent();
    int pos=contentList.indexOf(content);
    
    model->removeRow(pos);

    contentList.removeAt(pos);
    
    content->deleteLater();
}

void core::contentHandler::addWidget(QWidget *w, bool activate)
{
    genericContent *g=new genericContent(w);
    addContent(g,activate);

}

//=================genericContent================
core::contentHandler::genericContent::genericContent(QWidget *parent)
        :abstractContent()
{
    widget=parent;
    QHBoxLayout *hlayout = new QHBoxLayout();

    hlayout->addWidget(widget);
    this->setLayout(hlayout);
}

QString core::contentHandler::genericContent::genericContent::name() const
{
    if ( widget->windowTitle().isEmpty() )
        return "Unnamed";

    return widget->windowTitle();
}

void core::contentHandler::addMenu(core::abstractMenu* m)
{
    mutex.lock();
    menuList.append(m);
    mutex.unlock();
}

void core::contentHandler::removeMenu(core::abstractMenu* m)
{
    mutex.lock();
    int pos=menuList.indexOf(m);
    menuList.removeAt(pos);
    mutex.unlock();
}

void core::contentHandler::contextMenu(QMenu* menu, QUrl u, bool multFiles)
{
  foreach(abstractMenu *m,menuList)
  {
      if(m->canShow(u,multFiles) )	
      {
	menu->addAction(m->action() );	
      }
  }
}


namespace core
{
  contentHandler *contentHdl;
}