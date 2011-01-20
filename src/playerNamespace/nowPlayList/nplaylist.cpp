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
    circle=true;
    qRegisterMetaType<nplList>("nplList");
    connect(this,SIGNAL(insertSig(nplList,int)),this,SLOT(insertSlot(nplList,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(removeSig(int)),this,SLOT(removeSlot(int)),Qt::QueuedConnection);
}
nplPointer player::nplaylist::getPlayingTrack()
{
    return playing;
}

void player::nplaylist::insert(nplList list,int pos)
{
    emit (insertSig(list,pos) );
}


void player::nplaylist::insertSlot(nplList list, int pos)
{

    if (pos>trackList.size()|| pos<0 )	pos=trackList.size();

    if (list.isEmpty())
    {
         
        return ;
    }
    
    model->beginInsertRows(QModelIndex(), pos,pos+list.size()-1 );
    for(int i=0;i<list.size();i++)
    {
	trackList.insert (pos+i,list.at(i));
	totalLength+=list.at(i)->tag(LENGTH).toInt();
    }
    
    model->endInsertRows();    
     
    return ;
}

nplPointer player::nplaylist::getTrack(int pos)
{
    nplPointer ret;
     
    if( pos >= trackList.size() )
    {
         
        return  ret;
    }
    ret= trackList.at(pos);
     
    return    ret;
}

void player::nplaylist::remove(const int n)
{
    emit(removeSig(n) );
}


void player::nplaylist::removeSlot(const int pos)
{
     
    if (pos>=trackList.size() )
    {         
        return;
    }

    model->beginRemoveRows(QModelIndex(), pos,pos);
    nplPointer t=trackList.takeAt(pos);
    if (t==playing)	playing.clear();
    model-> endRemoveRows();
    
    t.clear();     

    return;
}

void player::nplaylist::duplicate(const int pos)
{
    QString u=url(pos);
    if(u.isEmpty() )
    {
	return ;
    }
    nplList list;
    list<<nplTrack::getNplTrack(u);
    insert(list,pos+1 );
}

void player::nplaylist::clear()
{
     
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
    emit(cancelThreads() );
    model->beginResetModel ();
    trackList.clear();
    totalLength=0;
    model-> endResetModel();
     
}

int player::nplaylist::size()
{
     

    int ret=trackList.size();
     
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
     
    trackList.move(from,pos);
     
}

QString player::nplaylist::url(int n)
{
     
    if (n>=trackList.size() )
    {
         
        return QString();
    }

    nplPointer p=trackList.at(n);

     
    return p->path();
}

QString player::nplaylist::playUrl(int n)
{
     
    QString ret;
    if (n>=trackList.size() )
    {
         
        return ret;
    }

    playing=trackList.at(n);
    ret=playing->path();
     
    return ret;
}

QString player::nplaylist::next()
{
     
    QString ret;
    int pos=trackList.indexOf(playing,0);

    if (pos==-1)
    {
        if (trackList.size()>=1)
        {
            playing=trackList.at(0);
            ret=playing->path();
             
            return ret;
        }
         
        return QString();
    }

    pos++;
    if (pos>=trackList.size() )
    {
        if (circle && trackList.size()>=1)
        {

            playing=trackList.at(0);
            ret=playing->path();
             
            return ret;
        }

         
        return ret;
    }

    playing=trackList.at(pos);
    ret=playing->path();
     
    return ret;
}

QString player::nplaylist::previous()
{
     

    int k=trackList.indexOf(playing,0);
    QString ret;
    
    k--;
    if (k<0 )
    {
         
        return ret;
    }

    playing=trackList.at(k);
     
    ret=playing->path();
    return ret;
}


bool player::nplaylist::isPlaying(const int pos)
{
     

    if (pos>=trackList.size() )
    {
         
        return false;
    }

    nplPointer t=trackList.at(pos);

    if ( t==playing)
    {
         
        return true;
    }
    else
    {
         
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
    model->beginResetModel();
    randomShuffle(trackList.begin(),trackList.size() );
    model-> endResetModel();     
}


const int player::nplaylist::ADD=1;
const int player::nplaylist::REMOVE=2;
const int player::nplaylist::CLEAR=3;
