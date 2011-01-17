#ifndef MYSTANDARDMODELITEM_H
#define MYSTANDARDMODELITEM_H
#include"myStandardModel.h"
#include"QDomElement"

class folderItem :public myStandardItem
{
    public:
	folderItem(const QString &text);
	folderItem(const QDomElement &el);
	
	virtual int type () const;
	virtual QDomElement xml() const;
	
	virtual bool removeR(int);
	virtual bool addRow(myStandardItem *item);
	virtual void setData ( const QVariant & value, int role = Qt::UserRole + 1 );
	
	virtual bool hasChildr() const;
	virtual bool canFetchMore () const;      
	virtual void fetchMore ();
	
    protected:
      QDomElement element;
};


#endif