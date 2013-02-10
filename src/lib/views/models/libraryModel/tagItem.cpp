#include"tagItem.h"
#include<queries/tagQuery.h>
#include<queries/matchQuery.h>
#include<queries/queryGeneration.h>
#include<queries/albumQueryGrt.h>
#include<queries/artistQueryGrt.h>
#include<queries/fileQueryGrt.h>
#include<queries/tagQueryGrt.h>
#include"../../decoration/decoration.h"
views::tagItem::tagItem(audioFiles::tagInfo tag,QObject *parent): QObject(parent),_tag(tag),_customFilter(0)
{
    _tags.resize(audioFiles::INVALID);
    connect(database::db(),SIGNAL( newEvent(database::dbEventP)),this,SLOT(dbEvents(database::dbEventP)) );
}

views::tagItem::tagItem(const views::tagItem &other): QObject(other.parent()),_tag(other._tag),_customFilter(0)
{
    _tags.resize(audioFiles::INVALID);
    connect(database::db(),SIGNAL( newEvent(database::dbEventP)),this,SLOT(dbEvents(database::dbEventP)) );
}

views::tagItem::tagItem(QObject *parent): QObject(parent),_customFilter(0)
{
    _tags.resize(audioFiles::INVALID);
    connect(database::db(),SIGNAL( newEvent(database::dbEventP)),this,SLOT(dbEvents(database::dbEventP)) );
}


void views::tagItem::operator=(const views::tagItem& other)
{
    _tag=other._tag;
    setParent(other.parent() );
}


database::abstractQuery* views::tagItem::filter()
{
    database::abstractQuery *parentQ=0;

    tagItem* parent=parentItem();
    if(parent!=0)
    {
        parentQ=parent->filter();
    }

    if(type() == audioFiles::FILES)
    {
        return 0;
    }

    if(type()==audioFiles::INVALID && parentQ==0 && _customFilter==0)
    {
        return 0;
    }

    database::matchQuery *match=new database::matchQuery(database::AND);
    if(parentQ!=0)
    {
        match->append(parentQ);
    }
    if(type()!=audioFiles::INVALID )
    {
        database::abstractQuery *q;
        if(type()==audioFiles::ALBUM_ARTIST )
        {
            q=new database::tagQuery( audioFiles::ALBUM_ARTIST,database::EQUAL,_tag.property("id") );
        }
        else
        {
            q=new database::tagQuery( type(),database::EQUAL,_tag.data() );
        }
        match->append(q);
    }
    if(_customFilter!=0)
    {
        match->append(_customFilter);
    }

    return match;
}

bool views::tagItem::populate(int type,bool force)
{
    if(type<0||type>audioFiles::FILES)
    {
        qDebug()<<"invalid type:"<<type;
        return false;
    }
    
    if(!force && _tags[type].isSelected )
    {
	return true;
    }
    
    return doPopulate(type);

}

bool views::tagItem::doPopulate(int type)
{
    if(type<0||type>audioFiles::FILES)
    {
        qDebug()<<"invalid type:"<<type;
        return false;
    }

    database::queryGrt *qGrt;

    if(type==audioFiles::ALBUM)
    {
        qGrt=new database::albumQueryGrt();
    }
    else if(type==audioFiles::ALBUM_ARTIST)
    {
        qGrt=new database::artistQueryGrt();
    }
    else if(type==audioFiles::FILES)
    {
        qGrt=new database::filesQueryGrt();
    }
    else
    {
        database::tagQueryGrt *tmp=new database::tagQueryGrt();
        tmp->setTag(type);
        qGrt=tmp;
    }

    database::abstractQuery *f=filter();
    qGrt->setQuery(f);
    if(!qGrt->select() )
    {
        qDebug()<<"queryGeneration returned false";
        qDebug()<<qGrt->queryString();
        return false;
    }

    QList<audioFiles::tagInfo> results=qGrt->results();
    QVector<tagItem*> *tagL=tags(type);
    tagL->clear();
    tagL->reserve(results.size() );

    foreach(audioFiles::tagInfo tag ,results )
    {
        appendItem(tag,type);
    }

    _tags[type].isSelected=true;
    _tags[type].isDirty=false;
    return true;
}

void views::tagItem::appendItem(audioFiles::tagInfo& tag,int type)
{
    QVector<tagItem*> *tagL=tags(type);
    tagL->append(new tagItem(tag,this) );
}

int views::tagItem::size(int type)
{
    if(type<0||type>=audioFiles::INVALID )
    {
        return 0;
    }

    return tags(type)->size();
}


void views::tagItem::setCustomFilter(database::abstractQuery* q)
{
    if(_customFilter!=0)
        delete _customFilter;

    _customFilter=q->clone();
}

bool views::tagItem::hasDataPopulated(int type)
{
    return _tags[type].isSelected;
}

QVariant views::tagItem::icon()
{
    return QVariant(views::decor->tagIcon(type() ) );
}

views::tagItem* views::tagItem::itemAt(int type, int row)
{
    if(type<0||type>=audioFiles::INVALID ||row<0)
    {
        return 0;
    }

    QVector<views::tagItem*> *v=tags(type);

    if(row>=v->size() )
    {
        return 0;
    }

    return v->value(row);
}

void views::tagItem::dbEvents(database::dbEventP e)
{
    using namespace database;
    using namespace audioFiles;
    int t=e->type();
    
    //if any change to the database have occured we mark all as dirty
    if(t==FILES_REM || t==FILES_INS || t==UPDATE_COMP || t==RESCAN_COMP || t==NEW_CONN)
    {
        foreach(tagVec v,_tags)
        {
            v.isDirty=true;
        }
    }
    else if(t==FILES_CHANG)//if an audioFile has changed
    {
        dbEventAF *ev= static_cast<dbEventAF*>(e.data() );

        //for every file that has been altered
        foreach(const audioFile &f, ev->files)
        {
            database::abstractQuery *q=filter();
            //if the filter that has beeb used for the selection match any of the files we mark all the vectors as dirty
            if(q!=0 && q->match(f) )
            {
                for(int i=0; i<audioFiles::INVALID; i++)
                {
                    setNeedUpdate(i);
                }
                return ;
            }
            else
            {
                //for every tag tha it have been altered we set the corresponding vector as dirty
                foreach(tagChanges c,f.tagChanged() )
                {
                    setNeedUpdate(c.tag);
                }
            }
        }
    }
}

void views::tagItem::setNeedUpdate(int t)
{   
    if(_tags[t].isSelected && !_tags[t].isDirty)
    {
        _tags[t].isDirty=true;
        emit needUpdate(t);
    }
    
    if(t==audioFiles::ARTIST ||t==audioFiles::LEAD_ARTIST)
    {
	if(_tags[audioFiles::ALBUM_ARTIST].isSelected && !_tags[audioFiles::ALBUM_ARTIST].isDirty)
	{
	    _tags[audioFiles::ALBUM_ARTIST].isDirty=true;
	    qDebug()<<"dirty";
	    emit needUpdate(audioFiles::ALBUM_ARTIST);
	}
    }
}