#include"nplaylist.h"
#include<iostream>
#include<player.h>
#include"nplTread.h"
#include"nplFile.h"
#include<KMimeType>
#include"../../random.cpp"

using namespace player;
player::nplaylist::nplaylist()
        :QObject()
{
//     playing;
    circle=true;
}
nplPointer player::nplaylist::getPlayingTrack()
{
    return playing;
}



bool player::nplaylist::insert(int pos,nplPointer tr)
{
    mutex.lock();

    if (pos>trackList.size()|| pos<0 )	pos=trackList.size();

    if (tr.isNull())
    {
        mutex.unlock();
        return false;
    }	  
    emit (aboutToInsert(pos) );

    trackList.insert (pos,tr);
    totalLength+=tr->tag(LENGTH).toInt();

    emit changed(ADD);

    mutex.unlock();
    return true;
}

nplPointer player::nplaylist::getTrack(int pos)
{
    nplPointer ret;
    mutex.lock();
    if ( pos >= trackList.size() )
    {
        mutex.unlock();
        return  ret ;
    }
    ret= trackList.at(pos);
    mutex.unlock();
    return    ret;
}

bool player::nplaylist::remove(const int pos)
{
    mutex.lock();
    if (pos>=trackList.size() )
    {
        mutex.unlock();
        return false;
    }
//     nplPointer t;
//     nplPointer t=trackList.takeAt(pos);

    emit (aboutToRemove(pos) );
//     trackList.removeAt(pos);
    nplPointer t=trackList.takeAt(pos);
//     totalLength-=t->tag(LENGTH).toInt();
    emit changed(REMOVE);

    if (t==playing)	playing.clear();

//     delete t;
    t.clear();
    mutex.unlock();

    return true;
}


void player::nplaylist::duplicate(const int pos)
{
    QString u=url(pos);
    if(u.isEmpty() )
    {
	return ;
    }
    insert(pos+1,nplTrack::getNplTrack(u) );
//     mutex.lock();
// 
//     if (pos>=trackList.size() )
//     {
//         mutex.unlock();
//         return ;
//     }
// 
//     nplPointer p=trackList.at(pos);
// 
//     nplPointer *n=new nplPointer(*p);
// 
//     emit (aboutToInsert(pos) );
// 
//     trackList.insert (pos+1,n);
//     totalLength+=n->data()->tag(LENGTH).toInt();
// 
//     emit changed(ADD);
// 
//     mutex.unlock();
}

void player::nplaylist::clear()
{
    mutex.lock();
//     QList<nplPointer>::iterator it;
// 
//     int size=trackList.size()-1;
//     emit(aboutToClear(size) );
// 
//     //mutex prevend from accesing the deleted data
//     for (it= trackList.begin(); it != trackList.end(); ++it)
//     {
//         delete *it;
//     }
    int size=trackList.size()-1;
    emit(aboutToClear(size) );
    trackList.clear();
    totalLength=0;
    emit changed(CLEAR);
    mutex.unlock();
}

int player::nplaylist::size()
{
    mutex.lock();

    int ret=trackList.size();
    mutex.unlock();
    return ret;
}

void player::nplaylist::addMediaList(const QList <QUrl> &urlList,int pos)
{
    if (urlList.isEmpty() )	return ;

    nplTread *thr=new nplTread();
    thr->setUrls(urlList);
    thr->setPos(pos);

    thr->start();

}

void player::nplaylist::addMediaList(const QStringList &list,int pos)
{
    if (list.isEmpty() )	return ;

    nplTread *thr=new nplTread();
    thr->setStringL(list);
    thr->setPos(pos);

    thr->start();

}


void player::nplaylist::move(int from,int pos)
{
    mutex.lock();
    trackList.move(from,pos);
    mutex.unlock();
}

QString player::nplaylist::url(int n)
{
    mutex.lock();
    if (n>=trackList.size() )
    {
        mutex.unlock();
        return QString();
    }

    nplPointer p=trackList.at(n);

//      nplTrack *t=p.data();
    mutex.unlock();
    return p->path();
}

QString player::nplaylist::playUrl(int n)
{
    mutex.lock();
    QString ret;
    if (n>=trackList.size() )
    {
        mutex.unlock();
        return ret;
    }

    playing=trackList.at(n);
    ret=playing->path();
    mutex.unlock();
    return ret;
}

QString player::nplaylist::next()
{
    mutex.lock();
    QString ret;
    int pos=trackList.indexOf(playing,0);

    if (pos==-1)
    {
        if (trackList.size()>=1)
        {
            playing=trackList.at(0);
            ret=playing->path();
            mutex.unlock();
            return ret;
        }
        mutex.unlock();
        return QString();
    }

    pos++;
    if (pos>=trackList.size() )
    {
        if (circle && trackList.size()>=1)
        {

            playing=trackList.at(0);
            ret=playing->path();
            mutex.unlock();
            return ret;
        }

        mutex.unlock();
        return ret;
    }

    playing=trackList.at(pos);
    ret=playing->path();
    mutex.unlock();
    return ret;
}

QString player::nplaylist::previous()
{
    mutex.lock();

    int k=trackList.indexOf(playing,0);
    QString ret;
    
    k--;
    if (k<0 )
    {
        mutex.unlock();
        return ret;
    }

    playing=trackList.at(k);
    mutex.unlock();
    ret=playing->path();
    return ret;
}


bool player::nplaylist::isPlaying(const int pos)
{
    mutex.lock();

    if (pos>=trackList.size() )
    {
        mutex.unlock();
        return false;
    }

    nplPointer t=trackList.at(pos);

    if ( t==playing)
    {
        mutex.unlock();
        return true;
    }
    else
    {
        mutex.unlock();
        return false;
    }
}

QStringList player::nplaylist::getList()
{
    QStringList list;

    foreach(nplPointer t,trackList)
    {
        list<<t->path();
    }
    return list;
}

int player::nplaylist::getLength()
{
    return totalLength;
}

void player::nplaylist::suffle()
{
//         qDebug()<<"edop";
    mutex.lock();
    randomShuffle(trackList.begin(),trackList.size() );
    
    mutex.unlock();
}


const int player::nplaylist::ADD=1;
const int player::nplaylist::REMOVE=2;
const int player::nplaylist::CLEAR=3;
