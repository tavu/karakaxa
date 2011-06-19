#include"queryGeneration.h"
#include<QDebug>
#include"../../files/tagsTable.h"
#include"database.h"
#include"status/playerStatus.h"
using namespace audioFiles;

core::queryGrt::queryGrt(QObject* parent)
  :QObject(parent),
  q(0)
{
   connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
   connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );
}

core::queryGrt::queryGrt(core::queryGrt::abstractQuery *qe,QObject* parent)
  :QObject(parent)
{
    q=qe;
   connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
   connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );
}


bool core::queryGrt::select()
{
    _needUpdate=false;
    if(q==0||!q->isValid() )
    {
	return false;
    }
        
    QSqlDatabase dBase=db->getDatabase();
    
    {
	QSqlQuery quer(dBase );
	
	if(!quer.exec(queryString() ) )
	{
	    status->addErrorP(quer.lastError().text() );
	    status->addError("executing query error");
	    db->closeDatabase(dBase);
	    return false;
	}
	
	foreach(audioFiles::audioFile *f,files)
	{
	    delete f;
	}
	map.clear();
	
	if(quer.size()>0 )
	{
	    files.resize(quer.size() );
	    int i=0;	
	    while ( quer.next() ) 
	    {
		audioFiles::audioFile *f=new audioFiles::audioFile(quer.record(),false );
		files.replace(i,f);
		map.insert(f->path(),f);
		i++;
	    }
	}
	else
	{
	    files.clear();
	    while ( quer.next() ) 
	    {
		audioFiles::audioFile *f=new audioFiles::audioFile(quer.record() );
		files.append(f);
		map.insert(f->path(),f);
	    }
	}   
    }
    
    db->closeDatabase(dBase);
    emit selectionMade();
    
    return true;
}


// QString core::queryGrt::query(int t,equal e,QString value,bool n)
// {
//     QString s("%1 %2 %3");
// 
//     QString tag=tagToSql(t);
//     QString like;
// 
//     if (t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE)
//     {
//         if (value.isEmpty() )
//             return QString();
// 
//         if (e==EQUAL&& !n)
//         {
//             like=QString('=');
//         }
//         else if (e==EQUAL&& n)
//         {
//             like=QString("<>");
//         }
//         else if (e==GREATER&& !n)
//         {
//             like=QString('>');
//         }
//         else if (e==GREATER&& n)
//         {
//             like=QString("<=");
//         }
//         else if (e==LESS&& !n)
//         {
//             like=QString('<');
//         }
//         else if (e==LESS&& n)
//         {
//             like=QString(">=");
//         }
//         else
//         {
//             //error
//             return QString();
//         }
//     }
//     else
//     {
//         if (n)
//         {
//             like= QString("NOT LIKE");
//         }
//         else
//         {
//             like= QString("LIKE");
//         }
// 
//         QString tag=tagToSql(t);
// 
//         core::database::toSqlSafe(value);
// 
//         if (e==STARTS)
//         {
//             value.append('%');
//         }
//         else if (e==ENDS)
//         {
//             value.prepend('%');
//         }
//         else if (e==CONTAINS)
//         {
//             value.prepend('%');
//             value.append('%');
//         }
//         else if (e!=EQUAL)
//         {
//             return QString();
//         }
// 
// 	core::database::toSqlSafe(value);
//         value.append('\"');
//         value.prepend('\"');
//     }
// 
//     s=s.arg(tag);
//     s=s.arg(like);
//     s=s.arg(value);
// 
//     return s;
// }

QList<core::queryGrt::album> core::queryGrt::albums()
{
    QString ret("select album,image,id from artist_album order by album asc");
    QSqlDatabase dBase=db->getDatabase();
    QSqlQuery q(dBase);
    
    if(!q.exec(ret) )
    {
	status->addErrorP(q.lastError().text() );
	status->addError("Could not retrive artists names");
    }
    
    QList<album> l;
    while ( q.next() ) 
    {
	album al;
	al.name=q.record().value(0).toString();
	al.cover=q.record().value(1).toString();
	al.id=q.record().value(2).toInt();
	
	l<<al;
    }
    
    db->closeDatabase(dBase);
    
    return l;
}

QList<core::queryGrt::album> core::queryGrt::albums(QString artist)
{
    QString ret("select distinct album,image,id from artist_album where artist_album.artist = '%1' order by artist_album.album asc");
    core::database::toSqlSafe(artist);
    ret=ret.arg(artist);

    QSqlDatabase dBase=db->getDatabase();      
    QSqlQuery q(dBase );
    
    if(!q.exec(ret) )
    {
	status->addErrorP(q.lastQuery() );
	status->addErrorP(q.lastError().text() );
	status->addError("Could not retrive artists names");
    }
    
    QList<album> l;
    while ( q.next() ) 
    {
	album al;
	al.name=q.record().value(0).toString();
	al.cover=q.record().value(1).toString();
	al.id=q.record().value(2).toInt();
	
	l<<al;
    }
    
    db->closeDatabase(dBase);

    return l;

}

QList<core::queryGrt::album> core::queryGrt::albums(QString artist,core::queryGrt::abstractQuery *qe)
{
    QString ret("select distinct artist_album.album,artist_album.image,artist_album.id from artist_album inner join trackView on artist_album.id=trackView.album_id and artist_album.artist='%1' AND ( %2 ) order by album asc");
    core::database::toSqlSafe(artist);
    ret=ret.arg(artist);
    ret=ret.arg(qe->text() );

    QSqlQuery q(db->getDatabase() );
    if(!q.exec(ret) )
    {
	status->addErrorP(q.lastQuery() );
	status->addErrorP(q.lastError().text() );
	status->addError("Could not retrive artists names");
    }
    
    QList<album> l;
    while ( q.next() ) 
    {
	album al;
	al.name=q.record().value(0).toString();
	al.cover=q.record().value(1).toString();
	al.id=q.record().value(2).toInt();
	
	l<<al;
    }
    
    return l;
}

QStringList core::queryGrt::artists()
{
    QString ret("select distinct artist_album.artist from artist_album order by artist_album.artist asc");
    QSqlDatabase dBase=db->getDatabase();
    QStringList l;    
    
    {
	QSqlQuery q(dBase);
	
	if(!q.exec(ret) )
	{
	    status->addErrorP(q.lastError().text() );
	    status->addError("Could not retrive artists names");
	}
	

	while ( q.next() ) 
	{
	    l<<q.record().value(0).toString();
	}
    }
    
    db->closeDatabase(dBase);
    
    return l;
}

QStringList core::queryGrt::artists(const abstractQuery *qe)
{
    QString ret("select distinct artist_album.artist from artist_album inner join trackView on artist_album.id=trackView.album_id AND ( %1 ) order by artist_album.artist asc");
    ret=ret.arg(qe->text() );
    QStringList l;
    
    QSqlDatabase dBase=db->getDatabase();    
    {
	QSqlQuery q(dBase);
	    
	if(!q.exec(ret) )
	{
	    status->addErrorP(q.lastError().text() );
	    status->addError("Could not retrive artists names");
	}
		
	while ( q.next() ) 
	{
	    l<<q.record().value(0).toString();
	}
    }
    
    db->closeDatabase(dBase);
    return l;
}

QString core::queryGrt::tagToSql(int t)
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
	    return QString("trackView.leadArtist" );
	}
	case PATH:
	{
	    return QString("trackView.path");
	}
	case COUNTER:
	{
	    return QString("trackView.count");
	}	
	case ALBUM_ID:
	{
	    return QString("album_id");
	}
    }
    return QString();
}


//=======================================class query========================================//

//==========matchQuery==============//

core::queryGrt::matchQuery::matchQuery(MATCH m)
  :valid(false),
  matchType(m)
{  
}

core::queryGrt::matchQuery::matchQuery(matchQuery* mq)
{  
    valid=mq->valid;
    matchType=mq->matchType;
    foreach(abstractQuery *q,  mq->queries)
    {
	queries.append(q );
    }
}

core::queryGrt::matchQuery::~matchQuery()
{
  clear();
}


bool core::queryGrt::matchQuery::isValid() const
{
    if(queries.isEmpty() )
    {
	return false;
    }
    bool ret=true;    
    foreach(abstractQuery *q,queries)
    {
	ret = q->isValid() && ret ;
    }
    return ret;
}

void core::queryGrt::matchQuery::clear()
{
    foreach(abstractQuery *q,queries)
    {
	delete q;
    }
    queries.clear();
}



bool core::queryGrt::matchQuery::append(core::queryGrt::abstractQuery *q)
{
    queries.append(q);
    valid=true;
    return true;
}

QString core::queryGrt::matchQuery::text() const
{
    
    QString m;
    if(matchType==AND)
    {
      m=QString(" AND ");
    }
    else
    {
	m=QString(" OR ");
    }
                
    QString q=QString("(");
    
    if(!queries.at(0)->isValid() )
    {
	return QString();
    }
    
    q+=queries.at(0)->text();
    q+=+')';
    for(int i=1;i<queries.size();i++)
    {        
	if(!queries.at(i)->isValid() )
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



//=========tagQuery==========

core::queryGrt::tagQuery::tagQuery()
  :valid(false)
{
}


core::queryGrt::tagQuery::tagQuery(int t,equal e,QVariant var,bool n)
{
    init(t,e,var,n);
}

void core::queryGrt::tagQuery::init(int t, core::queryGrt::equal e, QVariant var, bool n)
{
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
	core::database::toSqlSafe(val);

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


QString core::queryGrt::tagQuery::text() const
{
    QString s;
    
    if(!isValid() )	
    {
	return s;
    }
    
    if(revert)
    {
      s=QString("NOT ");
    }
    
    s.append(q);
    return s;
}

core::queryGrt::tagQuery::tagQuery(core::queryGrt::tagQuery* t)
    :abstractQuery()
{
    tag=t->tag;
    eq=t->eq;
    value=t->value;
    valid=t->valid;
    q=t->q;
    revert=t->revert;
}



