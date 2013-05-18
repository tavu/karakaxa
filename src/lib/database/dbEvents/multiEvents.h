#ifndef MULTI_EVENTS_H 
#define MULTI_EVENTS_H
#include "databaseEvent.h"
#include<QLinkedList>
namespace database
{

class multiEvents :public dbEvent
{
    public:
        multiEvents();
        ~multiEvents()
        {
            foreach(dbEvent *e,eventList)
            {
                delete e;
            }
        }
        void addEvent(dbEvent *e)
        {
            eventList.append(e);
        }
         
        QLinkedList<dbEvent*> events()
        {
            return eventList;
        }
        
    private:
        QLinkedList<dbEvent*> eventList;
};

    
}
#endif
