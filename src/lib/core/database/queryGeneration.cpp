#include"queryGeneration.h"
#include<QDebug>
#include"../../files/tagsTable.h"
#include"database.h"
#include"status/playerStatus.h"
using namespace audioFiles;

//==========queryGrt============
core::queryGrt::queryGrt(QObject *parent)
  :QObject(parent),q(0)
{
    connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
    connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate(audioFiles::audioFile)) );
}

core::queryGrt::queryGrt(abstractQuery* qe, QObject* parent)
    :QObject(parent),q(qe)
{
    connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
    connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate(audioFiles::audioFile)) );  
}

void core::queryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    if(_needUpdate)
    {
        return ;
    }
    
    if(q!=0)
    {
        _needUpdate = q->match(f);

        if(_needUpdate)
        {
            emit updateNeeded();
        }
    }
}


QString core::queryGrt::tagToSql(int t)
{
    switch (t)
    {
	case ARTIST:
	{
	    return QString("trackView.artist " );
	}
	case ALBUM:
	{
	    return QString("trackView.album " );
	}
	case TITLE:
	{
	    return QString("trackView.title " );
	}
	case COMPOSER:
	{
	    return QString("trackView.composer " );
	}
	case GENRE:
	{
	    return QString("trackView.genre ");
	}
	case COMMENT:
	{
	    return QString("trackView.comment ") ;
	}
	case TRACK:
	{
	    return QString("trackView.tracknumber ");
	}
	case YEAR:
	{
	    return QString("trackView.year ");
	}
	case LENGTH:
	{
	    return QString("trackView.length ");
	}
	case RATING:
	{
	    return QString("trackView.rating ");
	}
	case BITRATE:
	{
	    return QString("trackView.bitrate ");
	}
	case LEAD_ARTIST:
	{
	    return QString("trackView.leadArtist " );
	}
	case PATH:
	{
	    return QString("trackView.path ");
	}
	case COUNTER:
	{
	    return QString("trackView.count ");
	}	
	case ALBUM_ID:
	{
	    return QString("album_id ");
	}
    }
    return QString();
}


//=========filesQueryGrt==============

core::filesQueryGrt::filesQueryGrt(QObject* parent)
  :queryGrt(parent),
  thr(this)
{
//    connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
//    connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );
   
   connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

core::filesQueryGrt::filesQueryGrt(abstractQuery *qe,QObject* parent)
  :queryGrt(parent),
  thr(this)
{
   q=qe;
//    connect(core::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
//    connect(core::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );
   
   connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

bool core::filesQueryGrt::select()
{
    emit selectionCalled();
    _needUpdate=false;
    thr.files.clear();
    if(q==0||!q->isValid() ||thr.isRunning() )
    {
        return false;
    }

   thr.start();
   _needUpdate=false;
   return true;
}

void core::filesQueryGrt::selectionFinished()
{
   emit selectionMade();
}

//=========tagQueryGrt============/

QString core::tagQueryGrt::queryString() const
{
    QString ret("select distinct "); 	
    QString s=tagToSql(tag_);

    if(s.isEmpty() )
    {
	return QString(); 	    	  	    
    }
    ret=ret.append(s).append(" from trackView" );

    if(q!=0)
    {
        if(q->isValid() )
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

void core::tagQueryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    foreach(tagChanges c,f.tagChanged() )
    {
        if(c.tag==tag_)
        {
            _needUpdate = true;
            emit updateNeeded();
            return ;
        }
    }
    
    core::queryGrt::setNeedUpdate(f);
}


bool core::tagQueryGrt::select()
{
    list.clear();
    QString s=queryString();
    
    if(s.isEmpty() )
    {
        return false;
    }
    
    QSqlDatabase dBase=db->getDatabase();
    
    {
        QSqlQuery quer(dBase );

        if(!quer.exec(s) )
        {
            status->addErrorP(quer.lastError().text() );
            status->addError("executing query error");
            db->closeDatabase(dBase);
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
    
    db->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}



//==========artistQueryGrt==========//

bool core::artistQueryGrt::select()
{
    list.clear();
    QString s=queryString();
    
    if(s.isEmpty() )
    {
        return false;
    }
    
    QSqlDatabase dBase=db->getDatabase();

    dBase.open();
    {
        QSqlQuery quer(dBase );

        if(!quer.exec(s) )
        {
            status->addErrorP(quer.lastError().text() );
            status->addError("executing query error");
            db->closeDatabase(dBase);
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
    
    db->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}

void core::artistQueryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    foreach(tagChanges c,f.tagChanged() )
    {
        if(c.tag == ARTIST || c.tag == LEAD_ARTIST )
        {
            _needUpdate =true;
            emit updateNeeded();
            return ;
        }
    }
    core::queryGrt::setNeedUpdate(f);
}


QString core::artistQueryGrt::queryString() const
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

//==========albumQueryGrt==========//

bool core::albumQueryGrt::select()
{
    list.clear();
    QString s=queryString();
    
    if(s.isEmpty() )
    {
        return false;
    }
    
    QSqlDatabase dBase=db->getDatabase();
    
    {
	QSqlQuery quer(dBase );
	
	if(!quer.exec(s) )
	{
	    status->addErrorP(quer.lastError().text() );
	    status->addError("executing query error");
	    db->closeDatabase(dBase);
	    return false;
	}
	
	if(quer.size()>0 )
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
    
    db->closeDatabase(dBase);
    _needUpdate=false;
    return true;
}

QString core::albumQueryGrt::queryString() const
{
    QString ret("SELECT DISTINCT artist_album.id , artist_album.album , artist_album.artist , artist_album.image from artist_album ");


    if(q!=0)
    {
	if(q->isValid() )
	{
	    ret=ret.append("INNER JOIN trackView ON artist_album.id=trackView.album_id AND (" + q->text() + ")" );
	    
	    if(!artist_.isEmpty() )
	    {
		QString s=artist_;
		database::toSqlSafe(s);
		ret=ret.append("AND artist_album.artist= '"+s+"'" );
	    }
	}
	else
	{
	    return QString();
	}
    }
    else if(!artist_.isEmpty() )
    {
	QString s=artist_;
	database::toSqlSafe(s);
	ret=ret.append("WHERE artist_album.artist = '"+s+"'" );
    }
    
    ret=ret.append(" order by artist_album.album asc");    
    return ret;
}

void core::albumQueryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    foreach(tagChanges c,f.tagChanged() )
    {
	 if(c.tag == ARTIST || c.tag == LEAD_ARTIST ||c.tag == ALBUM )
	 {
		_needUpdate =true;
		emit updateNeeded();
		
		return ;
	 }
    }    
    core::queryGrt::setNeedUpdate(f);
}



//=======================================class query========================================//

//==========matchQuery==============//


core::queryGrt::matchQuery::matchQuery(MATCH m)
  :valid(false),
  matchType(m)
{  
}

bool core::queryGrt::matchQuery::match(const audioFiles::audioFile& f) const
{
    bool ret=false;
    
    foreach(abstractQuery *q,queries)
    {
	if( q->match(f) )
	{
	    ret=true;
	    break ;
	}
    }
    
    return ret;
    
}



core::queryGrt::matchQuery::matchQuery(matchQuery* mq)
{  
    valid=mq->valid;
    matchType=mq->matchType;
    foreach(abstractQuery *q,  mq->queries)
    {
	queries.append(q->clone() );
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



bool core::queryGrt::matchQuery::append(abstractQuery *q)
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

void core::queryGrt::tagQuery::init(int t, equal e, QVariant var, bool n)
{
    tag=t;
    eq=e;
    value=var;
    revert=n;
    
    q=QString ("%1 %2 %3");

    QString tag=queryGrt::tagToSql(t);
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

bool core::queryGrt::tagQuery::match(const audioFiles::audioFile& f) const
{
    bool ret=false;
    QList<tagChanges> l=f.tagChanged();
    
    foreach(tagChanges c,l)
    {
	if(c.tag==tag)
	{
	    ret=true;
	    break;
	}
    }
    
    return ret;
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

