#include"nplTrack.h"
#include"../../files/fileTags.h"
#include"Basic/tagsTable.h"
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
    return tag(Basic::ARTIST);
}

core::nplPointer core::nplTrack::getNplTrack(const QString url)
{
    return getNplTrack(KUrl(url) );
}

core::nplPointer core::nplTrack::getNplTrack(const QUrl url)
{
    nplTrack *ret=0;

    if (Basic::isStream(url.toString()) )
    {
        ret=new nplStream(url.toString());
    }
    if(Basic::isAudio(url.toString()) )
    {
        ret=new nplFile(url.toLocalFile() );
    }

    return nplPointer(ret);    
}
      


QVariant core::nplTrack::tag(int t)
{
    if(t==Basic::TITLE)
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
