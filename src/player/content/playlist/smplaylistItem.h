#ifndef SMPLAYLISTITEM_H 
#define SMPLAYLISTITEM_H
#include<core.h>
#include<queries/abstractQuery.h>

class smplaylistItem :public core::xmlItem
{
    public:
	smplaylistItem(QDomDocument &doc, const QString& text);
	smplaylistItem(const QDomElement &el);
	
	virtual QVariant data ( int column, int role = Qt::UserRole + 1 ) const; 
	
	virtual int type () const;
	
 	virtual database::abstractQuery* query() const;
	
	virtual bool insertRows ( int row, const QList< core::xmlItem* >& items )
	{
	    Q_UNUSED(row)
	    Q_UNUSED(items)
	    return false;
	}
	virtual bool insertRow ( int row, core::xmlItem* item )
	{
	    Q_UNUSED(row)
	    Q_UNUSED(item)
	    return false;
	}
	
	virtual bool setData (const QVariant& value, int column, int role = Qt::EditRole );
	
	
//  	static const int SMARTPL_ITEM;
	
    protected:
	
	mutable database::abstractQuery *quer;
// 	mutable QString _query;
	
 	void generateQuery() const;
 	database::abstractQuery * group(QDomNode nod) const;
};


#endif
