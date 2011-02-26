#include"fileTags.h"
#include<QDebug>
#include"tagsTable.h"
#include"audioFiles.h"
#include<stdlib.h>
using namespace player;
audioFiles::fileTags::fileTags(QString url)
        :file(url.toLocal8Bit().constData() ),
        path(url),
        tags(0),
        properties(0),
        err(OK)
{
    using namespace TagLib;
    if (file.isNull() )
    {

        err=NULL_FILE;
        return;
    }

    tags = file.tag();

    properties = file.audioProperties();

}
audioFiles::fileTags::~fileTags()
{
}

QVariant audioFiles::fileTags::title() const
{
    using namespace TagLib;

    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;

    return toQString( tags->title() );
}

QVariant audioFiles::fileTags::artist() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return toQString( tags->artist() );
}

QVariant audioFiles::fileTags::album() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return toQString( tags->album() );
}

QVariant audioFiles::fileTags::comment() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return toQString( tags->comment() );
}

QVariant audioFiles::fileTags::genre() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return toQString( tags->genre() );
}

QVariant audioFiles::fileTags::year() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return tags->year();
}

QVariant audioFiles::fileTags::track() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return tags->track();
}

QVariant audioFiles::fileTags::bitrate() const
{
    using namespace TagLib;
    if (tags==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;

    return properties->bitrate();
}

QVariant audioFiles::fileTags::length() const
{
    using namespace TagLib;
    if (properties==0 )
    {
        err=NULL_FILE;
        return QString();
    }
    err=0;
    return properties->length();
}

bool audioFiles::fileTags::setTitle(const QString &s)
{
    using namespace TagLib;

    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    tags->setTitle( toTString(s) );

    
    return true;
}


bool audioFiles::fileTags::setAlbum (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    String ts=toTString(s);
    tags->setAlbum(ts );

    
    return true;
}

bool audioFiles::fileTags::setArtist (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    String ts=toTString(s);
    tags->setArtist(ts );

    
    return true;
}

bool audioFiles::fileTags::setComment (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    tags->setComment(toTString(s) );
    

    return true;
}

bool audioFiles::fileTags::setGenre (const QString &s)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    tags->setGenre(toTString(s) );
    

    return true;
}

bool audioFiles::fileTags::setYear (const unsigned int &i)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    tags->setYear(i);
    

    return true;
}

bool audioFiles::fileTags::setTrack(const unsigned int &i)
{
    using namespace TagLib;
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    err=OK;
    tags->setTrack(i);
    

    return true;
}

void audioFiles::fileTags::getTags(audioFiles::tagRecord *t)
{
//     audioFiles::tagRecord *r=new audioFiles::tagRecord[FRAME_NUM];
    
//     audioFiles::tagRecord *r=(audioFiles::tagRecord*)malloc(FRAME_NUM*sizeof(audioFiles::tagRecord) );
    
    if(t==0)
      qDebug()<<"null tags";
//     for(player::tagsEnum i; i=TAGS_START; i<=TAGS_END; i++ )
    for(int i=0;i<FRAME_NUM;i++ )
    {
	t[i].value=tag( (player::tagsEnum)i);
	t[i].status=err;
    }
  
}

void audioFiles::fileTags::save()
{
    file.save();
}


QVariant audioFiles::fileTags::tag(player::tagsEnum t) const
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
        err=NS_TAG;
        return QVariant();
    }
    }
}

bool audioFiles::fileTags::setTag(player::tagsEnum t,const QVariant &var)
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
	    err=NS_TAG;
	    return false;
	}
    }
}

// const int audioFiles::fileTags::OK=0;
// const int audioFiles::fileTags::NULL_FILE=1;
// const int audioFiles::fileTags::INVALID_FILE=2;
// const int audioFiles::fileTags::WRONG_FILETYPE=3;
// const int audioFiles::fileTags::NS_TAG=3;




TagLib::String audioFiles::fileTags::toTString( QString s)
{
    return TagLib::String(s.toUtf8().data(),TagLib::String::UTF8 );
}

QString audioFiles::fileTags::toQString(TagLib::String s)
{
//      return QString( QByteArray (s.to8Bit(true) ) );
    return QString(s.toCString(true) );
}

void audioFiles::fileTags::toStringList( TagLib::StringList sl,QStringList &ql)
{
    for (unsigned int i=0;i<sl.size();i++)
    {
        ql.append(toQString(sl[i]) );
    }
}