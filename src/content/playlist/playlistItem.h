#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H
#include"myStandardModel.h"

class playlistFolder :public myStandardItem
{
    public:
	playlistFolder(const QString &name);
	virtual bool removeR(int);      
	virtual bool addRow(myStandardItem *item);
	virtual bool canFetchMore () const;      
	virtual void fetchMore ();
	virtual int type() const;
	virtual bool hasChildr() const ;
	
    protected:
	bool childrenFlag;
};


class playlistItem :public myStandardItem
{
    public:
	playlistItem(const QString &p);
	
	virtual QVariant data(int role = Qt::UserRole+1 ) const;
	virtual int type () const;
	      
	virtual bool removeR(int);      
	virtual bool addRow(myStandardItem *item);
	
    private:
	QString path;
};
#endif