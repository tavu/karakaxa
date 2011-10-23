#include"contentHistory.h"

core::contentHistory::contentHistory()
{
    curentPos=history.end();
}

void core::contentHistory::addHistory(core::content_history& h)
{
    if(history.size()==_maxSize)
    {
	history.erase(history.begin() );
    }
    
    history.erase(curentPos,history.end());
    history.append(h);
    
    curentPos=history.end();
}

void core::contentHistory::addHistory(core::abstractContent* c)
{
    content_history h;
    h.value=c->state();
    h.p=c;
    addHistory(h);
}


core::content_history core::contentHistory::back()
{    
    if(!history.isEmpty() && curentPos!=history.begin() )
    {
	curentPos--;
	return *curentPos;
    }
    
    return content_history();
}

core::content_history core::contentHistory::forword()
{
    if(curentPos!=history.end() )
    {
	curentPos++;
	return *curentPos;
    }
    
    return content_history();
}

void core::contentHistory::removeAll(core::abstractContent* c)
{
    history.erase(curentPos,history.end());
    QLinkedList<core::content_history>::iterator it;
    content_history h;
    h.p=c;
    history.removeAll(h);
    
    curentPos=history.end();
}

