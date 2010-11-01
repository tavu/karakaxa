#include"fileTags.h"
#include<QDebug>
#include<player.h>
player::fileTags::fileTags(QString url)
        :file(url.toLocal8Bit().constData() ),
        path(url),
        tags(0),
        properties(0),
        err(0)
{
    using namespace TagLib;
//      file =new MPEG::File(path);

    if (file.isNull() )
    {

        err=NULLFILE;
        return;
    }

    tags = file.tag();

    properties = file.audioProperties();

}

QVariant player::fileTags::title() const
{
    using namespace TagLib;

    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;

    return toQString( tags->title() );
}

QVariant player::fileTags::artist() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return toQString( tags->artist() );
}

QVariant player::fileTags::album() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return toQString( tags->album() );
}

QVariant player::fileTags::comment() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return toQString( tags->comment() );
}

QVariant player::fileTags::genre() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return toQString( tags->genre() );
}

QVariant player::fileTags::year() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return tags->year();
}

QVariant player::fileTags::track() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return tags->track();
}

QVariant player::fileTags::bitrate() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;

    return properties->bitrate();
}

QVariant player::fileTags::length() const
{
    using namespace TagLib;
    if (properties==0 )
    {
        err=NULLFILE;
        return QString();
    }
    err=0;
    return properties->length();
}

bool player::fileTags::setTitle(const QString &s)
{
    using namespace TagLib;

    if (tags==0 )
    {
        err=INVALIDF;
        return false;
    }

    tags->setTitle( toTString(s) );

    file.save();
    return true;
}


bool player::fileTags::setAlbum (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    String ts=toTString(s);
    tags->setAlbum(ts );

    file.save();
    return true;
}

bool player::fileTags::setArtist (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    String ts=toTString(s);
    tags->setArtist(ts );

    file.save();
    return true;
}

bool player::fileTags::setComment (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    tags->setComment(toTString(s) );
    file.save();

    return true;
}

bool player::fileTags::setGenre (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    tags->setGenre(toTString(s) );
    file.save();

    return true;
}

bool player::fileTags::setYear (const unsigned int &i)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    tags->setYear(i);
    file.save();

    return true;
}

bool player::fileTags::setTrack(const unsigned int &i)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALIDF;
        return false;
    }

    err=0;
    tags->setTrack(i);
    file.save();

    return true;
}

TagLib::String player::fileTags::toTString( QString s)
{
    return TagLib::String(s.toUtf8().data(),TagLib::String::UTF8 );
}

QString player::fileTags::toQString(TagLib::String s)
{
//      return QString( QByteArray (s.to8Bit(true) ) );
    return QString(s.toCString(true) );
}

void player::fileTags::toStringList( TagLib::StringList sl,QStringList &ql)
{
    for (unsigned int i=0;i<sl.size();i++)
    {
        ql.append(toQString(sl[i]) );
    }
}

QVariant player::fileTags::tag(tagsEnum t) const
{
    switch (t)
    {
    case TITLE:
    {
        return title();
    }
    case ALBUM:
    {
        return album();
    }
    case ARTIST:
    {
        return artist();
    }
    case GENRE:
    {
        return genre();
    }
    case COMMENT:
    {
        return comment();
    }
    case TRACK:
    {
        return track();

    }
    case YEAR:
    {
        return year();
    }
    case LENGTH:
    {
        return length();
    }
    case BITRATE:
    {
        return bitrate();
    }
    default:
    {
        err=NSTAG;
        return QVariant();
    }
    }
}

bool player::fileTags::setTag(tagsEnum t,const QVariant &var)
{
    switch (t)
    {

    case TITLE:
    {
        return setTitle(var.toString());
    }
    case ALBUM:
    {
        return setAlbum(var.toString());
    }
    case ARTIST:
    {
        return setArtist(var.toString());
    }
    case GENRE:
    {
        return setGenre(var.toString());
    }
    case COMMENT:
    {
        return setComment(var.toString());
    }
    case TRACK:
    {
        return setTrack(var.toInt());

    }
    case YEAR:
    {
        return setYear(var.toInt());
    }
    default:
    {
        err=NSTAG;
        return false;
    }
    }
}

const int player::fileTags::NULLFILE=1;
const int player::fileTags::INVALIDF=2;
const int player::fileTags::WRONGFT=3;
const int player::fileTags::NSTAG=3;
