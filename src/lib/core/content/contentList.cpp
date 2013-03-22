#include"contentList.h"
#include"contentView.h"
#include"../status/playerStatus.h"
core::contentsPrivate::contentList::contentList(): QObject(),current(0)
{

}

void core::contentsPrivate::contentList::setCurrentContent(core::abstractContent* p,int submenuPos)
{
    if(!contents.contains(p) )
    {
	status->addError(tr("Could not change content") );
        return ;
    }
    
    setCurrentContentP(p,submenuPos);
    history.addHistory(p);    
}

void core::contentsPrivate::contentList::setCurrentContentP(core::abstractContent* p,int n)
{
    if(current!=0)
    {
       current->hiden();
    }
    abstractContent *prev=current;
    
    current=p;
    p->activated(n);
    contView->contentActivated(current,prev);
}


void core::contentsPrivate::contentList::addContent(core::abstractContent* c)
{    
    uniqueContent *uc=dynamic_cast<uniqueContent*>(c);
    if(uc!=0)
    {
        if(uniqueContentMap[uc->uniqueName()] !=0)
        {
            return ;
        }
        uniqueContentMap.insert(uc->uniqueName(),c);
    }
    
    contents.append(c);
    contView->contentAdded(c);
//     emit contentAdded(c) ;    
    c->loaded();
}

void core::contentsPrivate::contentList::removeContent(core::abstractContent* p)
{
    int pos=contents.indexOf(p);
    removeContent(pos);
}

void core::contentsPrivate::contentList::removeContent(int pos)
{
    if(pos<0||pos>=contents.size() )
    {
        return ;
    }        
    
    abstractContent *p=contents[pos];
    p->unloadContent();
    contents.removeAt(pos);        
  
    uniqueContent *uc=dynamic_cast<uniqueContent*>(p);
    if(uc!=0)
    {
        uniqueContentMap.remove(uc->uniqueName() );
    }
    
    history.removeAll(p);
    
    if(currentContent()==p)
    {
        back();
    }
    contView->contentRemoved(p);
//     emit contentRemoved(p);
    p->deleteLater();
}

void core::contentsPrivate::contentList::clear()
{
    foreach(abstractContent *p,contents)
    {        
        p->unloaded();
        delete p;
    }
    contents.clear();
    uniqueContentMap.clear();
}



bool core::contentsPrivate::contentList::back()
{
    content_history h=history.back();
    if(h.p==0)
    {
	return false;
    }
    
    setCurrentContentP(h.p,-1);
    return true;    
}

bool core::contentsPrivate::contentList::forward()
{
    return false;
}


namespace core
{

namespace contentsPrivate
{
    contentList *contList;
}

}