#include"tagSelector.h"
#include<queries/tagQuery.h>
#include<queries/matchQuery.h>
#include<views/decoration/decoration.h>
#include<views/viewsFunc.h>
#include<database/queries/provider/queryProvider.h>

views::tagSelector::tagSelector(audioFiles::tagInfo tag,QObject *parent): QObject(parent),_tag(tag),_customFilter(0)
{
}

views::tagSelector::tagSelector(QObject *parent): QObject(parent),_customFilter(0)
{
}


void views::tagSelector::operator=(const views::tagSelector& other)
{
    _tag=other._tag;
    setParent(other.parent() );    
}

views::tagSelector::~tagSelector()
{
    if(_customFilter!=0)
        delete _customFilter;
    
    foreach (tagVec *value, _tags)
    {
        delete value;
    }
}


database::abstractQuery* views::tagSelector::filter() const
{
    database::abstractQuery *parentQ=0;

    tagSelector* parent=parentItem();
    if(parent!=0)
    {
        parentQ=parent->filter();
    }

    if(type() == Basic::FILES)
    {
        return 0;
    }

    if(type()==Basic::INVALID && parentQ==0 && _customFilter==0)
    {
        return 0;
    }

    database::matchQuery *match=new database::matchQuery(database::AND);
    if(parentQ!=0)
    {
        match->append(parentQ);
    }
    
    if(type()!=Basic::INVALID )
    {
        database::abstractQuery *q;
        q=new database::tagQuery( type(),database::EQUAL,_tag.data() );
        match->append(q);
    }
    if(_customFilter!=0)
    {
        match->append(_customFilter);
    }

    return match;
}

bool views::tagSelector::populate(int type,bool force)
{
    if(type<0||type>Basic::FILES)
    {
        qDebug()<<"invalid type:"<<type;
        return false;
    }
    
    
    if(_tags.contains(type) && !force && _tags[type]->isSelected && !_tags[type]->isDirty )
    {
	return false;
    }
    
    return doPopulate(type);

}

bool views::tagSelector::doPopulate(int type)
{
    database::queryProvider *pr=new database::queryProvider(type);
    database::abstractQuery *f=filter();
        
    if(pr->select(f) !=Basic::OK )
    {
        qDebug()<<"query data provider returned false";
        qDebug()<<pr->lastErrorStr();
        delete pr;
        return false;
    }
    
    
    QList<audioFiles::tagInfo> results=pr->results();      
    
    _tags[type]=new tagVec();
    QVector<tagSelector*> *tagL=tags(type);
    
    tagL->reserve(results.size() );

    for(int i=0;i<results.size();i++)
    {        
//         audioFiles::tagInfo t=results[i];
        appendItem(results[i],tagL);
    }

    _tags[type]->isSelected=true;
    _tags[type]->isDirty=false;
    delete pr;
    return true;
}

void views::tagSelector::appendItem(audioFiles::tagInfo tag,QVector<tagSelector*> *tagL)
{
    tagSelector *i=new tagSelector(tag,this);
    tagL->append(i);
}

int views::tagSelector::size(int type)
{
    QVector<tagSelector*> *v=tags(type);
    if(v==0 )
    {
        return 0;
    }

    return v->size();
}


void views::tagSelector::setCustomFilter(database::abstractQuery* q)
{
    if(_customFilter!=0)
        delete _customFilter;

    if(q==0)
    {
        _customFilter=0;
    }
    else
    {
        _customFilter=q->clone();
    }
    
     foreach (tagVec *value, _tags)
     {
         value->isDirty=true;
     }
}

bool views::tagSelector::hasDataPopulated(int type) const
{
    if(!_tags.contains(type))
    {
        return false;
    }
    
    return _tags[type]->isSelected;
}

QVariant views::tagSelector::icon()
{
    return QVariant(views::decor->tagIcon(type() ) );
}

views::tagSelector* views::tagSelector::itemAt(int type, int row)
{
    QVector<views::tagSelector*> *v=tags(type);

    if(v==0)
    {
        return 0;
    }

    if(row>=v->size() )
    {
        return 0;
    }

    return v->value(row);
}

void views::tagSelector::setNeedUpdate(int t)
{   
    if(!_tags.contains(t) )
    {
        return ;
    }
    
    if(_tags[t]->isSelected && !_tags[t]->isDirty)
    {
        _tags[t]->isDirty=true;
    }
    
    if(t==Basic::ARTIST ||t==Basic::LEAD_ARTIST)
    {
	if(_tags[Basic::ALBUM_ARTIST]->isSelected && !_tags[Basic::ALBUM_ARTIST]->isDirty)
	{
	    _tags[Basic::ALBUM_ARTIST]->isDirty=true;
	}
    }
}

void views::tagSelector::clear(int t)
{
    QVector<tagSelector*> *tagL=tags(t);
    if(tagL==0)
    {
        return ;
    }

    for(int i=0;i<tagL->size();i++)
    {
        tagSelector *t=tagL->value(i);
        delete t;
    }
    tagVec *v=_tags.take(t);
    delete v;
    
}

int views::tagSelector::columnCount() const
{
    return 1;
}

QVariant views::tagSelector::data(int column, int role) const
{
    if(column!=0)
    {
        return QVariant();
    }
    
    if(role==Qt::DisplayRole)
    {
        return views::pretyTag(_tag.data(),type() );
    }
    if(role==Qt::DecorationRole)
    {
        return decor->tagIcon(type());
    }
    return QVariant();
}

QVariant views::tagSelector::data(int t)
{
    return _tag.property(t);
}
