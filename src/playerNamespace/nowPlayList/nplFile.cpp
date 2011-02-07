#include"nplFile.h"
#include<player.h>
player::nplFile::nplFile(QString s)
        :nplTrack()
{
    file=player::audioFile::getAudioFile(s);
        
    if (file==0 )
    {
	qDebug()<<"null file";
        ok=false;
    }
    else if(!file->isValid())
    {
	ok=false;
    }
    else
    {
      //if the file is valid we read the info we are soure that we will use.
        file->tag(TITLE);
	file->tag(TRACK);
	file->tag(LENGTH);
    }
    
}

QVariant nplFile::artist()
{
    if(file==0)	return QVariant();
    
    return file->albumArtist();
}


player::nplFile::~nplFile()
{
  qDebug()<<"deleting nplFile";
    audioFile::releaseAudioFile(file);
}

int player::nplFile::length()
{
    if(file==0)	return 0;
    return file->tag(player::LENGTH).toInt();
}

QString player::nplFile::path()
{
    if(file==0)	return QString();
    return file->getPath();
}

QString player::nplFile::title()
{
    if(file==0)	return QString();
    return file->tag(player::TITLE).toString();
}

int player::nplFile::type()
{
    return NPLAUDIOFILE;
}

QString player::nplFile::cover()
{
    if(file==0)	return QString();
    return file->cover();
}

QVariant player::nplFile::tag(tagsEnum t)
{
    if(file==0)	return QVariant();
    return file->tag(t);
}

audioFile* player::nplFile::getAudioFile()
{
    return file;
}