#include"matchQuery.h"

database::matchQuery::matchQuery(MATCH m,QObject *parent)
        :abstractQuery(parent),
        valid(false),
        matchType(m)
{
}

database::matchQuery::matchQuery(matchQuery* mq,QObject *parent)
    :abstractQuery(parent),
    valid(mq->valid),
    matchType(mq->matchType)
{    
    foreach(abstractQuery *q,  mq->queries)
    {
        queries.append(q->clone() );
    }
}




bool database::matchQuery::match(const audioFiles::audioFile& f) const
{
    bool ret=false;

    foreach(abstractQuery *q, queries)
    {
        if ( q->match(f) )
        {
            ret=true;
            break ;
        }
    }

    return ret;

}





database::matchQuery::~matchQuery()
{
    clear();
}


bool database::matchQuery::isValid() const
{
    if (queries.isEmpty() )
    {
        return false;
    }    

    foreach(abstractQuery *q,queries)
    {
        if(!q->isValid() )
        {
            return false;
        }
    }
    return true;
}

void database::matchQuery::clear()
{
    foreach(abstractQuery *q,queries)
    {
        delete q;
    }
    queries.clear();
}



bool database::matchQuery::append(abstractQuery *q)
{
    queries.append(q);
    valid=true;
    return true;
}

QString database::matchQuery::text() const
{

    QString m;
    if (matchType==AND)
    {
        m=QString(" AND ");
    }
    else
    {
        m=QString(" OR ");
    }

    QString q=QString("(");

    if (!queries.at(0)->isValid() )
    {
        return QString();
    }

    q+=queries.at(0)->text();
    q+=+')';
    
    for (int i=1;i<queries.size();i++)
    {
        if (!queries.at(i)->isValid() )
        {
            return QString();
        }

        q +=m;
        q += '(';
        q += queries.at(i)->text();
        q += ')';
    }
    return q;

}

