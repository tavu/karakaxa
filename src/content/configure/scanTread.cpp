#include"scanTread.h"

#include<QDebug>
#include<iostream>
#include<player.h>

scanTread::scanTread()
        :QThread()
{
    itemNumber=0;
    filesImported=0;
    stopped=false;
//
//      connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );
}

void scanTread::findItemN(QString dir)
{

    QDirIterator it(dir,QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    while (it.hasNext() && !stopped )
    {
        itemNumber++;
        it.next();
    }
    qDebug()<<itemNumber;
    emit itemsNum(itemNumber);
}

bool scanTread::scanFolder(QDir dir)
{
    QFileInfoList infoList=dir.entryInfoList( player::config.files());

    for (int i=0;i<infoList.size();i++)
    {
        if (!stopped)
        {
            if ( !importer.import(infoList.at(i).absoluteFilePath() ) )
            {
// 		    player::errors.setError(importer.error());
            }

            filesImported++;
            emit imported(filesImported);
        }
        else
        {
// 	       emit canceled(filesImported);
            quit();
            return true;
        }
    }

    dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);

    infoList=dir.entryInfoList();

    for (int i=0;i<infoList.size();i++)
    {
        scanFolder(QDir( infoList.at(i).absoluteFilePath()) ) ;
// 	       return false;
    }
    return true;
}

// void scanTread::import(QString file)
// {
//     QString albumArist;
//     tagsTable t=fileTags(file).getTagsTable();
//
//     if( t.tags[LEAD_ARTIST].isNull() )
//     {
// 	 if(t.artists.size()>0)		albumArist=t.artists.at(0) ;
//     }
//     else
//     {
// 	 albumArist=t.tags[LEAD_ARTIST].toString();
//     }
//
//     if( !importer.import(QVariant(albumArist),t) )
//     {
//  	 player::errors.setError(importer.error());
//     }
//     else
//     {
// 	  filesImported++;
// 	  emit imported(filesImported);
//     }
// }

void scanTread::run()
{

    QString file,type;

    QStringList libraryF=player::db.getLibraryFolders();

    for (int i = 0; i<libraryF.size(); i++)
    {
        findItemN(libraryF.at(i));
    }

    for (int i = 0; i<libraryF.size(); i++)
    {
        QDir dir= QDir( libraryF.at(i) );
        scanFolder(dir);
    }
}

void scanTread::stop()
{
    stopped=true;
}
