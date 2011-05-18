#ifndef MYSTANDARDMODELITEM_H
#define MYSTANDARDMODELITEM_H
#include<core.h>
#include"QDomElement"

class folderItem :public core::xmlItem
{ 
    public:
	folderItem(QDomDocument &doc,const QString &text);
	folderItem(const QDomElement &el);
	
	virtual int type () const;
	
	virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const;

	virtual bool canFetchMore () const;      
	virtual void fetchMore ();
	
	virtual bool hasChildren() const
	{
	    return element.hasChildNodes();
	}
	
	void setSizeHint(const QSize &s)
	{
	    sizeHint=s;
	}
//  	static const int FOLDER_ITEM;
    protected:
      QSize sizeHint;
};

class smplalistHead :public folderItem
{
    public:
	smplalistHead(const QDomElement &el)
	: folderItem(el)
	{}
	
	QVariant data (int column, int role = Qt::UserRole + 1 ) const;

	
};


#endif