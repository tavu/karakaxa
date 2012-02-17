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
#include"../status/playerStatus.h"
#include"../config/config.h"


// using namespace core;
core::nplaylist::nplaylist()
        :playlist(),
        totalLength(0)
{
    circle=true;
    qRegisterMetaType<nplList>("nplList");
    
    KSharedConfigPtr config=core::config->configFile();	
    KConfigGroup group( config, "nowPlaylist" );	
    rememberPl=group.readEntry( "rememberPl", false);

    connect(engine,SIGNAL(trackChanged(QString) ),this,SLOT(informTrack() ),Qt::QueuedConnection );
//     connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(prepareToQuit()) );
}

core::nplaylist::~nplaylist()
{
    prepareToQuit();
}

void nplaylist::setRememberPlaylist(bool b)
{
    rememberPl=b;
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "nowPlaylist" );
    group.writeEntry( "rememberPl", QVariant(rememberPl));
    group.config()->sync();
}


void core::nplaylist::prepareToQuit()
{
    if(rememberPl)
    {
	   QStringList l;
	   
	   foreach(nplPointer p ,trackList)
	   {
		  l<<p->path();
	   }
	   QVariant var(l);
	   KSharedConfigPtr config=core::config->configFile("nowPlaylist");
	   KConfigGroup group( config, "list" );
	   group.writeEntry( "list", QVariant(l) );
	   group.config()->sync(); 
    }    
}

void core::nplaylist::loadSavedPlaylist()
{
    if(rememberPl)
    {
	   KSharedConfigPtr config=core::config->configFile("nowPlaylist");	
	   KConfigGroup group( config, "list" );	
	   QStringList l=group.readEntry("list", QStringList() );
	   		
	   addMediaList(l,0);    
    }
}

nplPointer core::nplaylist::getPlayingTrack() const
{
    return playing;
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
    insert(pos,list);
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

QString core::nplaylist::url(int n) const
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
    
//     playing.clear();
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
        else
        {
            playing.clear();
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


bool core::nplaylist::isPlaying(const int pos) const
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

QStringList core::nplaylist::getList() const
{
    QStringList list;

    foreach(nplPointer t,trackList)
    {
        list<<t->path();
    }
    return list;
}

int core::nplaylist::getLength() const
{
    return totalLength;
}

void core::nplaylist::suffle()
{
    
    core::randomShuffle(trackList.begin(),trackList.size() );
    
}

void core::nplaylist::informTrack()
{
   if(!playing.isNull() )
   {
//       playing->play();
   }
}

const int core::nplaylist::ADD=1;
const int core::nplaylist::REMOVE=2;
const int core::nplaylist::CLEAR=3;


namespace core
{
    nplaylist *npList;
}