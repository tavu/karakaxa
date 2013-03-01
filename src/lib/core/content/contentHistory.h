#ifndef CONTENTHISTORY_H 
#define CONTENTHISTORY_H 

#include"abstractContent.h"
#include<QLinkedList>
namespace core
{

namespace contentsPrivate
{

class content_history
{
    public:
        content_history():p(0){}
	abstractContent *p;
	QVariant value;
	bool operator==(const content_history &h)
	{
	    return p==h.p;
	}
};



class contentHistory
{
    public:
        contentHistory();
        void addHistory(content_history &h);
        void addHistory(core::abstractContent *c);
        void setMaxSize(int n)
        {
            _maxSize=n;
        }

        void removeAll(abstractContent *c);

        int maxSize()
        {
            return _maxSize;
        }

        content_history back();

        content_history forword();
	
    private:
        QLinkedList<content_history> history;
        int _maxSize;
        QLinkedList<content_history>::iterator curentPos;
};//class

extern contentHistory *history;
};//contentsPrivate

};//core
#endif