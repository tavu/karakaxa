#include"lfmCover.h"
// #include<XmlQuery>
#include<lastfm/ws.h>
#include <KUrl>
#include<viewsFunc.h>
#include <unistd.h>
#include <func.h>

#include<QThread>
lastFm::lfmCover::lfmCover(QObject *parent)
	:views::coverDownloader(parent),reply(0)
{
	albumSe=new searchAlbum(this);
// 	albumSe->setLimit(5);
	connect(albumSe,SIGNAL(albumsFound(QList<lastFm::albumInfo>)),this,SLOT(albums(QList<lastFm::albumInfo>)) );
}

void lastFm::lfmCover::fetchCovers()
{
	albumSe->fetchInfo();
}

void lastFm::lfmCover::albums(QList< lastFm::albumInfo > al)
{
	if(artist().isEmpty() )
	{
		foreach(albumInfo a,al)
		{
			alInfo<<a;
		}
	}
	else
	{
		foreach(albumInfo a,al)
		{
			if(views::compare(a.artist,artist() )==0 )
			{
				alInfo<<a;
			}
		}
	}
	getNextImage();
}

void lastFm::lfmCover::getNextImage()
{
	if(alInfo.size()==0)
	{
		return ;
	}
	
	if(reply!=0)
	{
		if(!reply->isFinished() )
		{
			return ;
		}
		delete reply;
		reply=0;
	}
	
	albumInfo al=alInfo[0];
	
	QString url;
	for(int i=LARGE;i<=MEGA;i++)
	{
		if(!al.imageUrl[i].isEmpty() )
		{
			url=al.imageUrl[i];
			break;
		}
	}
	alInfo.removeAt(0);
	if(url.isEmpty() )
	{
		getNextImage();
	}
	else
	{	
		reply=lastfm::nam()->get(QNetworkRequest(QUrl(url) ) );
		connect(reply,SIGNAL(finished ()),this,SLOT(answer()),Qt::QueuedConnection );
	}
	
}


void lastFm::lfmCover::answer()
{
	if(reply->error()!=QNetworkReply::NoError)
	{
		qWarning("lfmCover network error "+reply->error() );
		getNextImage();
		return;
	}
	views::imageP image(new QPixmap );
	image->loadFromData(reply->readAll() );
	
  	emit(newImage(image) );
	
	getNextImage();
}


lastFm::lfmCover::~lfmCover()
{

}
