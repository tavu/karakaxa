#include"queryGeneration.h"
#include<QDebug>
#include<player.h>
queryGrt::queryGrt()
{
}

QString queryGrt::finish(QString s)
{
    s.prepend("select distinct * from trackView where ");
    return s;
}

QString queryGrt::query(tagsEnum t,equal e,QString value,bool n)
{
    QString s("%1 %2 %3");

    QString tag=tagToSql(t);
    QString like;

    if (t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE)
    {
        if (value.isEmpty() )
            return QString();

        if (e==EQUAL&& !n)
        {
            like=QString('=');
        }
        else if (e==EQUAL&& n)
        {
            like=QString("<>");
        }
        else if (e==GREATER&& !n)
        {
            like=QString('>');
        }
        else if (e==GREATER&& n)
        {
            like=QString("<=");
        }
        else if (e==LESS&& !n)
        {
            like=QString('<');
        }
        else if (e==LESS&& n)
        {
            like=QString(">=");
        }
        else
        {
            //error
            return QString();
        }
    }
    else
    {
        if (n)
        {
            like= QString("NOT LIKE");
        }
        else
        {
            like= QString("LIKE");
        }

        QString tag=tagToSql(t);

        player::database::toSqlSafe(value);

        if (e==STARTS)
        {
            value.append('%');
        }
        else if (e==ENDS)
        {
            value.prepend('%');
        }
        else if (e==CONTAINS)
        {
            value.prepend('%');
            value.append('%');
        }
        else if (e!=EQUAL)
        {
            return QString();
        }

        value.append('\"');
        value.prepend('\"');
    }

    s=s.arg(tag);
    s=s.arg(like);
    s=s.arg(value);

    return s;
}

QString queryGrt::connectAnd(QStringList l)
{
    if (l.size()==0)	return QString();

    if (l.size()==1)	return l.at(0);

    QString ret;

    for (int i=0;i<l.size()-1;i++)
    {
        ret.append(l.at(i)+" AND ");
    }

    ret.append(l.at(l.size()-1));

    ret.prepend ('(');
    ret.append  (')');

    return ret;
}

QString queryGrt::albums()
{
    QString ret("select album,image,id from artist_album");
    return ret;
}

QString queryGrt::albums(QString artist)
{
    QString ret("select distinct album,image,id from artist_album where artist='%1'");
    player::database::toSqlSafe(artist);
    ret=ret.arg(artist);
    return ret;

}

QString queryGrt::albums(QString artist,QString s)
{
    QString ret("select distinct artist_album.album,artist_album.image,artist_album.id from artist_album inner join trackView on artist_album.id=trackView.album_id and artist_album.artist='%1' AND %2");
    player::database::toSqlSafe(artist);
    ret=ret.arg(artist);
    ret=ret.arg(s);
    return ret;
}

QString queryGrt::artist()
{
    QString ret("select distinct artist_album.artist from artist_album order by artist_album.artist asc");
    return ret;
}
QString queryGrt::artist(const QString &s)
{
    QString ret("select distinct artist_album.artist from artist_album inner join trackView on artist_album.id=trackView.album_id AND %2 order by artist_album.artist asc");
    ret=ret.arg(s);
    return ret;
}


// QString queryGrt::tracks()
// {
//      QString ret("select distinct * from trackView");
//      return ret;
// }

QString queryGrt::tracks(int albumId)
{
    QString ret("trackView.album_id='%1'");
    ret=ret.arg(albumId);
    return ret;
}

QString queryGrt::tracks(int albumId,QString s)
{
    QString ret("trackView.album_id='%1' and %2");
    ret=ret.arg(albumId);
    ret=ret.arg(s);
    return ret;
}

QString queryGrt::tracks(QString s)
{
    s.prepend("select distinct * from trackView where ");
    return s;
}

QString queryGrt::connectOr(QStringList l)
{
    if (l.size()==0)	return QString();

    if (l.size()==1)	return l.at(0);

    QString ret;

    for (int i=0;i<l.size()-1;i++)
    {
        ret.append(l.at(i)+" OR ");
    }

    ret.append(l.at(l.size()-1));

    ret.prepend ('(');
    ret.append  (')');

    return ret;
}

QString queryGrt::tagToSql(tagsEnum t)
{
    switch (t)
    {
    case ARTIST:
    {
        return QString("trackView.artist" );
    }
    case ALBUM:
    {
        return QString("trackView.album" );
    }
    case TITLE:
    {
        return QString("trackView.title" );
    }
    case COMPOSER:
    {
        return QString("trackView.composer" );
    }
    case GENRE:
    {
        return QString("trackView.genre");
    }
    case COMMENT:
    {
        return QString("trackView.comment") ;
    }
    case TRACK:
    {
        return QString("trackView.tracknumber");
    }
    case YEAR:
    {
        return QString("trackView.year");
    }
    case LENGTH:
    {
        return QString("trackView.length");
    }
    case RATING:
    {
        return QString("trackView.rating");
    }
    case BITRATE:
    {
        return QString("trackView.bitrate");
    }
    case LEAD_ARTIST:
    {
        return QString("trackView.lead_artist" );
    }
    case PATH:
    {
        return QString("trackView.path");
    }
    case COUNTER:
    {
        return QString("trackView.count");
    }
    }
}
