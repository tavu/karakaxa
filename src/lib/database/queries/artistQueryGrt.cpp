#include"artistQueryGrt.h"

#include<status/playerStatus.h>
#include<audioFiles.h>

bool database::artistQueryGrt::select()
{
    list.clear();
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
            core::status->addErrorP(quer.lastError().text() );
            core::status->addError("executing query error");
            db()->closeDatabase(dBase);
            return false;
        }

        if(quer.size()>0 )
        {
            list.reserve(quer.size() );
        }

        while ( quer.next() )
        {
            list.append(quer.record().value(0).toString() );
        }
    }

    db()->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}

void database::artistQueryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    using namespace audioFiles;
    
    foreach(tagChanges c,f.tagChanged() )
    {
        if(c.tag == ARTIST || c.tag == LEAD_ARTIST )
        {
            _needUpdate =true;
            emit updateNeeded();
            return ;
        }
    }
    queryGrt::setNeedUpdate(f);
}


QString database::artistQueryGrt::queryString() const
{
    QString ret("select distinct artist_album.artist from artist_album ");

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
