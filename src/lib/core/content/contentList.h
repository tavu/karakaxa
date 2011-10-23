#ifndef CONTENT_LIST_H
#define CONTENT_LIST_H
#include <qobject.h>
#include "abstractContent.h"
#include"abstractContent.h"
#include"uniqueContent.h"
#include"contentHistory.h"
namespace core
{
class contentList :public QObject
{
    Q_OBJECT
    public:
	explicit contentList(QObject* parent = 0);
	
	inline core::abstractContent *currentContent()
	{
	    return current;
	}
		
	inline core::abstractContent *previousContent()
	{
	    return previous;
	}
	
	void setCurrentContent(core::abstractContent* p,int submenuPos);
	void setCurrentContent(core::abstractContent *p)
	{
	    setCurrentContent(p,-1);
	}
	
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
	
	void removeContent(int pos);
	
	bool back();
	
	bool forward();
	
    private:
	QList<core::abstractContent*> contents;
	core::abstractContent *current;
	core::abstractContent *previous;
	QMap<QString ,core::abstractContent *> uniqueContentMap;
	contentHistory history;
	
	void setCurrentContentP(core::abstractContent *p,int n);
	
    signals:
	void contentAdded(core::abstractContent *c);
	void contentChanged(core::abstractContent *c);
	void contentRemoved(core::abstractContent *c);
	
};

extern contentList *contList;

}
#endif