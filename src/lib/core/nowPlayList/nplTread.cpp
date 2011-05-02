#include"nplTread.h"
// #include<KMimeType>
#include<QDirIterator>
#include<QDebug>
#include"nplFile.h"
#include"../core.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include"nplStream.h"

#define test qDebug()<<"test";

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
//     core::m3uPl m3u(url);
//     m3u.load();	
//     for (int i=0;i<m3u.size() && !canceled;i++)    
    {            
//       addSingleFile(m3u.item(i));
    }
}

void nplTread::addSingleFile(const QString& url)
{
    nplPointer tr=core::nplTrack::getNplTrack(url);
    list<<tr;
    
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
// 	qDebug()<<"ffffffffff "<<info.filePath();
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
