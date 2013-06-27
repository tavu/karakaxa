#include"rescanJob.h"

#include<QDebug>
#include<iostream>
#include<QHash>
#include <QHBoxLayout>
#include<QPushButton>
#include<KIcon>

#include<core.h>

#include"../libraryImpScan.h"
#include"../libraryImpUpdate.h"



database::rescanJob::rescanJob(dbState t,QObject *parent)
        :dbThrJob(parent),
        _type(t),
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

}

database::rescanJob::~rescanJob()
{
    if(importer!=0)
    {
        delete importer;
    }

    delete w;
}

void database::rescanJob::findAllItemN()
{
    foreach(KUrl u,dirs)
    {
        findItemN(u);
    }

    emit itemsNum(itemNumber);
}

void database::rescanJob::init()
{
    label->setText(tr("Starting") );
    if(type()== RESCAN)
    {
        importer = new libraryImpScan();
        eventP=dbEventP(new dbEvent(RESCAN_COMP) );
    }
    else
    {
        importer = new libraryImpUpdate();
        eventP=dbEventP(new dbEvent(UPDATE_COMP) );
    }
}


void database::rescanJob::scanAllFolders()
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

void database::rescanJob::save()
{
    label->setText(tr("Saving") );
    progressBar->setMaximum(progressBar->value() );
    importer->save();
    label->setText(tr("done") );
    delete importer;
    importer=0;
}



void database::rescanJob::findItemN(KUrl dir)
{
    if(Basic::isAudio(dir.toLocalFile()) )
    {
        itemNumber++;
    }
    else
    {
        QDirIterator it(dir.toLocalFile(),QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
        while (it.hasNext() && !stopped )
        {
            itemNumber++;
            it.next();
        }
    }
}

bool database::rescanJob::scanFolder(KUrl url)
{
    QDir dir(url.toLocalFile() );
    QLinkedList<albumEntry> albums;
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
        if(Basic::isPlaylist(infoList.at(i).absoluteFilePath() ) )
        {
            if(! importer->importPl(infoList.at(i).absoluteFilePath() ) )
            {
               errors<<infoList.at(i).absoluteFilePath();
            }
        }
        else if(Basic::isAudio(infoList.at(i).absoluteFilePath() ) )
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
        else if(Basic::isImage(infoList.at(i).absoluteFilePath() ) )
        {
            images<<infoList.at(i).absoluteFilePath();
        }
        else if(Basic::isDirectory(infoList.at(i).absoluteFilePath()) )
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

void database::rescanJob::run()
{
    init();
    findAllItemN();
    scanAllFolders();
    save();
    db()->emitEvent(eventP);
}

void database::rescanJob::cancel()
{
    stopped=true;
    eventP->setProperty("canceld",QVariant(true) );
}

void database::rescanJob::setDirs(const QStringList& l)
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


void database::rescanJob::initWidget()
{
    w=new QWidget();
    progressBar=new QProgressBar(w);
    label=new QLabel(w);

    QPushButton *cancelB=new QPushButton(w);
    cancelB->setIcon(KIcon("dialog-cancel") );
    cancelB->setFlat(true);
    connect(cancelB,SIGNAL(clicked (bool)),this,SLOT(cancel()),Qt::QueuedConnection);

    QHBoxLayout *l=new QHBoxLayout(w);
    l->setContentsMargins(0,0,0,0);

    l->addWidget(label);
    l->addWidget(progressBar);
    l->addWidget(cancelB);
}

