#ifndef MENULIST_H 
#define MENULIST_H
#include "abstractContent.h"
#include<KUrl>
namespace core
{
  
class abstractMenu;

class menuList
{
    public:
	menuList(){}
	void addMenu(core::abstractMenu* m);
	void removeMenu(core::abstractMenu* m);
	

	//returns a menu with appropriate action for tha url.
	//the reciver must check if the menu is empty and must delete the menu later.

	void contextMenu(QMenu* menu, QUrl u,const QList<QUrl> &urls);
	
    private:
	QList<abstractMenu*>menus;
};


//This is a menu that can be shown by right click to any item.
//the views can ask for the contentHandler for an appropriate menu.
class abstractMenu :public QObject
{
    friend class menuList;
    public:
      abstractMenu() :QObject(){}      
      virtual ~abstractMenu(){}
      
      //return true if the menu can be shown for the spesific url u. 
      //the multFiles spesifies if there are more than one selected files.
      virtual bool canShow()=0;
      //return an action for the menu.
      //this object must connect the acction to the appropriate slot.
      virtual QAction* action()=0;
	 
	 static KUrl url()
	 {
		return _url;
	 }
	 
	 static QList<QUrl>urls()
	 {
		return _urls;
	 }
	 
    private:
	   static QUrl _url;
	   static QList<QUrl> _urls;
};

extern core::menuList *menuL;

};
#endif
