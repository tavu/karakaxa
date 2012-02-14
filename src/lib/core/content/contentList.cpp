#include"contentList.h"
#include"../status/playerStatus.h"
core::contentList::contentList(QObject* parent): QObject(parent),current(0),previous(0)
{

}

void core::contentList::setCurrentContent(core::abstractContent* p,int submenuPos)
{
    if(!contents.contains(p) )
    {
	status->addError(tr("Could not change content") );
    }
    
    setCurrentContentP(p,submenuPos);    
    history.addHistory(p);
}

void core::contentList::setCurrentContentP(core::abstractContent* p,int n)
{
    if(current!=0)
    {
       current->hiden();;
    }
    
    previous=current;
    current=p;
    p->activated(n);        
    emit contentChanged(current);    
}


void core::contentList::addContent(core::abstractContent* c)
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
    
    emit contentAdded(c) ;    
    c->loaded();
}

void core::contentList::removeContent(core::abstractContent* p)
{
    int pos=contents.indexOf(p);
    removeContent(pos);
}

void core::contentList::removeContent(int pos)
{
    if(pos<0||pos>=contents.size() )
    {
        return ;
    }        
    
    abstractContent *p=contents[pos];
    p->_isLoaded=false;
    p->unloaded();
    contents.removeAt(pos);        
  
    uniqueContent *uc=dynamic_cast<uniqueContent*>(p);
    if(uc!=0)
    {
        uniqueContentMap.remove(uc->uniqueName() );
    }
    
    history.removeAll(p);
    
    if(previous==p)
    {
        previous=0;
    }
    if(currentContent()==p)
    {
        back();
    }
    
    emit contentRemoved(p);
    
    p->deleteLater();;  
}

void core::contentList::clear()
{
    foreach(abstractContent *p,contents)
    {        
        p->unloaded();
        delete p;
    }
    contents.clear();
    uniqueContentMap.clear();
}



bool core::contentList::back()
{
    content_history h=history.back();
    if(h.p==0)
    {
	return false;
    }
    
    setCurrentContentP(h.p,-1);
    return true;    
}

bool core::contentList::forward()
{
    return false;
}


namespace core
{
     contentList *contList;
}