#include"nplaylist.h"
#include<iostream>
// #include<player.h>
#include"nplTread.h"
#include"nplFile.h"
#include"../engine/engine.h"
#include"func.h"
// #include<KMimeType>
// #include"../../random.cpp"
#include<QApplication>


using namespace core;
core::nplaylist::nplaylist()
        :QObject(),
        totalLength(0)
{
    circle=true;
    qRegisterMetaType<nplList>("nplList");
    connect(this,SIGNAL(insertSig(nplList,int)),this,SLOT(insertSlot(nplList,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(removeSig(int)),this,SLOT(removeSlot(int)),Qt::QueuedConnection);    
    connect(engine,SIGNAL(trackChanged(QString) ),this,SLOT(informTrack() ),Qt::QueuedConnection );
}


void nplaylist::prepareToQuit()
{
    clear();
}


core::nplaylist::~nplaylist()
{
}

nplPointer core::nplaylist::getPlayingTrack()
{
    return playing;
}

void core::nplaylist::insert(nplList list,int pos)
{  
    if(QThread::currentThread()==core::mainThr() )
    {
	insertSlot(list,pos);
    }
    else
    {
	emit (insertSig(list,pos) );
    }
}


void core::nplaylist::insertSlot(nplList list, int pos)
{

    if (pos>trackList.size()|| pos<0 )	pos=trackList.size();

    if (list.isEmpty())
    {
         
        return ;
    }
    
    model->beginInsertRows(QModelIndex(), pos,pos+list.size()-1 );
    for(int i=0;i<list.size();i++)
    {
	if(!list[i].isNull() && list[i]->isValid() )
	{
	    trackList.insert (pos+i,list[i] );
	    totalLength+=list[i]->tag(LENGTH).toInt();
	}
    }
    
    model->endInsertRows();
     
    emit( inserted(list.size() ) );
    return ;
}

nplPointer core::nplaylist::getTrack(int pos)
{
    nplPointer ret;
     
    if( pos >= trackList.size() )
    {
         
        return  ret;
    }
    ret= trackList.at(pos);
     
    return    ret;
}

void core::nplaylist::remove(const int n)
{
    emit(removeSig(n) );
}


void core::nplaylist::removeSlot(const int pos)
{
     
    if (pos>=trackList.size() )
    {         
        return;
    }

    model->beginRemoveRows(QModelIndex(), pos,pos);
    nplPointer t=trackList.takeAt(pos);
    if (t==playing)	playing.clear();
    model-> endRemoveRows();
    
    emit removed(1);
    
    t.clear();     

    return;
}

void core::nplaylist::duplicate(const int pos)
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

void core::nplaylist::clear()
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
    emit (cleared() );
     
}

int core::nplaylist::size()
{
     

    int ret=trackList.size();
     
    return ret;
}

void core::nplaylist::addMediaList(const QList <QUrl> &urlList,int pos)
{
    if (urlList.isEmpty() )	return ;

    nplTread *thr=new nplTread();
    thr->setUrls(urlList);
    thr->setPos(pos);

    thr->start();

}

void core::nplaylist::addMediaList(const QStringList &list,int pos)
{
    if (list.isEmpty() )	return ;

    nplTread *thr=new nplTread();
    thr->setStringL(list);
    thr->setPos(pos);

    thr->start();

}


void core::nplaylist::move(int from,int pos)
{     
    trackList.move(from,pos);     
}

QString core::nplaylist::url(int n)
{
     
    if (n>=trackList.size() )
    {
         
        return QString();
    }

    nplPointer p=trackList.at(n);

     
    return p->path();
}

QString core::nplaylist::playUrl(int n)
{
     
    QString ret;
    if (n>=trackList.size() || n<0 )
    {
         
        return ret;
    }

    playing=trackList.at(n);
    ret=playing->path();
     
    return ret;
}

QString core::nplaylist::next()
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

QString core::nplaylist::previous()
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


bool core::nplaylist::isPlaying(const int pos)
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

QStringList core::nplaylist::getList()
{
    QStringList list;

    foreach(nplPointer t,trackList)
    {
        list<<t->path();
    }
    return list;
}

int core::nplaylist::getLength()
{
    return totalLength;
}

void core::nplaylist::suffle()
{
    model->beginResetModel();
    core::randomShuffle(trackList.begin(),trackList.size() );
    model-> endResetModel();     
}

void core::nplaylist::informTrack()
{
   if(!playing.isNull() )
   {
      playing->play();
   }
}

const int core::nplaylist::ADD=1;
const int core::nplaylist::REMOVE=2;
const int core::nplaylist::CLEAR=3;


namespace core
{
    nplaylist *npList;
}