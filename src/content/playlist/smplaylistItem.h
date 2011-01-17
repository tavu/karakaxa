#ifndef SMPLAYLISTITEM_H 
#define SMPLAYLISTITEM_H

#include"myStandardModel.h"

class smplaylistItem :public myStandardItem
{
    public:
	smplaylistItem(const QString& text);	
	
	virtual QVariant data ( int role = Qt::UserRole + 1 ) const; 
	virtual int type () const;
	
	virtual QString query() const;	
	
	virtual void setXmlElement(QDomElement el);
	QDomElement xml() const;
	
	virtual bool addRow(myStandardItem* item);
	virtual bool removeR(int);
	
    
    protected:
	mutable QString _query;
	QDomElement element;
	
	void generateQuery() const;
	QString group(QDomNode nod) const;
};


#endif
