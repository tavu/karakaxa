#include"searchAlbum.h"
// #include<XmlQuery>
#include<QDomDocument>
#include<QDomNodeList>

#include<lastfm/ws.h>
#include"lastFmFunc.h"
#include <Basic/status.h>
bool lastFm::searchAlbum::canFetchMore()
{
	if(totalResults<0 || totalResults>itemsNum)
	{
		return true;
	}
	return false;
}

void lastFm::searchAlbum::clear()
{
	if(reply!=0)
	{
		delete reply;
	}
	reply=0;
	totalResults=-1;
	itemsNum=0;
	page=1;
}


void lastFm::searchAlbum::fetchInfo()
{
	if(!canFetchMore())
	{
		return ;
	}
	if(reply!=0)
	{
		delete reply;
	}
	map["page"] = QString::number (page);
	reply=lastfm::ws::get(map);
	connect(reply,SIGNAL(finished()),this,SLOT(answer()) );
}

lastFm::searchAlbum::searchAlbum(QObject* parent): QObject(parent),page(1),reply(0)
{
	map["method"]="album.search";
}


void lastFm::searchAlbum::answer()
{
	QList<struct lfmAlbumSearch> albumL;
	QDomDocument domdoc;
    try
    {
        domdoc.setContent(lastfm::ws::parse(reply) );
	}
	catch (lastfm::ws::ParseError& e)
    {
        Basic::msg()->error(tr("Last fm error on album search") );
		return ;
    }
	
	QDomElement el = domdoc.documentElement();
	QDomNodeList nl;
	nl=el.elementsByTagName("opensearch:totalResults") ;
	
	if(nl.count()==1)
	{
		totalResults=nl.item(0).toElement().text().toInt();
		qDebug()<<"TOTAL "<<totalResults;
	}
	else
	{
		Basic::msg()->error(tr("error downoading some covers") );
		return ;
	}
	
		
	nl=el.elementsByTagName("album");		
	
	for(int i=0;i<nl.count();i++)
	{
		QDomElement e = nl.item(i).toElement();
		struct lfmAlbumSearch al;
			
		al.artist=e.firstChildElement("artist").text();
		al.id=e.firstChildElement("id").text().toInt();
		al.name=e.firstChildElement("name").text();
			
		QDomNodeList imageNodes=e.elementsByTagName("image");
		
		for(int j=0;j<imageNodes.count();j++)
		{
 				QDomElement e=imageNodes.item(j).toElement();
				QString size=e.attribute("size");
				int i=sizeFromString(size);
				
				if(i<0)
				{
					continue;
				}
				al.imageUrl[i]=e.text();				
		}
		al.url=e.firstChildElement("url").text();
		albumL.append(al);        
	}
	itemsNum+=nl.count();
	
	page++;
// 	delete reply;
// 	reply=0;
    emit(albumsFound(albumL));
}
