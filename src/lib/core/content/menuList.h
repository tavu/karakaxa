#ifndef MENULIST_H 
#define MENULIST_H
#include "abstractContent.h"
#include<KUrl>

namespace core
{
  
class abstractMenu;

namespace contentsPrivate
{
    
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
};//class
extern menuList *menuL;
};//contentsPrivate

};//core
#endif
