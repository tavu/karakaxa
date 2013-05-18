#ifndef TAG_EVENT_H 
#define TAG_EVENT_H
#include"dbEvents.h"
#include<tagInfo.h>
namespace database
{
    
class tagEvent :public dbEvent
{
    public:
        //set type only as TAG_INSERT TAG_REMOVED
        //if the tag have been removed, set the privious value, else set the new one
        tagEvent(int type,tagInfo tag):dbEvent(type)
        {
            _tag=tag;
        }
        
        tagInfo tag()
        {
            return _tag;
        }        
        
    private:
        tagInfo _tag;
};

class tagAltered :public dbEvent
{
    public:
        tagAltered(int type,tagInfo tag,QVariant prevValue):dbEvent(TAG_ALTERED)
        {
            _tag=tag;
            _prevValue=prevValue;
        }
        
        QVarian prevValue()
        {
            return _prevValue;
        }
        
        tagInfo tag()
        {
            return _tag;
        }
    private:
        
        tagInfo _tag;
        QVariant _prevValue;
};
    
}

#endif


