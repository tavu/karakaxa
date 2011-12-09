#include"playlist.h"

void core::playlist::insert(int pos, core::nplPointer p)
{
    if(p.isNull() )
        return ;

    if(pos<0 || pos>trackList.size() )
        pos=trackList.size();

    if(_emitSignals)
    {
        emit aboutToInsertTrack(pos);
        trackList.insert(pos,p);
        emit trackInserted(pos);
    }
    else
    {
        trackList.insert(pos,p);
    }
}

void core::playlist::remove(int pos)
{
    if(pos<0 || pos>trackList.size() )
        return ;

    if(_emitSignals)
    {
        emit aboutToRemoveTrack(pos);
        trackList.removeAt(pos);
        emit trackRemoved(pos);
    }
    else
    {
        trackList.removeAt(pos);
    }
}

void core::playlist::move(int from, int to)
{
    if(from<0 || from>trackList.size() )
        return ;

    if(to<0 && to>trackList.size() )
        return ;

        if(_emitSignals)
    {
        emit aboutToMoveTrack(from,to);
        trackList.move(from,to);
        emit trackMoved(from,to);
    }
    else
    {
        trackList.move(from,to);
    }
}

void core::playlist::insert(int pos, nplList l)
{
    if(pos<0 || pos>trackList.size() )
        pos=trackList.size();

    if(l.isEmpty() )
        return ;

    int newPos=pos;

    if(_emitSignals)
        emit aboutToInsertTracks(pos,l.size() );
    for(int i=0;i<l.size();i++)
    {
       trackList.insert (newPos,l[i] );
       newPos++;
    }
    if(_emitSignals)
        emit tracksInserted(pos,l.size() );
}

void core::playlist::clear()
{
    if(_emitSignals)
    {
        emit aboutToClear();
        trackList.clear();
        emit cleared();
    }
    else
    {
        trackList.clear();
    }
}
