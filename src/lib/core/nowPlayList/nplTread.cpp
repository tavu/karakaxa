#include"nplTread.h"

#include<QDirIterator>
#include<QDebug>
#include"nplFile.h"
#include"../core.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include"nplStream.h"
#include"playlist/filePlaylist.h"
#include<QtAlgorithms>

nplTread::nplTread()
        :QThread(),
        canceled(false),
        size(10)
{    

//     statusBar.addPermanentWidget(w);

    connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );
//     connect(&npList(),SIGNAL(cancelThreads()),this ,SLOT(cancel() ),Qt::QueuedConnection );
}

void nplTread::cancel()
{
    canceled=true;
}


nplTread::~nplTread()
{
    qDebug()<<"quit";
}

void nplTread::run()
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

void nplTread::cleanUp()
{
    if(!list.isEmpty() )
    {
      npList()->insert(pos,list);
    }
}

void nplTread::addMedia(const QUrl &url)
{
    if (core::isDirectory(url.toLocalFile()) )
    {
        if(list.size()>0)
        {
            npList()->insert(pos,list);
            pos+=list.size();
            list.clear();
        }
        addDirectory(url);
    }
    else if(core::isPlaylist(url.toLocalFile()) )
    {
        addPlaylist(url);
    }
    else if(core::isAudio(url.toLocalFile()) || core::isStream(url) )
    {
        addSingleFile(url);
    }
}


void nplTread::addPlaylist(const QUrl& url)
{
    filePlaylist *pl=getPlaylist(url.toLocalFile());
    if(pl==0)
    {
	   status->addError(tr("Can't load playlist") );
	   return;
    }
    
    pl->load();
    for (int i=0;i<pl->size() && !canceled;i++)    
    {            
	   addSingleFile(pl->item(i) );
    }    
    delete pl;
}

void nplTread::addSingleFile(const QUrl& url)
{
    nplPointer tr=core::nplTrack::getNplTrack(url);
    addSingleFile(tr);
}


void nplTread::addSingleFile(nplPointer tr)
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



void nplTread::setUrls(QList <QUrl> l)
{
    urlList=l;
}

void nplTread::setStringL(QStringList l)
{
    sList=l;
}

void nplTread::setPos(int num)
{
    pos=num;
}

void nplTread::addDirectory(const QUrl &url)
{
    QLinkedList<QString> dirs;    
    {
	   nplList files;
	   	   
	   QDir dir(url.toLocalFile());
	   QFileInfoList infoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);    
	   
	   for (int i=0;i<infoList.size() && !canceled ;i++)
	   {
		  if(core::isAudio(infoList.at(i).absoluteFilePath() ) )
		  {
			 nplPointer tr=core::nplTrack::getNplTrack(infoList.at(i).absoluteFilePath() );
			 if(!tr.isNull() )
			 {
				files<<tr;
				audioFile file(infoList.at(i).absoluteFilePath());
				file.load();
			 }
		  }
		  else if(core::isDirectory(infoList.at(i).absoluteFilePath()) )	 
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

bool nplTread::trackLessThan(nplPointer a,nplPointer b)
{
    int trackA,trackB;
    trackA=a->tag(TRACK).toInt();
    trackB=b->tag(TRACK).toInt();
    
    return trackA<trackB;
}