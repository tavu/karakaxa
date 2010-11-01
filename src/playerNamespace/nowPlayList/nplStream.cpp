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
    mediaObject = new Phonon::MediaObject();
    titleS=QObject::tr("Stream: ")+url.host();
    albumS=url.url();

//      connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );

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

QString player::nplStream::album()
{
    return albumS;
}

void player::nplStream::getMetaData()
{
    QStringList l=engine.getMediaObject()->metaData("TITLE");
    if (l.isEmpty() )
    {
        titleS=QObject::tr("Stream: ")+url.host();
    }
    else
    {
        titleS=l.at(0);
        qDebug()<<"MO "<<titleS;
    }

    l=engine.getMediaObject()->metaData("ALBUM");
    if (l.isEmpty() )
    {
        albumS=url.url();
    }
    else
    {
        albumS=l.at(0);
        qDebug()<<"MO "<<albumS;
    }
}

QString player::nplStream::type()
{
    return QString("Stream");
}
