#include"viewsFunc.h"
#include<Basic/tagsTable.h>
#include<QDebug>
#include"actionMenu.h"


QString views::prettyLength(int l)
{
    QString s;
    int min=l/60;
    int hour=min/60;
    min=min-hour*60;
    int sec=l%60;

    s.append(QString::number(sec));
    if(sec<10)
    {
	 s.prepend(QString::number(0) );
    }
    
    s.prepend(QString::number(min)+':');
    if(min<10)
    {
	 s.prepend(QString::number(0) );
    }               
    
    if (hour>0)
    {
        s.prepend(QString::number(hour)+':');
    }
    
    return s;
}

QString views::prettyLength(qint64 l)
{
    return prettyLength( (int)(l/1000) );
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
    using namespace Basic;
    
    if (t==LENGTH )
    {
	   if ( var.toInt()==0)
	   {
		    return QVariant();
	   }
	   return prettyLength(var.toInt() );
    }
    else if(t==YEAR || t==BITRATE || t==TRACK)
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
    else if(t==RATING || t==COUNTER)
    {
	   return var;
    }
    else
    {
	   return QVariant(var.toString().simplified() );
    }
}

QString views::tagName(int t)
{
    using namespace Basic;
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

void views::cleanUp()
{
    delete decor;
    delete actionMenu::_instance;
}


int views::compare(const QString& first, const QString& second)
{
	QString s1=first.simplified();
	QString s2=second.simplified();
	
	if(s1.startsWith("the ") )
	{
		s1.remove(0, 4);
	}
	s1.remove("'");

	if(s2.startsWith("the ") )
	{
		s2.remove(0,4);
	}
	s2.remove("'");
	
	return s1.compare(s2,Qt::CaseInsensitive);

}
