#include"albumQueryGrt.h"

#include<status/playerStatus.h>

#include"./dbFunc.h"
#include<audioFiles.h>
#include<audioFile.h>

bool database::albumQueryGrt::select()
{
    list.clear();
    QString s=queryString();

    if (s.isEmpty() )
    {
        return false;
    }

    QSqlDatabase dBase=db()->getDatabase();

    {
        QSqlQuery quer(dBase );

        if (!quer.exec(s) )
        {
            core::status->addErrorP(quer.lastError().text() );
            core::status->addError("executing query error");
            db()->closeDatabase(dBase);
            return false;
        }

        if (quer.size()>0 )
        {
            list.reserve(quer.size() );
        }

        while ( quer.next() )
        {
            albumEntry a;
            a.id=quer.record().value(0).toInt();
            a.name=quer.record().value(1).toString();
            a.artist=quer.record().value(2).toString();
            a.cover=quer.record().value(3).toString();
            list.append(a );
        }
    }

    db()->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}

QString database::albumQueryGrt::queryString() const
{
    QString ret("SELECT DISTINCT artist_album.id , artist_album.album , artist_album.artist , artist_album.image from artist_album ");


    if (q!=0)
    {
        if (q->isValid() )
        {
            ret=ret.append("INNER JOIN trackView ON artist_album.id=trackView.album_id AND (" + q->text() + ")" );

            if (!artist_.isEmpty() )
            {
                QString s=artist_;
                toSqlSafe(s);
                ret=ret.append("AND artist_album.artist= '"+s+"'" );
            }
        }
        else
        {
            return QString();
        }
    }
    else if (!artist_.isEmpty() )
    {
        QString s=artist_;
        toSqlSafe(s);
        ret=ret.append("WHERE artist_album.artist = '"+s+"'" );
    }

    ret=ret.append(" order by artist_album.album asc");
    return ret;
}

void database::albumQueryGrt::dbEvents(database::dbEventP e)
{
    using namespace audioFiles;
    if(needUpdate() )
    {
        return ;
    }
    int t=e->type();
    
    if(t==FILES_CHANG)
    {
        dbEventAF *ev= static_cast<dbEventAF*>(e.data() );

        foreach(const audioFile &f, ev->files)
        {
            foreach(tagChanges c,f.tagChanged() )
            {
                if (c.tag == ARTIST || c.tag == LEAD_ARTIST ||c.tag == ALBUM )
                {
                    setNeedUpdate();
                    return ;
                }
            }
            if(q!=0 && q->match(f) )
            {
                setNeedUpdate();
                return ;
            }
        }

    }
    queryGrt::dbEvents(e);
}
