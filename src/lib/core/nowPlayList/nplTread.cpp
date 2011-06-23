#include"nplTread.h"
// #include<KMimeType>
#include<QDirIterator>
#include<QDebug>
#include"nplFile.h"
#include"../core.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include"nplStream.h"
#include"playlist/abstractPlaylist.h"


nplTread::nplTread()
        :QThread(),
        canceled(false),
        size(10)
{    

//     statusBar.addPermanentWidget(w);

    connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );
//     connect(&npList,SIGNAL(cancelThreads()),this ,SLOT(cancel() ),Qt::QueuedConnection );
}

void nplTread::cancel()
{
    canceled=true;
}


nplTread::~nplTread()
{
//     statusBar.removeWidget(w);
    qDebug()<<"quit";
//     delete w;
}

void nplTread::run()
{
    foreach(QUrl url, urlList)
    {
	if(!canceled)
	{
	    addMedia(url.toLocalFile() );
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
	    addMedia(url);
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
      npList->insert(list,pos);
    }
}


void nplTread::addMedia(const QString &url)
{
    if (core::isDirectory(url) )	
    {
      addDirectory(url);
    }
    else if(core::isPlaylist(url) )
    {
      addPlaylist(url);
    }
    else if(core::isAudio(url) )
    {
      addSingleFile(url);
    }
}


void nplTread::addPlaylist(const QString& url)
{
    abstractPlaylist *pl=getPlaylist(url);
    if(pl==0)
    {
	   status->addError(tr("Can't load playlist") );
	   return;
    }
    
    pl->load();	
    for (int i=0;i<pl->size() && !canceled;i++)    
    {            
	   addSingleFile(pl->item(i));
    }
    delete pl;
}

void nplTread::addSingleFile(const QString& url)
{
    nplPointer tr=core::nplTrack::getNplTrack(url);
    list<<tr;
       	  
    if(tr->type()==NPLAUDIOFILE)		
    {				 
	   audioFile file(url);		 
	   file.load();	
    }
    
    if(list.size()>=size )	
    {
	npList->insert(list,pos);
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

void nplTread::addDirectory(const QString &url)
{
    QDirIterator it(url,QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    QFileInfo info;
    while (it.hasNext() && !canceled )
    {
        it.next();
        info=it.fileInfo();
	
	if(core::isAudio(info.filePath()) )
	{
	    addSingleFile(info.filePath());
	}	
	else if(core::isDirectory(info.filePath() ) )
	{
	    addDirectory(info.filePath() );
	}
    }
}
