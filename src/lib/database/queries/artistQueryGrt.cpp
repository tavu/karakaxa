#include"artistQueryGrt.h"

#include<Basic/status.h>
#include<audioFiles.h>

bool database::artistQueryGrt::select()
{
    list.clear();
	resultsList.clear();
    QString s=queryString();

    if(s.isEmpty() )
    {
        return false;
    }

    QSqlDatabase dBase=db()->getDatabase();

    dBase.open();
    {
        QSqlQuery quer(dBase );

        if(!quer.exec(s) )
        {
            Basic::msg()->logErr(quer.lastError().text() );
            Basic::msg()->error("executing query error");
            db()->closeDatabase(dBase);
            return false;
        }

        if(quer.size()>0 )
        {
            list.reserve(quer.size() );
			resultsList.reserve(quer.size() );
        }

        while ( quer.next() )
        {
            list.append(quer.record().value(0).toString() );
			audioFiles::tagInfo t=audioFiles::tagInfo(Basic::ALBUM_ARTIST,quer.record().value(0) );
			t.setProperty("id",quer.record().value(1));
			resultsList<<t;
        }
    }

    db()->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}

void database::artistQueryGrt::dbEvents(database::dbEventP e)
{
    using namespace audioFiles;
    if(e->type() ==FILES_CHANG)
    {
        dbEventAF *ev= static_cast<dbEventAF*>(e.data() );
        foreach(const audioFile &f, ev->files)
        {
            foreach(tagChanges c,f.tagChanged() )
            {
                if(c.tag == Basic::ARTIST || c.tag == Basic::LEAD_ARTIST )
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
    
    database::queryGrt::dbEvents(e);
}


QString database::artistQueryGrt::queryString() const
{
    QString ret("select distinct artist_album.artist, artist_album.artist_id from artist_album ");

    if(q!=0)
    {
        if(q->isValid() )
        {
            ret=ret.append(" inner join trackView on artist_album.id=trackView.album_id AND ( " + q->text() +")" );
        }
        else
        {
            return QString();
        }
    }
    ret=ret.append("order by artist_album.artist asc");
    return ret;
}
