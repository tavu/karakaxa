#ifndef SONGMODEL_H
#define SONGMODEL_H

#include <QSqlTableModel>

// #include<trackUrl.h>

// #include<QWidget>
#include<player.h>
#include<trackView.h>
#include<QSortFilterProxyModel>

class songModel :public QSqlQueryModel 
{
    Q_OBJECT
    
    public:
	songModel(QWidget *parent );
	QVariant data(const QModelIndex &item, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

 	virtual void setFilter(const QString &s);
 	virtual void select();
	virtual int  columnCount ( const QModelIndex & index = QModelIndex() ) const;
	
	virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	virtual KUrl url( int row) const;
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );
	virtual void setSort ( int column, Qt::SortOrder order );


	
    private:

     	  QSqlQueryModel queryM;
	  QString	_filter;
	  int 		_order;
	  Qt::SortOrder sortO;
	  bool doNotUpdate;
	  	  
	  
	  
    public slots:
	void refresh();

};


#endif
