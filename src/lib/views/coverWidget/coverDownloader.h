#ifndef COVER_DOWNLOADER_H
#define COVER_DOWNLOADER_H

#include<QObject>
#include <QPixmap>
#include<QSharedPointer>

namespace views
{

typedef QSharedPointer<QPixmap> imageP;
class coverDownloader :public QObject
{
	Q_OBJECT
	public:
		coverDownloader(QObject *parent=0):QObject(parent){}
		virtual ~coverDownloader(){};
		
		virtual void setArtist(QString)=0;
		virtual void setAlbum(QString)=0;		
		
		virtual QString artist()=0;
		virtual QString album()=0;
	signals:
		void newImage(views::imageP);
		
	public slots:
		virtual void fetchCovers()=0;
		virtual bool canFetchMore()=0;
		virtual void clear(){}
};
};
#endif