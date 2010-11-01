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
    audioFile::releaseAudioFile(file);
}

QString player::nplFile::artist()
{
    QString s=file->tag(player::LEAD_ARTIST).toString();
    if (s.isEmpty() )
    {
        s=file->tag(player::ARTIST).toString();
    }
    return s;
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

QString player::nplFile::album()
{
    return file->tag(player::ALBUM).toString();
}

int player::nplFile::trackN()
{
    return file->tag(player::TRACK).toInt();
}

QString player::nplFile::type()
{
    return QString("AudioFile");
}
