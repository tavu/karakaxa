#include"nplTread.h"

#include<QDirIterator>
#include<QDebug>
#include"nplFile.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include"nplStream.h"
#include"playlist/filePlaylist.h"
#include<QtAlgorithms>
#include<Basic/tagsTable.h>
#include<Basic/status.h>
#include<Basic/func.h>

core::nplTread::nplTread()
        :QThread(),
        canceled(false),
        size(10)
{    

//     statusBar.addPermanentWidget(w);

    connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );
//     connect(&npList(),SIGNAL(cancelThreads()),this ,SLOT(cancel() ),Qt::QueuedConnection );
}

void core::nplTread::cancel()
{
    canceled=true;
}


core::nplTread::~nplTread()
{
    qDebug()<<"quit";
}

void core::nplTread::run()
{
    foreach(QUrl url, urlList)
    {
        if(!canceled)
        {
            addMedia(url );
        }
        else
        {
            return ;
        }
    }

    foreach(QString url, sList)
    {
        if(!canceled)
        {
            addMedia(KUrl(url) );
        }
        else
        {
            return ;
        }
    }
    
    cleanUp();
}

void core::nplTread::cleanUp()
{
    if(!list.isEmpty() )
    {
      npList()->insert(pos,list);
    }
}

void core::nplTread::addMedia(const QUrl &url)
{
    if (Basic::isDirectory(url.toLocalFile()) )
    {
        if(list.size()>0)
        {
            npList()->insert(pos,list);
            pos+=list.size();
            list.clear();
        }
        addDirectory(url);
    }
    else if(Basic::isPlaylist(url.toLocalFile()) )
    {
        addPlaylist(url);
    }
    else if(Basic::isAudio(url.toLocalFile()) || Basic::isStream(url) )
    {
        addSingleFile(url);
    }
}


void core::nplTread::addPlaylist(const QUrl& url)
{
    filePlaylist *pl=getPlaylist(url.toLocalFile());
    if(pl==0)
    {
	   Basic::msg()->error(tr("Can't load playlist") );
	   return;
    }
    
    pl->load();
    for (int i=0;i<pl->size() && !canceled;i++)    
    {            
	   addSingleFile(pl->item(i) );
    }    
    delete pl;
}

void core::nplTread::addSingleFile(const QUrl& url)
{
    nplPointer tr=core::nplTrack::getNplTrack(url);
    addSingleFile(tr);
}


void core::nplTread::addSingleFile(nplPointer tr)
{
    if(!tr.isNull() )
    {
       list<<tr;

       if(tr->type()==NPLAUDIOFILE)
       {
          audioFile file(tr->path());
          file.load();
       }
    }

    if(list.size()>=size )
    {
        npList()->insert(pos,list);
        pos+=list.size();
        list.clear();
    }  
}



void core::nplTread::setUrls(QList <QUrl> l)
{
    urlList=l;
}

void core::nplTread::setStringL(QStringList l)
{
    sList=l;
}

void core::nplTread::setPos(int num)
{
    pos=num;
}

void core::nplTread::addDirectory(const QUrl &url)
{
    QLinkedList<QString> dirs;    
    {
	   nplList files;
	   	   
	   QDir dir(url.toLocalFile());
	   QFileInfoList infoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);    
	   
	   for (int i=0;i<infoList.size() && !canceled ;i++)
	   {
		  if(Basic::isAudio(infoList.at(i).absoluteFilePath() ) )
		  {
			 nplPointer tr=core::nplTrack::getNplTrack(infoList.at(i).absoluteFilePath() );
			 if(!tr.isNull() )
			 {
				files<<tr;
				audioFile file(infoList.at(i).absoluteFilePath());
				file.load();
			 }
		  }
		  else if(Basic::isDirectory(infoList.at(i).absoluteFilePath()) )	 
		  {
			 dirs<<infoList.at(i).absoluteFilePath();
		  }
       }
	   
	   qSort(files.begin(),files.end(),trackLessThan);
	   npList()->insert(pos,files);
	   pos+=files.size();    
    }

	foreach(QString s,dirs)
	{
		addDirectory(s);
	}
}

bool core::nplTread::trackLessThan(nplPointer a,nplPointer b)
{
    int trackA,trackB;
    trackA=a->tag(Basic::TRACK).toInt();
    trackB=b->tag(Basic::TRACK).toInt();
    
    return trackA<trackB;
}