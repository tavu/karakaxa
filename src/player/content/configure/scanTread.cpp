#include"scanTread.h"

#include<QDebug>
#include<iostream>
#include<core.h>
#include<QHash>

scanTread::scanTread()
        :QThread(),
        _step(20)
{
    itemNumber=0;
    filesImported=0;
    stopped=false;
    QStringList l;

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

bool scanTread::scanFolder(KUrl url)
{ 
    QDir dir(url.toLocalFile() );

    QLinkedList<QString> dirs;
    
    QFileInfoList infoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);    
    
    for (int i=0;i<infoList.size();i++)     
    {
	  if(stopped)
	  {
	       quit();
	       return true;
	  }	  
	  if(core::isPlaylist(infoList.at(i).absoluteFilePath() ) )
	  {
	      importer.importPl(infoList.at(i).absoluteFilePath() );
	  }	  
	  else if(core::isAudio(infoList.at(i).absoluteFilePath() ) )
	  {	      	      
	      albumEntry al=importer.import(infoList.at(i).absoluteFilePath());
	      albums.insert(al.id,al);
	      filesImported++;
	      
	      if(filesImported%_step==0)
	      {
		  emit imported(filesImported);
	      }
	  }
	  else if(core::isImage(infoList.at(i).absoluteFilePath() ) )
	  {
	      QString s=core::titleFromPath( infoList.at(i).absoluteFilePath() );
 	      s=s.toUpper();
	      
	      images.insert(s,infoList.at(i).absoluteFilePath() );
	  }
	  else if(core::isDirectory(infoList.at(i).absoluteFilePath()) )
	  {
	      dirs<<infoList.at(i).absoluteFilePath();
	  }
    }
    
    QMap<int,albumEntry>::iterator it;
    
    for(it=albums.begin();it!=albums.end();it++ )
    {
	QString s=image(*it);
	if(!s.isNull() )
	{
	    importer.saveAlbumArt(s,*it);
	}
    }
     
    albums.clear();
    images.clear();
    
    QLinkedList<QString>::iterator dirIt;
    for (dirIt=dirs.begin();dirIt!=dirs.end();dirIt++)
    {
	scanFolder( *dirIt ) ;    
    }    
    return true;
}

QByteArray scanTread::albumKey(albumEntry e)
{
    QByteArray key;
    key.append(e.album);
    key.append(QChar(QChar::Null) );
    key.append(e.artist);
    return key;
}

void scanTread::run()
{
    QString file,type;

    QStringList libraryF=core::db->getLibraryFolders();

    for (int i = 0; i<libraryF.size(); i++)
    {
        findItemN(libraryF.at(i));
    }        
    emit itemsNum(itemNumber);


    for (int i = 0; i<libraryF.size(); i++)
    {
        KUrl dir= KUrl( libraryF.at(i) );
        scanFolder(dir);
    }
    importer.save();
}

void scanTread::stop()
{
    stopped=true;
}

QString scanTread::image(albumEntry &al)
{
    QString ret;
    int num=0;
    
    int val=allAlbums.value(al.id);
    
    if(val==3)
    { 
	return ret;
    }                
    
    ret=images.value(al.album.toUpper() );
    num=3;
    if(ret.isNull() && val<2 )
    {
	ret=images.value("FOLDER" );
	num=2;
    }
    if(ret.isNull() && val<1 )
    {
	if(!images.isEmpty() )
	{
	  ret=images.begin().value();
	}	
	num=1;
    }
    
    if(!ret.isNull() )
    {
	allAlbums.insert(al.id,num);
    }

    return ret;
}
