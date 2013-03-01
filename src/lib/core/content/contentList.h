#ifndef CONTENT_LIST_H
#define CONTENT_LIST_H
#include <qobject.h>
#include "abstractContent.h"
#include"abstractContent.h"
#include"uniqueContent.h"
#include"contentHistory.h"
namespace core
{
    
namespace contentsPrivate
{

class contentList :public QObject
{    
    public:
	explicit contentList();
	
	inline core::abstractContent *currentContent()
	{
	    return current;
	}
	
	void setCurrentContent(core::abstractContent* p,int submenuPos=-1);
	
	void addContent(core::abstractContent *c);
    
	abstractContent* contentFromPos(int i)
	{
	    if(i<0||i>=contents.size() )
	    {
		return 0;
	    }
	    
	    return contents[i];
	}
	
	void removeContent(core::abstractContent *p);
        void clear();
	
	void removeContent(int pos);
	
	bool back();
	
	bool forward();
	
    private:
        QList<core::abstractContent*> contents;
        core::abstractContent *current;
        QMap<QString ,core::abstractContent *> uniqueContentMap;
        contentHistory history;
	
	void setCurrentContentP(core::abstractContent *p,int n);

};//class

extern contentList *contList;

};//contentsPrivate

};//core
#endif