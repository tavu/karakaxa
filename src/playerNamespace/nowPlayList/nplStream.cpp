#include"nplStream.h"
#include<QObject>
#include <Phonon/MediaObject>
#include<player.h>
player::nplStream::nplStream(QString s)
        :nplTrack(),
        QObject(),
        url(s)
{
    if (! player::isStream(url) )
    {
        ok=false;
        return ;
    }
    mediaObject = 0;
    titleS=QObject::tr("Stream: ")+url.host();
    albumS=url.url();

//      connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

void player::nplStream::play()
{
    mediaObject=engine.getMediaObject();
    connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

void player::nplStream::finish()
{
    disconnect(mediaObject, SIGNAL(metaDataChanged()), 0, 0);
}


QString player::nplStream::path()
{
    return url.url();
}

QString player::nplStream::title()
{
//      qDebug()<<"M "<<mediaObject->metaData("TITLE");
//      qDebug()<<"M "<<engine.getMediaObject()->metaData("ARTIST");

//      return engine.getMediaObject()->metaData("TITLE").at(0);
    return titleS;
}

void player::nplStream::getMetaData()
{
    QStringList l=mediaObject->metaData("TITLE");
    if (!l.isEmpty() )
    {
	titleS=l.at(0);
        qDebug()<<"MO "<<titleS;
    }
    l=engine.getMediaObject()->metaData("ALBUM");
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

QVariant player::nplStream::tag(tagsEnum t)
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

int player::nplStream::type()
{
    return NPLSTREAM;
}
