#include"nplTrack.h"
#include"../../files/fileTags.h"
//nplClasses
#include"nplTrack.h"
#include"nplFile.h"
#include"nplStream.h"
#include"../core.h"



core::nplTrack::nplTrack()
        :QObject(), ok(true)
{
}

core::nplTrack::~nplTrack()
{
}

QVariant core::nplTrack::artist()
{
    return tag(ARTIST);
}

core::nplPointer core::nplTrack::getNplTrack(const QString url)
{
    return getNplTrack(KUrl(url) );
}

core::nplPointer core::nplTrack::getNplTrack(const QUrl url)
{
    nplTrack *ret=0;

    if (core::isStream(url.toString()) )
    {
        ret=new nplStream(url.toString());
    }
    if(isAudio(url.toString()) )
    {
        ret=new nplFile(url.toLocalFile() );
    }

    return nplPointer(ret);    
}
      


QVariant core::nplTrack::tag(int t)
{
    if(t==TITLE)
    {
        return QVariant(title() );
    }
    
    return QVariant();
}

QString core::nplTrack::cover()
{
    return QString();
}

void core::nplTrack::play()
{
}

void core::nplTrack::finish()
{
}
