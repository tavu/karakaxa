#include<player.h>
#include"../content/edit/editTrackContent.h"
#include<QRegExp>
#include<QObject>
#include<KMimeType>
#include<QLinkedList>


namespace player
{
database 		db;
soundEngine		engine;
contentHandler 		contentHandlr;
PlayerConfigure 	config;
nplaylist 		npList;
QPalette		pal;
pStatusBar		statusBar;
decoration 		decor;
QLinkedList<audioFile*>	audioFiles;
};

void player::editTrack(const QString &s)
{
     editTrackContent *t=new editTrackContent(s);
     player::contentHandlr.addContent(t,true);
}

QString player::titleFromPath(const QString &path)
{
    int l,r;
    r=path.lastIndexOf('.');
    l=path.lastIndexOf('/');

    return path.mid(l+1,r-l-1);
}

QString player::prettyLength(int l)
{
    QString s;
    int min=l/60;
    int hour=min/60;
    int sec=l%60;

    s.append(QString::number(min)+':'+QString::number(sec));

    if (hour>0)
    {
        s.prepend(QString::number(hour)+':');
    }
    
    return s;
}

QString player::prettySize(int n)
{
    QString s;
    s.setNum( (double)n/(1024*1024),'g',2 );
    s.append(" Mb");
    return s;
}

QString player::format(QString path)
{

    path=path.mid(path.lastIndexOf('.')+1 );
    return path;
}

QString player::folder(QString path)
{
    if(path.isEmpty() )
    {
	return QString();
    }
    return path.left(path.lastIndexOf('/') );
}

bool player::isStream(const QString s)
{
    return isStream(QUrl(s) );
}

bool player::isStream(const QUrl url)
{
    if (url.scheme() == "http" || url.scheme() == "mms" || url.scheme() == "smb" )
    {
        return true;
    }
    return false;
}

bool player::isAudio(const QString &url)
{
    KMimeType::Ptr type = KMimeType::findByUrl(url );

    QStringList l=config.files();
    if (l.contains(type->name() ) )
    {
        return true;
    }
    return false;
}

bool player::isImage(const QString &url)
{
    QString s=player::format(url);
    
    s=s.toUpper();    
    if(config.imagefiles().contains(s) )
    {
	return true;
    }
    
    return false;
}

bool player::isDirectory(const QString &url)
{
    KMimeType::Ptr type = KMimeType::findByUrl(url );

    if (type->name() == "inode/directory")
    {
        return true;
    }
    return false;
}

bool player::isPlaylist(const QString &url)
{
    QString tmp=url.right(3);
    if (QString::compare("m3u",url.right(3),Qt::CaseInsensitive)==0)
    {
        return true;
    }
    return false;
}

QString player::tagName(tagsEnum t)
{
    switch (t)
    {
	case ALBUM:
	{
	    return QString(QObject::tr("Album") );
	}
	case TITLE:
	{
	    return QString(QObject::tr("Title") );
	}
	case COMPOSER:
	{
	    return QString(QObject::tr("Composer") );
	}
	case GENRE:
	{
	    return QString(QObject::tr("Genre") );
	}
	case COMMENT:
	{
	    return QString(QObject::tr("Comment") );
	}
	case TRACK:
	{
	    return QString(QObject::tr("Track") );
	}
	case YEAR:
	{
	    return QString(QObject::tr("Year") );
	}
	case LENGTH:
	{
	    return QString(QObject::tr("Length") );
	}
	case RATING:
	{
	    return QString(QObject::tr("Rating") );
	}
	case BITRATE:
	{
	    return QString(QObject::tr("Bitrate") );
	}
	case LEAD_ARTIST:
	{
	    return QString(QObject::tr("Lead artist") );
	}
	case ARTIST:
	{
	    return QString(QObject::tr("Artist") );
	}
	case PATH:
	{
	    return QString(QObject::tr("Path") );
	}
	case COUNTER:
	{
	    return QString(QObject::tr("Played counter") );
	}
	default:
	{
	    return QString();
	}
    }
}

int player::tagSize(tagsEnum t)
{
    switch (t)
    {
    case TRACK:
    {
        return 10;
    }
    case YEAR:
    {
        return 60;
    }
    case LENGTH:
    {
        return 10;
    }
    case RATING:
    {
        return 30;
    }
    case BITRATE:
    {
        return 10;
    }
    case PATH:
    {
        return 60;
    }
    case COUNTER:
    {
        return 20;
    }
    default:
    {
        return 50;
    }
    }
}


QVariant player::pretyTag(QVariant var, int t)
{
    if (t==LENGTH )
    {
	if ( var.toInt()==0)
	{
		return QVariant();
	}
	return prettyLength(var.toInt() );
    }
    if(t==YEAR || t==BITRATE || t==TRACK)
    {
	if(var.toInt()==0 )
	{
	    return QVariant();
	}
	else
	{
	    return var;
	}
    }
    if(t==RATING || COUNTER)
    {
	return var;
    }
    else
    {
	QString s=var.toString();
	return QVariant(s);
    }
}
bool player::exists(const QString &url)
{
    QFile f(url);
    return f.exists();
}

void player::init()
{
      statusBar.init();
      db.init();
      engine.init();      
}