#include"scanTread.h"

#include<QDebug>
#include<iostream>
#include<core.h>
#include<QHash>
#include <QHBoxLayout>
#include<QPushButton>
#include<KIcon>

core::scanThread::scanThread(QObject *parent)
        :QThread(parent),
        _step(20)
{
    itemNumber=0;
    filesImported=0;
    stopped=false;
    
    initWidget();
    progressBar->setMaximum(0);
    progressBar->setMinimum(0);

    connect(this,SIGNAL(itemsNum(int)),progressBar,SLOT(setMaximum(int)),Qt::QueuedConnection );
    connect(this,SIGNAL(imported(int)),progressBar,SLOT(setValue(int)),Qt::QueuedConnection );
    
    //      connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );
}

void core::scanThread::findItemN(KUrl dir)
{

    QDirIterator it(dir.toLocalFile(),QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    while (it.hasNext() && !stopped )
    {
        itemNumber++;
        it.next();
    }
}

bool core::scanThread::scanFolder(KUrl url)
{ 
//     QLinkedList<QString> dirs;
    
    {
	   QDir dir(url.toLocalFile() );    
	   QLinkedList<core::albumEntry> albums;    
	   QLinkedList<QString>images;
	   
	   QFileInfoList infoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);    
	   
	   for (int i=0;i<infoList.size();i++)     
	   {
		if(stopped)
		{
			 importer.save();
			 quit();
			 return true;
		}	  
		if(core::isPlaylist(infoList.at(i).absoluteFilePath() ) )
		{
		    if(! importer.importPl(infoList.at(i).absoluteFilePath() ) )
		    {
			   errors<<infoList.at(i).absoluteFilePath();
		    }
		}	  
		else if(core::isAudio(infoList.at(i).absoluteFilePath() ) )
		{	      	      
		    albumEntry al=importer.import(infoList.at(i).absoluteFilePath());
		    
		    if(al.name.isEmpty() )//an error ocured
		    {
			   errors<<infoList.at(i).absoluteFilePath();
		    }
		    else
		    {
			   albums<<al;
		    }
		    
		    filesImported++;
		    
		    if(filesImported%_step==0)
		    {
			   emit imported(filesImported);
		    }
		}
		else if(core::isImage(infoList.at(i).absoluteFilePath() ) )
		{	      
		    images<<infoList.at(i).absoluteFilePath();
		}
		else if(core::isDirectory(infoList.at(i).absoluteFilePath()) )
		{
		    dirs<<KUrl(infoList.at(i).absoluteFilePath() );
		}
	   }
	   
	   foreach(albumEntry al,albums)
	   {
		  QString cover;
 		  int mark=audioFiles::bestCover(images,al.name,cover);
		  int k=allAlbums[al.id];
		  if(mark>k)
		  {
			 importer.saveAlbumArt(cover,al);
			 allAlbums.insert(al.id,mark);
		  }
	   }
    }
    
/*    foreach(QString dir,dirs)
    {
	   scanFolder( KUrl(dir) ) ;    
    }   */ 
    return true;
}

void core::scanThread::run()
{
    label->setText(tr("Starting") );
    foreach(KUrl u,dirs)
    {
        findItemN(u);
    }
    
    emit itemsNum(itemNumber);
    
    label->setText(tr("Scanning") );
    
    QLinkedList<KUrl>::iterator it=dirs.begin();

    while(it!=dirs.end() )
    {	           
        scanFolder(*it);
	   it++;
	   dirs.removeFirst();
    }
    
    label->setText(tr("Saving") );
    progressBar->setMaximum(progressBar->value() );
    importer.save();
    label->setText(tr("done") );
}

void core::scanThread::stop()
{
    stopped=true;
}

void core::scanThread::setDirs(const QStringList& l)
{
    if(!dirs.isEmpty() )
    {
	   return ;
    }
    
    foreach(QString s,l)
    {
	   KUrl u(s);
	   if(u.isValid() )
	   {
		  dirs<<u;
	   }
    }
}


void core::scanThread::initWidget()
{
    w=new QWidget();
    progressBar=new QProgressBar(w);
//     progressBar->setFixedWidth(100);
    label=new QLabel(w);
    
    QPushButton *cancelB=new QPushButton(w);
    cancelB->setIcon(KIcon("dialog-cancel") );
    cancelB->setFlat(true);
//     cancelB->setAutoFillBackground(true);
    connect(cancelB,SIGNAL(clicked (bool)),this,SLOT(stop()),Qt::QueuedConnection);
        
    QHBoxLayout *l=new QHBoxLayout(w);
    l->setContentsMargins(0,0,0,0);
    
    l->addWidget(label);
    l->addWidget(progressBar);
    l->addWidget(cancelB);
//     return w;
}

QWidget* core::scanThread::widget()
{
    return w;
}