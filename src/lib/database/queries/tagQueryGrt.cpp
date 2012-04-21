#include"tagQueryGrt.h"
#include"abstractQuery.h"

#include<status/playerStatus.h>
#include<audioFiles.h>

QString database::tagQueryGrt::queryString() const
{
    QString ret("select distinct ");
    QString s=abstractQuery::tagToSql(tag_);

    if (s.isEmpty() )
    {
        return QString();
    }
    ret=ret.append(s).append(" from trackView" );

    if (q!=0)
    {
        if (q->isValid() )
        {
            ret=ret.append(" WHERE ").append(q->text() );
        }
        else
        {
            return QString();
        }
    }
    return ret;
}


void database::tagQueryGrt::dbEvents(database::dbEventP e)
{
    using namespace audioFiles;
    if(needUpdate() )
    {
        return ;
    }    

    if(e->type()==FILES_CHANG)
    {
        dbEventAF *ev= static_cast<dbEventAF*>(e.data() );

        foreach(const audioFile &f, ev->files)
        {
            foreach(tagChanges c,f.tagChanged() )
            {
                if (c.tag == tag_ )
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



bool database::tagQueryGrt::select()
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
            list.append(quer.record().value(0).toString() );
        }
    }

    db()->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}
