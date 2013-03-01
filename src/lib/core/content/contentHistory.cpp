#include"contentHistory.h"

core::contentsPrivate::contentHistory::contentHistory():_maxSize(5)
{
    curentPos=history.end();
}

void core::contentsPrivate::contentHistory::addHistory(core::contentsPrivate::content_history& h)
{
    if(history.size()==_maxSize)
    {
	history.erase(history.begin() );
    }
    
    if(curentPos!=history.end() )
    {
        curentPos++;
        if(curentPos!=history.end() )
        {
            history.erase(curentPos,history.end());
        }
    }
    history.append(h);
    
    curentPos=history.end();
}

void core::contentsPrivate::contentHistory::addHistory(core::abstractContent* c)
{
    content_history h;
    h.value=c->state();
    h.p=c;
    addHistory(h);
}


core::contentsPrivate::content_history core::contentsPrivate::contentHistory::back()
{    
    if(!history.isEmpty() && curentPos!=history.begin() )
    {
	curentPos--;
	return *curentPos;
    }
    
    return content_history();
}


core::contentsPrivate::content_history core::contentsPrivate::contentHistory::forword()
{
    if(curentPos!=history.end() )
    {
	curentPos++;
	return *curentPos;
    }
    
    return content_history();
}

void core::contentsPrivate::contentHistory::removeAll(core::abstractContent* c)
{
    if(curentPos!=history.end() )
    {
        curentPos++;
        if(curentPos!=history.end())
        {
            history.erase(curentPos,history.end());
        }
    }
    QLinkedList<core::contentsPrivate::content_history>::iterator it;
    content_history h;
    h.p=c;
    history.removeAll(h);
    
    curentPos=history.end();
}

namespace core
{
namespace contentsPrivate
{
    contentHistory *history;
}
}