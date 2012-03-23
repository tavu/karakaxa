#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QSqlQuery>
#include<QIcon>
#include<QAbstractListModel>
#include<QVariant>
#include<core.h>
#include<queries/abstractQuery.h>
#include<queries/albumQueryGrt.h>

#include "albumWidget.h"

class albumModel :public QAbstractListModel
{
    Q_OBJECT

    public:
	albumModel(QObject *parent = 0);
	QVariant data(const QModelIndex &item, int role) const;
	~albumModel();
	int albumId(const int row);
	void resize(QSize &s);
	void update();
	
	
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const
	{
	    return albums.size();
	}
	
	int columnCount ( const QModelIndex & parent = QModelIndex() )
	{
	    return 1;
	}
	
	void setSearch(database::abstractQuery *qe)
	{
// 	    searchQ=qe;
	    albumGrt->setQuery(qe);
	}
	
	void setArtist(const QString &s)
	{
	    artist=s;
	    albumGrt->setArtist(s);
	}
	
	const database::albumQueryGrt* queryGrt()
	{
	    return albumGrt;
	}
	
    private:

	QSize itemSize;
	QSize maxSize;
	QIcon *artistIcon;
	QIcon *songIcon;
	QIcon *albumIcon;
	
	
	QPixmap *pix;
	QPixmap *defaultPic;
	
	QString artist;
	
	database::abstractQuery *searchQ;
	database::albumQueryGrt *albumGrt;
	
	QList<database::album> albums;

	void resizePix();
};














#endif
