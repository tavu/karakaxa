#ifndef ABSTRACTMID_H
#define ABSTRACTMID_H
#include<QWidget>
#include<QMenu>
#include<QAction>
#include<KToolBar>
#include<QStandardItem>
#include <QLinkedList>
// #include"contentHandler.h"
// #include "contentHandler.h"

namespace core
{

class contentHandler;

class abstractContent :public QWidget
{    
    Q_OBJECT
    
    friend class core::contentHandler;

    public:
	abstractContent(QWidget *parent=0);

	virtual ~abstractContent();

	//return the visible name of the content
	virtual QString name()const =0;

	//return the icon of the content
	virtual QIcon icon() const;

	void showMenu(const QPoint p);
	bool isActive();
	
	//this function will load a content to the contentHandler
	void load();
	//this function will unload a content
	void unload();
	bool isLoaded()
	{
	    return _isLoaded;
	}
    // 	  virtual int childrenNum() const;
    protected:

	QMenu menu;
	void addSubmenu(const QString &s,QIcon icon=QIcon() );
	void addSubmenu(const int pos, const QString &s,QIcon icon=QIcon() );	
	void removeSubmenu(const int pos);
	KToolBar *toolBar;
	QAction *toolBarAction;
	
	//this function is called after the content have been loaded
	virtual void loaded();
	//this function is called before the content unloads
	virtual void unloaded()
	{}
	//thes function is called after the content have been deactivated.
	virtual void hiden();

	//this function is called after the content have been activated.
	virtual void activated(const int n);


    private:
	QStandardItem *_item;
	void updateContent(QStandardItem*);
	void hideContent();
	QLinkedList<QWidget *> widgets;
	QStandardItem* item();
	void unloadContent();
	void loadContent();
	bool _isLoaded;
};


// Q_DECLARE_INTERFACE(abstractContent,"abCont");

};
#endif
