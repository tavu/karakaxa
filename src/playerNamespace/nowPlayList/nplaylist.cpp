#include"nplaylist.h"
#include<iostream>
#include<player.h>
#include"nplTread.h"
#include"nplFile.h"
#include<KMimeType>

#define test std::cout<<"playlist test"<<std::endl;

using namespace player;
player::nplaylist::nplaylist()
        :QObject()
{
    playing=0;
    circle=true;
}

bool player::nplaylist::append(nplTrack *tr)
{
    //we just call insert with pos -1.    
    return insert(-1,tr);
}

bool player::nplaylist::insert(int pos,nplTrack *tr)
{
    mutex.lock();

    if (pos>trackList.size()|| pos<0 )	pos=trackList.size();

    if (tr==0)
    {
        mutex.unlock();
        return false;
    }

    nplPointer *p=new nplPointer(tr);
    emit (aboutToInsert(pos) );

    trackList.insert (pos,p);
    totalLength+=tr->length();

    emit changed(ADD);


    mutex.unlock();
    return true;
}

nplTrack* player::nplaylist::getTrack(int pos)
{
    nplTrack *ret=0;
    mutex.lock();
    if ( pos >= trackList.size() )
    {
        mutex.unlock();
        return  ret ;
    }
    ret= trackList.at(pos)->data();
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
    nplPointer *t=trackList.at(pos);

    emit (aboutToRemove(pos) );
    trackList.removeAt(pos);
    totalLength-=t->data()->length();
    emit changed(REMOVE);

    if (t==playing)	playing=0;

    delete t;

    mutex.unlock();

    return true;
}


void player::nplaylist::duplicate(const int pos)
{
    mutex.lock();

    if (pos>=trackList.size() )
    {
        mutex.unlock();
        return ;
    }

    nplPointer *p=trackList.at(pos);

    nplPointer *n=new nplPointer(*p);

    emit (aboutToInsert(pos) );

    trackList.insert (pos+1,n);
    totalLength+=n->data()->length();

    emit changed(ADD);

    mutex.unlock();
}

void player::nplaylist::clear()
{
    mutex.lock();
    QList<nplPointer*>::iterator it;

    int size=trackList.size()-1;
    emit(aboutToClear(size) );

    //mutex prevend from accesing the deleted data
    for (it= trackList.begin(); it != trackList.end(); ++it)
    {
        delete *it;
    }

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

    nplPointer *p=trackList.at(n);

    nplTrack *t=p->data();
    mutex.unlock();
    return t->path();
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
    ret=playing->data()->path();
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
            ret=playing->data()->path();
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
            ret=playing->data()->path();
            mutex.unlock();
            return ret;
        }

        mutex.unlock();
        return ret;
    }

    playing=trackList.at(pos);
    ret=playing->data()->path();
    mutex.unlock();
    return ret;
}

QString player::nplaylist::previous()
{
    mutex.lock();

    int k=trackList.indexOf(playing,0);
    QString ret;
    if (k==-1)
    {
        mutex.unlock();
        return ret;
    }

    k--;
    if (k<0 )
    {
        mutex.unlock();
        return ret;
    }

    playing=trackList.at(k);
    mutex.unlock();
    ret=playing->data()->path();
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

    nplPointer *t=trackList.at(pos);

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

    foreach(nplPointer *t,trackList)
    {
        list<<t->data()->path();
    }
    return list;
}

bool player::nplaylist::addAudio(const QString &url,const uint pos)
{
    if (!isAudio(url) )
    {
        qDebug()<<"not audio";
        return false;
    }

    nplTrack *t=new player::nplFile(url);

    if ( !t->isOk() )
    {
        return false;
    }

    return insert(pos,t);
}

bool player::nplaylist::isAudio(const QString &url)
{
    KMimeType::Ptr type = KMimeType::findByUrl(url );

    QStringList l=config.files();
    if (l.contains(type->name() ) )
    {
        return true;
    }
    return false;
}

int player::nplaylist::getLength()
{
    return totalLength;
}




const int player::nplaylist::ADD=1;
const int player::nplaylist::REMOVE=2;
const int player::nplaylist::CLEAR=3;
