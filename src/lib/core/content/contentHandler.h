#ifndef CONTENTHANDLER_H
#define CONTENTHANDLER_H

#include"abstractContent.h"
#include <QList>
#include<QTreeWidget>
#include<QStackedWidget>
#include<QMutex>
#include <QStandardItemModel>
#include<KToolBar>
#include<KUrl>
#include"contentHistory.h"
#include"contentList.h"
#include"contentView.h"
#include"menuList.h"
// class abstractContent;
// #include<QStandardItemModel>
namespace core
{

// class abstractMenu;

// class contentHistory;

class abstractContent;

/*
 * ContentHandler provides a set of functions  that is usefull to manage the contents ,the menus and every add-on
 * without concern the indernal structure of that operation.
 */

class contentHandler
{
   
  public:	      
		
    class genericContent :public abstractContent
    {
    public:
        genericContent(QWidget *parent);
        QString name() const;

    private:
        QWidget *widget;
    };
	

  public:
    contentHandler();
    ~contentHandler();
    
    QWidget* view()
    {
	return contView->mainView();
    }
    
    void setView(QTreeView *v)
    {
	contView->setView(v);
    }
    
    void setCurrentContent(abstractContent *c,int submenu=-1)
    {
	contList->setCurrentContent(c,submenu);
    }
         
    void setCurrentContent(const QModelIndex &in)
    {
	contView->activateContFromIndex(in);
    }
    
    core::abstractContent* currentContent()
    {
      return contList->currentContent();
    }
    
    void addContent(abstractContent *c,bool activate=false)
    {
	contList->addContent(c);
	if(activate)
	{
	    contList->setCurrentContent(c);
	}
    }
    
    void removeContent(abstractContent *c)
    {
      contList->removeContent(c);
    }
    
     
    void removeContent(int pos)
    {
      contList->removeContent(pos);
    }
    
    core::abstractContent* content(int i)
    {
	return contList->contentFromPos(i);
    }
    
    core::abstractContent* content(const QModelIndex &in)
    {
	return contView->contentFromIndex(in);
    }
        
    
    void addWidget(QWidget *w,bool activate=true)
    {
	genericContent *g=new genericContent(w);
	addContent(g,activate);
    }
    
    //for menu
	
    void addMenu(core::abstractMenu* m)
    {
	menuL->addMenu(m);
    }
    
	
    void removeMenu(core::abstractMenu* m)
    {
	menuL->removeMenu(m);
    }

    void contextMenu(QMenu* menu, QUrl u,const QList<QUrl> &urls)
    {
	menuL->contextMenu(menu,u,urls);
    }
    
    KToolBar* toolBar()
    {
	return contView->toolBar();
    }
};
  
  extern contentHandler *contentHdl;
}
#endif
