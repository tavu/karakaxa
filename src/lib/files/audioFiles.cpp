#include"audioFiles.h"
// #include<player.h>
#include"mp3Tags.h"
#include"audioFile.h"
#include"../core/core.h"
audioFiles::fileTags* audioFiles::getFileTags(const QString path)
{
    fileTags *ret;

    QString f=core::format(path);
    if (QString::compare(QString("mp3"),f, Qt::CaseInsensitive )==0)
    {
        ret=new mp3Tags(path);
    }
    else
    {
        ret=new fileTags(path);
    }
    return ret;
}

int audioFiles::coverMark(const QString &al, const QString &cov)
{
    QString album=al.toUpper();

    QString cover=core::titleFromPath(cov);
    
    if(album==cover)
    {
	return 3;
    }
    
    if(cover==QString("FOLDER" ) )
    {
	return 2;
    }
    
    return 1;
}

int audioFiles::bestCover( const QLinkedList<QString> &covers,QString album,QString &cover)
{
    int mark=0;
    album=album.toUpper();
    foreach(QString c,covers)
    {
	   QString s=core::titleFromPath(c);
	   s=s.toUpper();
	   
	   if(s==album)
	   {
		  cover=c;
		  mark=5;
	   }
	   else if(s==QString("FOLDER") && mark<4 )
	   {
		  cover=c;
		  mark=4;
	   }
	   else if(s==QString("FRONT") && mark<3 )
	   {
		  cover=c;
		  mark=3;
	   }
	   else if(s.contains("FRONT") && mark<2 )
	   {
		  cover=c;
		  mark=2;
	   }
	   else if(mark<1)
	   {
		  cover=c;
		  mark=1;
	   }
    }
    
    return mark;
}


const int audioFiles::BEST_COVER=5;

namespace audioFiles
{
  QLinkedList<audioFile>	fileList;
}