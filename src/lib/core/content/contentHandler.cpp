#include"contentHandler.h"
#include"contentList.h"
#include"contentHistory.h"
#include"contentView.h"
#include"menuList.h"
#include<QApplication>
#include<QHBoxLayout>

core::contentHandler::contentHandler ( QObject *parent ) :QObject ( parent )
{
    using namespace contentsPrivate;

    history=new contentHistory();
    contList=new contentList ( );
    contView=new contentView ();
    menuL=new menuList ();
    connect ( qApp,SIGNAL ( aboutToQuit() ),this,SLOT ( clear() ) );
}

core::contentHandler::~contentHandler()
{
    using namespace contentsPrivate;

    delete contView;
    delete contList;
    delete menuL;
    delete history;
}

QWidget *core::contentHandler::view()
{
    return contentsPrivate::contView->mainView();
}

void core::contentHandler::setView ( QTreeView *v )
{
    contentsPrivate::contView->setView ( v );
}

void core::contentHandler::setCurrentContent ( abstractContent *c,int submenu )
{
    contentsPrivate::contList->setCurrentContent ( c,submenu );
}

void core::contentHandler::setCurrentContent ( const QModelIndex &in )
{
    contentsPrivate::contView->activateContFromIndex ( in );
}

core::abstractContent *core::contentHandler::currentContent()
{
    return contentsPrivate::contList->currentContent();
}
void  core::contentHandler::addContent ( abstractContent *c,bool activate )
{
    c->setParent (contentsPrivate::contView->mainView() );
    contentsPrivate::contList->addContent ( c );

    if ( activate )
    {
        contentsPrivate::contList->setCurrentContent ( c );
    }
}

void  core::contentHandler::removeContent ( abstractContent *c )
{
    contentsPrivate::contList->removeContent ( c );
}


void  core::contentHandler::removeContent ( int pos )
{
    contentsPrivate::contList->removeContent ( pos );
}

core::abstractContent  *core::contentHandler::content ( int i )
{
    return contentsPrivate::contList->contentFromPos ( i );
}

core::abstractContent  *core::contentHandler::content ( const QModelIndex &in )
{
    return contentsPrivate::contView->contentFromIndex ( in );
}


void  core::contentHandler::addWidget ( QWidget *w,bool activate )
{
    genericContent *g=new genericContent ( w );
    addContent ( g,activate );
}

//for menus
void  core::contentHandler::addMenu ( core::abstractMenu *m )
{
    contentsPrivate::menuL->addMenu ( m );
}


void  core::contentHandler::removeMenu ( core::abstractMenu *m )
{
    contentsPrivate::menuL->removeMenu ( m );
}

void  core::contentHandler::contextMenu ( QMenu *menu, QUrl u,const QList<QUrl> &urls )
{
    contentsPrivate::menuL->contextMenu ( menu,u,urls );
}

KToolBar* core::contentHandler::toolBar()
{
    return contentsPrivate::contView->toolBar();
}

void core::contentHandler::clear()
{
    contentsPrivate::contList->clear();
}
/*
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
*/
//=================genericContent================
core::contentHandler::genericContent::genericContent ( QWidget *parent )
    :abstractContent()
{
    widget=parent;
    QHBoxLayout *hlayout = new QHBoxLayout();

    hlayout->addWidget ( widget );
    this->setLayout ( hlayout );
}

QString core::contentHandler::genericContent::genericContent::name() const
{
    if ( widget->windowTitle().isEmpty() )
        return "Unnamed";

    return widget->windowTitle();
}





namespace core
{
contentHandler *contentHdl;
}
