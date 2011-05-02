#include"viewsFunc.h"
#include"../../files/tagsTable.h"
QString views::prettyLength(int l)
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

QString views::prettySize(int n)
{
    QString s;
    s.setNum( (double)n/(1024*1024),'g',2 );
    s.append(" Mb");
    return s;
}


QVariant views::pretyTag(QVariant var, int t)
{
    using namespace audioFiles;
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

QString views::tagName(int t)
{
    using namespace audioFiles;
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

void views::init()
{

    decor = new decoration;   
}