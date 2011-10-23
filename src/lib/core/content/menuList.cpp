#include "menuList.h"
void core::menuList::addMenu(core::abstractMenu* m)
{
    menus.append(m);
}

void core::menuList::removeMenu(core::abstractMenu* m)
{
    int pos=menus.indexOf(m);
    menus.removeAt(pos);
}

void core::menuList::contextMenu(QMenu* menu, QUrl u,const QList<QUrl> &urls)
{
  abstractMenu::_url=u;
  abstractMenu::_urls=urls;
  
  foreach(abstractMenu *m,menus)
  {
      if(m->canShow() )	
      {
	  menu->addAction(m->action() );	
      }
  }
}

QUrl core::abstractMenu::_url;
QList<QUrl> core::abstractMenu::_urls;

namespace core
{
  menuList *menuL;
};
