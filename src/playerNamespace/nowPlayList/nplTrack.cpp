#include"nplTrack.h"

//nplClasses
#include"nplTrack.h"
#include"nplFile.h"
#include"nplStream.h"




player::nplTrack::nplTrack()
        :ok(true)
{
}

player::nplTrack::~nplTrack()
{
}


nplPointer player::nplTrack::getNplTrack(const QString url)
{
    nplTrack *ret=0;
    
    if (player::isStream(url) )
    {
        ret=new nplStream(url);        
    }
    if(isAudio(url) )
    {
	ret=new nplFile(url);
    }
    
    return nplPointer(ret);    
}

QVariant player::nplTrack::tag(tagsEnum t)
{
    if(t==TITLE)
    {
	return QVariant(title() );
    }
    
    return QVariant();
}


