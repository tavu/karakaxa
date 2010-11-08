#include"nplTrack.h"

//nplClasses
#include"nplTrack.h"
#include"nplFile.h"
#include"nplStream.h"




player::nplTrack::nplTrack()
        :ok(true)
{
}

int player::nplTrack::trackN()
{
    //in case we don't have the track number
    //else we have to reimplement this function
    return 0;
}

int player::nplTrack::length()
{
    //in case we don't know the length
    //else we have to reimplement this function
    return 0;
}

QString player::nplTrack::artist()
{
    //in case we don't have artists
    //else we have to reimplement this function
    return QString();
}

nplTrack* player::getNplTrack(const QString url)
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
    
    return ret;
}