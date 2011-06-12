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
    nplTrack *ret=0;
    
    if (core::isStream(url) )
    {
        ret=new nplStream(url);        
    }
    if(isAudio(url) )
    {
	ret=new nplFile(url);
    }
    
    return nplPointer(ret);    
}

core::nplPointer core::nplTrack::getNplTrack(const QUrl url)
{
    return getNplTrack(url.toLocalFile());
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
