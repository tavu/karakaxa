#ifndef TAG_EVENT_H 
#define TAG_EVENT_H
#include"dbEvents.h"

namespace database
{
    
class tagEvent :public dbEvent
{
    public:
        tagEvent(int type,int tag):dbEvent(type)
        {
            _tag=tag;
        }
        
        int tag()
        {
            return _tag;
        }        
        
    private:
        int _tag;
};

    
}

#endif


