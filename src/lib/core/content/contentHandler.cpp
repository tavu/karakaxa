#include"contentHandler.h"
#include<QModelIndex>
#include<QVBoxLayout>
#include<QFont>
#include <QPluginLoader>
#include<QDebug>
#include"abstractContent.h"
#include<QApplication>
#include "contentView.h"
#define MAX_HS 20
#define SIZE QSize(20,20)

core::contentHandler::contentHandler()
{
    core::contList=new contentList;
    core::contView=new contentView;
    core::menuL=new menuList;
}

core::contentHandler::~contentHandler()
{
    delete contList;
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





namespace core
{
  contentHandler *contentHdl;
}