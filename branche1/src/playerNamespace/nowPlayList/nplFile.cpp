#include"nplFile.h"
#include<player.h>
player::nplFile::nplFile(QString s)
        :nplTrack()
{
    file=player::audioFile::getAudioFile(s);

    if (file==0 )
    {
        ok=false;
        return ;
    }
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
    return file->getPath();
}

QString player::nplFile::title()
{
    if(file==0)	return 0;
    return file->tag(player::TITLE).toString();
}

int player::nplFile::type()
{
    return NPLAUDIOFILE;
}

QString player::nplFile::cover()
{
    if(file==0)	return 0;
    return file->cover();
}

QVariant player::nplFile::tag(tagsEnum t)
{
    if(file==0)	return 0;
    return file->tag(t);
}

audioFile* player::nplFile::getAudioFile()
{
    return file;
}