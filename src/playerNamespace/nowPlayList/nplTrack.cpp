#include"nplTrack.h"

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
