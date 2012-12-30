#ifndef LFM_COVER_H
#define LFM_COVER_H

#include<coverWidget/coverDownloader.h>
#include<QMap>
#include<QNetworkReply>
#include"searchAlbum.h"

namespace lastFm
{


class lfmCover :public views::coverDownloader
{
		Q_OBJECT
	public:
		lfmCover(QObject *parent=0);
		~lfmCover();
		
		void setArtist(QString s)
		{
			_artist=s;
		}
		void setAlbum(QString s)
		{
			albumSe->setAlbum(s);
		}
		
		void clear()
		{
			albumSe->clear();
		}
		
		QString artist()
		{
			return _artist;
		}
		QString album()
		{
			return albumSe->album();
		}
		
		void fetchCovers();
		
		bool canFetchMore()
		{
			return albumSe->canFetchMore();
		}
		

	private:
		searchAlbum *albumSe;
		
		QMap<QString, QString> map;
		QNetworkReply *reply;
		QString _artist;
		
		QList<lastFm::albumInfo> alInfo;
	
		void getNextImage();
	private slots:
		void albums(QList<lastFm::albumInfo>);
		void answer();
		
};
};
#endif