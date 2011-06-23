#include"nplStream.h"
#include<QObject>
#include <Phonon/MediaObject>
// #include<player.h>
#include"../core.h"
#include"../files/audioFile.h"

using namespace audioFiles;

core::nplStream::nplStream(QString s)
        :nplTrack(),
        url(s)
{
    if (! core::isStream(url) )
    {
        ok=false;
        return ;
    }
    mediaObject = 0;
    titleS=QObject::tr("Stream: ")+url.host();
    albumS=url.url();

//      connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

core::nplTrack* core::nplStream::clone()
{
    return new nplStream(url.url());
}

void core::nplStream::play()
{
    mediaObject=engine->getMediaObject();
    connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

void core::nplStream::finish()
{
    disconnect(mediaObject, SIGNAL(metaDataChanged()), 0, 0);
}


QString core::nplStream::path()
{
    return url.url();
}

QString core::nplStream::title()
{
    return titleS;
}

void core::nplStream::getMetaData()
{
    QStringList l=mediaObject->metaData("TITLE");
    if (!l.isEmpty() )
    {
	titleS=l.at(0);
        qDebug()<<"MO "<<titleS;
    }
    l=engine->getMediaObject()->metaData("ALBUM");
    if (!l.isEmpty() )
    {
        albumS=l.at(0);
        qDebug()<<"MO "<<albumS;
    }
    l=mediaObject->metaData("ARTIST");     
    if (!l.isEmpty() )
    {
        artistS=l.at(0);
        qDebug()<<"MO "<<artistS;
    }      
    l=mediaObject->metaData("DESCRIPTION");     
    if (!l.isEmpty() )
    {
        commentS=l.at(0);
        qDebug()<<"MO "<<commentS;
    }
    l=mediaObject->metaData("GENRE");  
    if (!l.isEmpty() )
    {
        genreS=l.at(0);
        qDebug()<<"MO "<<genreS;
    }
    
}

QVariant core::nplStream::tag(int t)
{
    if(t==TITLE)
    {
	return QVariant(titleS);
    }
    else if(t==ALBUM)
    {
	return QVariant(albumS);
    }
    else if(t==GENRE)
    {
	return QVariant(genreS);
    }
    else if(t==ARTIST)
    {
	return QVariant(artistS);	
    }
    else if(t==COMMENT)
    {
	return QVariant(commentS);	
    }
    
    return QVariant();
}

int core::nplStream::type()
{
    return NPLSTREAM;
}
