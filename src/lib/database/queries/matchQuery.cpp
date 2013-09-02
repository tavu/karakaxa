#include"matchQuery.h"
#include<QDebug>

database::matchQuery::matchQuery(MATCH m,QObject *parent)
        :abstractQuery(parent),
        matchType(m)
{
}

database::matchQuery::matchQuery(matchQuery* mq,QObject *parent)
    :abstractQuery(parent),
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
    if(q==0)
    {
        return false;
    }
    queries.append(q);
    return true;
}


QString database::matchQuery::text(QString table) const
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

    q+=queries.at(0)->text(table);
    q+=+')';
    
    for (int i=1;i<queries.size();i++)
    {
        if (!queries.at(i)->isValid() )
        {
            return QString();
        }

        q +=m;
        q += '(';
        q += queries.at(i)->text(table);
        q += ')';
    }
    return q;

}

QList< int > database::matchQuery::tags() const
{
    QList<int> tags;
    foreach(abstractQuery *q,queries)
    {
        if(!q->isValid() )
        {
            return QList<int>();
        }
        tags.append(q->tags());
    }
    
    return tags;
}

