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
// class abstractContent;
// #include<QStandardItemModel>
namespace core
{

//This is a menu that can be shown by right click to any item.
//the views can ask for the contentHandler for an appropriate menu.
class abstractMenu :public QObject
{
    public:
      abstractMenu() :QObject(){}      
      virtual ~abstractMenu(){}
      
      //return true if the menu can be shown for the spesific url u. 
      //the multFiles spesifies if there are more than one selected files.
      virtual bool canShow(QUrl &u ,bool multFiles)=0;
      //return an action for the menu.
      //this object must connect the acction to the appropriate slot.
      virtual QAction* action()=0;
};
  

class contentHandler :public QObject
{
    friend class abstractContent;
    Q_OBJECT    
    public:
	contentHandler();
	~contentHandler();
	void loadPlugins();
	abstractContent* content(const QModelIndex &index) const;
	abstractContent* currentContent() const;
	void setCurrentContent(core::abstractContent* content);

	void removeContent(abstractContent *content);
	bool isActive(QWidget *w);
	
	void setView(QTreeView* v)
	{
	    view=v;
	    view->setModel(model);
	    connect(view,SIGNAL(activated( const QModelIndex & ) ),this, SLOT(itemChanger (const QModelIndex &) ) );
	}
	
	QFrame* contentView() const;

	KToolBar* toolBar()
	{
	    return _toolBar;
	}
	
	void addMenu(abstractMenu *m);
	void removeMenu(abstractMenu *m);
	
	//returns a menu with appropriate action for tha url.
	//the reciver must check if the menu is empty and must delete the menu later.
	void contextMenu(QMenu* menu, QUrl u, bool multFiles);
	
    private:
	void activateContent(abstractContent*,bool);
		
	
	QStackedWidget *stack;
	QList<abstractContent * > contentList;
	QList<abstractMenu * > menuList;
	
	KToolBar *_toolBar;

	
	
	
	QMutex mutex;
	QList<abstractContent*>history;
	QStandardItemModel *model;
	QTreeView *view;
      
		
    class genericContent :public abstractContent
    {
    public:
        genericContent(QWidget *parent);
        QString name() const;

    private:
        QWidget *widget;
    };
	

  public slots:

    void itemChanger(const QModelIndex &);
    void addContent(abstractContent *,bool activate=false);
    void addWidget(QWidget *w,bool activate=true);



};





    extern contentHandler *contentHdl;

}
#endif
