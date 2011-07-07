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

const int audioFiles::BEST_COVER=3;

namespace audioFiles
{
  QLinkedList<audioFile>	fileList;
}