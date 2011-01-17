#ifndef NPLABSTRACTMODEL_H
#define NPLABSTRACTMODEL_H

#include<QAbstractItemModel>
#include"nplaylist.h"


class nplAbstractModel :public QAbstractItemModel
{
    Q_OBJECT
    friend class player::nplaylist;
        
    public:
	nplAbstractModel(QObject *parnet=0);
	virtual QModelIndex index(int row,int column,const QModelIndex &parent=QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex&) const;
	virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	
};
#endif