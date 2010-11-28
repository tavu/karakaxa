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
}

bool scanTread::scanFolder(QDir dir)
{
    QStringList l;
    l<<player::config.files()<<player::config.playListFiles();
    QFileInfoList infoList=dir.entryInfoList( l);

     for (int i=0;i<infoList.size();i++)
     {
	  if(stopped)
	  {
	       quit();
	       return true;
	  }
	  if(player::isPlaylist(infoList.at(i).absoluteFilePath() ) )
	  {
	      qDebug()<<"Import playlist";
	      importer.importPl(infoList.at(i).absoluteFilePath() );
	  }
	  else
	  {
	      importer.import(infoList.at(i).absoluteFilePath() );
	  }
	  
          filesImported++;
          emit imported(filesImported);        
     }

    dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);

    infoList=dir.entryInfoList();

    for (int i=0;i<infoList.size();i++)
    {
        scanFolder(QDir( infoList.at(i).absoluteFilePath()) ) ;
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
    emit itemsNum(itemNumber);


    for (int i = 0; i<libraryF.size(); i++)
    {
        QDir dir= QDir( libraryF.at(i) );
        scanFolder(dir);
    }
    importer.save();
}

void scanTread::stop()
{
    stopped=true;
}
