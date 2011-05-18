#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H
#include<core.h>

class playlistFolder :public standardItem
{
    public:
	playlistFolder(const QString &name);

	
	QVariant data(int column, int role = Qt::UserRole + 1) const;
	virtual bool canFetchMore () const;      
	virtual void fetchMore ();
	virtual int type() const;
	virtual bool hasChildren() const ;
	int columnCount() const;
	
	void setSizeHint(const QSize &s)
	{
	    sizeHint=s;
	}
    protected:
	bool childrenFlag;
	QSize sizeHint;
};


class playlistItem :public standardItem
{
    public:
	playlistItem(const QString &p);
	
	virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const ;
	
	virtual int type () const;
	      
	virtual bool insertRows ( int row, const QList< standardItem* >& items )
	{
	    return false;
	}
	virtual bool insertRow ( int row, standardItem * item )
	{
	  return false;
	}
	
	int columnCount() const;
	
    protected:
	QString path;
	QString name;
};
#endif