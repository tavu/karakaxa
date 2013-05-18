#include"nplStream.h"
#include<QObject>
#include <Phonon/MediaObject>
#include<files/audioFile.h>
#include<Basic/tagsTable.h>
#include<Basic/func.h>
#include<core/engine/engine.h>
using namespace audioFiles;
using namespace Basic;

core::nplStream::nplStream(QString s)
        :nplTrack(),
        url(s)
{
    if(s.endsWith("/") )
    {
        s.remove(s.size()-1,s.size()-1);
    }

    url=KUrl(s);

    if (! isStream(url) )
    {
        ok=false;
        return ;
    }


    mediaObject = 0;
    titleS=url.host();
    artistS=QObject::tr("Streamming");
    albumS=url.url();

//      connect(mediaObject,SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

core::nplTrack* core::nplStream::clone()
{
    return new nplStream(url.url());
}

void core::nplStream::play()
{    
    connect(engine()->getMediaObject(),SIGNAL(metaDataChanged() ),this,SLOT(getMetaData() ) );
}

void core::nplStream::finish()
{
    disconnect(mediaObject, 0, this, 0);
//     disconnect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), 0, 0);
}


QString core::nplStream::path()
{
    return url.url();
}

QString core::nplStream::title()
{
    return titleS;
}

void core::nplStream::stateCh(Phonon::State newstate, Phonon::State oldstate)
{
//     if(oldstate==Phonon::LoadingState)
        getMetaData();
}

void core::nplStream::getMetaData()
{
    QStringList l=engine()->getMediaObject()->metaData("TITLE");
    if (!l.isEmpty() )
    {
        titleS=l.at(0);
        qDebug()<<"MO "<<titleS;
    }
    l=engine()->getMediaObject()->metaData("ALBUM");
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

    emitChanged();

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
