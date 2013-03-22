#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include<QAction>
#include<QUrl>
#include<QList>
#include<KUrl>

namespace core
{
namespace contentsPrivate
{
    class menuList;
}
//This is a menu that can be shown by right click to any item.
//the views can ask for the contentHandler for an appropriate menu.
class abstractMenu :public QObject
{
    friend class contentsPrivate::menuList;
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
};//class

}//core

#endif
