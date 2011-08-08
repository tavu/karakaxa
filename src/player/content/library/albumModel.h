#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QSqlQuery>
#include<QIcon>
#include<QAbstractListModel>
#include<QVariant>
#include<core.h>
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
	
	void setSearch(core::queryGrt::abstractQuery *qe)
	{
// 	    searchQ=qe;
	    albumGrt->setQuery(qe);
	}
	
	void setArtist(const QString &s)
	{
	    artist=s;
	    albumGrt->setArtist(s);
	}
	
	const core::albumQueryGrt* queryGrt()
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
	
	core::queryGrt::abstractQuery *searchQ;
	core::albumQueryGrt *albumGrt;
	
	QList<core::album> albums;

	void resizePix();
};














#endif
