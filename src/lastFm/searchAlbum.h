#ifndef SEARCH_ALBUM_H
#define SEARCH_ALBUM_H
#include <QObject>
#include"imageSize.h"
#include<QMap>
#include<QNetworkReply>
namespace lastFm
{

struct lfmAlbumSearch
{
	QString name;
	QString artist;
	int id;
	QString url;
	QString imageUrl[MEGA];
	QString mbid;
};
typedef struct lfmAlbumSearch albumInfo;

class searchAlbum :public QObject
{
	Q_OBJECT
	public:
		searchAlbum(QObject *parent=0);
		~searchAlbum()
		{
			if(reply!=0)
				delete reply;
		}
		void setAlbum(QString s)
		{
			map["album"] = s;
			clear();
		}
		
		QString album()
		{
			return map["album"];
		}
		
		void setLimit(int l)
		{
			if (l > 0)
			{
				map["limit"] = QString::number(l);
			}			
		}
		
		int limit()
		{
			QString s=map["limit"];
			if(s.isNull() ||s.isEmpty() )
			{
				return -1;
			}
			return s.toInt();
		}
		
		void fetchInfo();
		void clear();
		bool canFetchMore();
		int resultNum()
		{
			return totalResults;
		}
		
	signals:
		void albumsFound(QList<lastFm::albumInfo>);
		
	private:
		
		QMap<QString, QString> map;
		QNetworkReply *reply;		
		
		int totalResults;
		int itemsNum;
		int page;
			
	private slots:
		void answer();
};


}
#endif