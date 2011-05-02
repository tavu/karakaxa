#include"nplFile.h"
#include<QDebug>
// #include<player.h>
#include"../core.h"
#include"../../files/fileTags.h"
using namespace audioFiles;
core::nplFile::nplFile(QString s)
        :nplTrack()
{
    file=new audioFile(s);
        
    if (file==0 )
    {
	qDebug()<<"null file";
        ok=false;
    }
    else if(!core::exists(s) )
    {
	ok=false;
    }
    else
    {
      //if the file is valid we read the info we are soure that we will use.
        file->load();
    }
//     file->setMutable(true);

}

void core::nplFile::play()
{
    int c=file->tag(COUNTER).toInt();
    file->setTag(COUNTER,QVariant(c+1) );
}

QVariant core::nplFile::artist()
{
    if(file==0)	return QVariant();
    
    return file->albumArtist();
}


core::nplFile::~nplFile()
{
   qDebug()<<"deleting nplFile";
   delete file;
}

int core::nplFile::length()
{
    if(file==0)	return 0;
    return file->tag(LENGTH).toInt();
}

QString core::nplFile::path()
{
    if(file==0)	return QString();
    return file->path();
}

QString core::nplFile::title()
{
    if(file==0)	return QString();
    return file->tag(TITLE).toString();
}

int core::nplFile::type()
{
    return NPLAUDIOFILE;
}

QString core::nplFile::cover()
{
    if(file==0)	return QString();
    return file->cover();
}

QVariant core::nplFile::tag(int t)
{
    if(file==0)	return QVariant();
    return file->tag(t);
}

audioFile* core::nplFile::getAudioFile()
{
    return file;
}