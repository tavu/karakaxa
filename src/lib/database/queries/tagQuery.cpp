#include"tagQuery.h"

#include<audioFiles.h>

#include"../dbFunc.h"


database::tagQuery::tagQuery(QObject *parent)
        :abstractQuery(parent),
        valid(false)
{
}


database::tagQuery::tagQuery(int t,equal e,QVariant var,bool n,QObject *parent)
    :abstractQuery(parent)
{
    init(t,e,var,n);
}

database::tagQuery::tagQuery(database::tagQuery* t, QObject* parent)
        :abstractQuery(parent)
{
    tag=t->tag;
    eq=t->eq;
    value=t->value;
    valid=t->valid;
    q=t->q;
    revert=t->revert;
}


void database::tagQuery::init(int t, equal e, QVariant var, bool n)
{
    using namespace audioFiles;
    
    tag=t;
    eq=e;
    value=var;
    revert=n;

    q=QString ("%1 %2 %3");
    
    QString tag=tagToSql(t);
    QString like;
    QString val=var.toString();

    //var should be an int;
    if (t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE || t==ALBUM_ID)
    {
        bool k;
        var.toInt(&k);
        if (!k)
        {
            valid=false;
            return ;
        }

        if (e==EQUAL)
        {
            like=QString('=');
        }
        else if (e==GREATER)
        {
            like=QString('>');
        }
        else if (e==LESS)
        {
            like=QString('<');
        }
        else
        {
            //error
            valid=false;
            return ;
        }
    }
    else
    {
        like= QString("LIKE");
        toSqlSafe(val);

        if (e==STARTS)
        {
            val.append('%');
        }
        else if (e==ENDS)
        {
            val.prepend('%');
        }
        else if (e==CONTAINS)
        {
            val.prepend('%');
            val.append('%');
        }
        else if (e!=EQUAL)
        {
            valid=false;
            return ;
        }
        val.append('\"');
        val.prepend('\"');
    }

    q=q.arg(tag);
    q=q.arg(like);
    q=q.arg(val);

    valid=true;
}

bool database::tagQuery::match(const audioFiles::audioFile& f) const
{
    using namespace audioFiles;
    bool ret=false;
    QList<tagChanges> l=f.tagChanged();

    foreach(tagChanges c,l)
    {
        if (c.tag==tag)
        {
            ret=true;
            break;
        }
    }

    return ret;
}



QString database::tagQuery::text() const
{
    QString s;

    if (!isValid() )
    {
        return s;
    }

    if (revert)
    {
        s=QString("NOT ");
    }

    s.append(q);
    return s;
}


