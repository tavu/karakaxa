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
    return file->tag(player::LENGTH).toInt();
}

QString player::nplFile::path()
{
    return file->getPath();
}

QString player::nplFile::title()
{
    return file->tag(player::TITLE).toString();
}

QString player::nplFile::type()
{
    return QString("AudioFile");
}

QVariant player::nplFile::tag(tagsEnum t)
{
    return file->tag(t);
}

audioFile* player::nplFile::getAudioFile()
{
    return file;
}