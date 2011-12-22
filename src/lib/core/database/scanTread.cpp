#include"scanTread.h"

#include<QDebug>
#include<iostream>
#include<core.h>
#include<QHash>
#include <QHBoxLayout>
#include<QPushButton>
#include<KIcon>
#include"libraryImpScan.h"
#include"libraryImpUpdate.h"

core::scanThread::scanThread(database::dbState t,QObject *parent)
        :databaseScanner(t,parent),
        _step(20),
        importer(0)
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

core::scanThread::~scanThread()
{
    if(importer!=0)
    {
        delete importer;
    }

    delete w;
}

void core::scanThread::findAllItemN()
{
    foreach(KUrl u,dirs)
    {
        findItemN(u);
    }

    emit itemsNum(itemNumber);
}

void core::scanThread::init()
{
    label->setText(tr("Starting") );
    if(type()== database::RESCAN)
    {
        importer = new libraryImpScan();
    }
    else
    {
        importer = new libraryImpUpdate();
    }
}


void core::scanThread::scanAllFolders()
{
    label->setText(tr("Scanning") );

    QLinkedList<KUrl>::iterator it=dirs.begin();

    while(it!=dirs.end() && !stopped )
    {
       scanFolder(*it);
       it++;
       dirs.removeFirst();
    }

}

void core::scanThread::save()
{
    label->setText(tr("Saving") );
    progressBar->setMaximum(progressBar->value() );
    importer->save();
    label->setText(tr("done") );
    delete importer;
    importer=0;
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
    QDir dir(url.toLocalFile() );
    QLinkedList<core::albumEntry> albums;
    QLinkedList<QString>images;
	   
    QFileInfoList infoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);
	   
    for (int i=0;i<infoList.size();i++)
    {
		if(stopped)
		{
			 //importer->save();
             //delete importer;
             //importer = 0;
             return true;
		}
		if(core::isPlaylist(infoList.at(i).absoluteFilePath() ) )
		{
		    if(! importer->importPl(infoList.at(i).absoluteFilePath() ) )
		    {
			   errors<<infoList.at(i).absoluteFilePath();
		    }
		}	  
		else if(core::isAudio(infoList.at(i).absoluteFilePath() ) )
		{	      	      
		    albumEntry al=importer->import(infoList.at(i).absoluteFilePath());
		    
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
            importer->saveAlbumArt(cover,al);
			allAlbums.insert(al.id,mark);
        }
    }
    return true;
}

void core::scanThread::run()
{    
    init();
    findAllItemN();       
    scanAllFolders();
    save();
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
    label=new QLabel(w);
    
    QPushButton *cancelB=new QPushButton(w);
    cancelB->setIcon(KIcon("dialog-cancel") );
    cancelB->setFlat(true);
    connect(cancelB,SIGNAL(clicked (bool)),this,SLOT(stop()),Qt::QueuedConnection);
        
    QHBoxLayout *l=new QHBoxLayout(w);
    l->setContentsMargins(0,0,0,0);
    
    l->addWidget(label);
    l->addWidget(progressBar);
    l->addWidget(cancelB);
}
