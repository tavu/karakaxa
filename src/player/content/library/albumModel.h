#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QSqlQuery>
#include<QIcon>
#include<QAbstractListModel>
#include<QVariant>
#include<core.h>

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
	
	void setSearch(core::queryGrt::matchQuery *qe)
	{
	    searchQ=qe;
	}
	
	void setArtist(const QString &s)
	{
	    artist=s;
	}
	
    private:

	QSize itemSize;
	QSize maxSize;
	QSize minSize;
	QSize imageSize;
	QIcon *artistIcon;
	QIcon *songIcon;
	QIcon *albumIcon;
	
	
	QPixmap *pix;
	QPixmap *defaultPic;
	
	QString artist;
	
	core::queryGrt::matchQuery *searchQ;
	
	QList<core::queryGrt::album> albums;

	void resizePix();
};

#endif
