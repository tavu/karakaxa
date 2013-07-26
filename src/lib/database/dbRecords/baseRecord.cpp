#include"baseRecord.h"

#include <QMap>
#include<QVariant>
#include<QSqlQuery>
#include<QDebug>
#include<Basic/tagsTable.h>
#include<QSqlRecord>

database::dbPrivate::baseRecord::baseRecord(QString t)
    :abstractRecord(), entry(),
    _isSelected(false),
    _table(t),
    _hasChanged(false),
    _needNewId(false)
{
#ifdef DEBUG
    if(table().isEmpty())
    {
        qDebug()<<"no table have been set";
    }
#endif

    _unique=false;
}

/************ implementation of entry *****************/

QString database::dbPrivate::baseRecord::sqlType() const
{
    return QString("int(10)");
}


QVariant database::dbPrivate::baseRecord::value() const
{
    return id();
}

//it is not possible to have knowledge of the new id since the id is assigned from the database automatically
void database::dbPrivate::baseRecord::changeValue ( QVariant& v )
{
    v.clear();
}

QVariant database::dbPrivate::baseRecord::newValue() const
{
    if(!_newId.isNull() )
    {
        return _newId;
    }
    
    return id();
}

int database::dbPrivate::baseRecord::saveValue ()
{
    if(!_newId.isNull() )
    {
        _id=_newId;
        _needNewId=false;
        _newId=QVariant();
    }      
    _hasChanged=false;
    return Basic::OK;
}

bool database::dbPrivate::baseRecord::hasChanged() const
{
    //return if the id has changed not any other field
    return _needNewId;
}

void database::dbPrivate::baseRecord::setValue(QVariant v)
{
    setId(v);
}

void database::dbPrivate::baseRecord::clearData()
{
    clearId();
    _hasChanged=false;
    _needNewId=false;
    _newId=QVariant();
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        it.value()->clearData();        
    }
}

void database::dbPrivate::baseRecord::clearNewValue()
{
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        it.value()->clearNewValue();
    } 
    _hasChanged=false;
    _needNewId=false;
}

/**************** BASE RECORD ***************/

bool database::dbPrivate::baseRecord::isRelated ( int i)
{
    return getRelated(i)!=0;
}

database::dbPrivate::baseRecord* database::dbPrivate::baseRecord::getRelated(int t) const
{
    if(!hasEntry(t) )
    {
        return 0;
    }
    
    return getRelatedEntry(entries[t] );
}

database::dbPrivate::baseRecord* database::dbPrivate::baseRecord::getRelatedEntry (entry *e )
{
    return dynamic_cast<baseRecord*>(e);
}

void database::dbPrivate::baseRecord::addEntry ( int i, database::dbPrivate::entry *e)
{    
    entries.insert(i,e); 
}

void database::dbPrivate::baseRecord::setValue(int i, QVariant v)
{
    if(!hasEntry(i))
    {
        v=QVariant();
        return ;
    }
    entries[i]->setValue(v);
}

void database::dbPrivate::baseRecord::changeEntry ( int i, QVariant& v )
{
    if(!hasEntry(i))
    {
        v=QVariant();
        return ;
    }
    
    entry *e=entries[i];
    e->changeValue(v);
    _hasChanged=true;
    if(e->isUnique())
    {
        _needNewId=true;
    }
}

QVariant database::dbPrivate::baseRecord::getValue(int i) const
{
    if(!hasEntry(i))
    {
        return QVariant();
        
    }
    return entries[i]->value();
}

bool database::dbPrivate::baseRecord::hasEntry(int i) const
{
    return entries.contains(i);
}


QVariant database::dbPrivate::baseRecord::id() const
{
    return _id;
}

void database::dbPrivate::baseRecord::setId(QVariant v)
{
    _id=v;
}

int database::dbPrivate::baseRecord::doUpdate()
{    
    clearError();
    
    QString queryS="UPDATE "+table()+" SET ";
    bool hasChanges=false;
    
    for(constEntryIter i=entries.constBegin();i!=entries.constEnd();i++)
    {
        entry *e=i.value();
        if( e->hasChanged() )
        {
            hasChanges=true;
            queryS.append(e->name() + "= ?," );
        }
    }
    if(!hasChanges)
    {
        qDebug()<<"no changes have been made";
        return Basic::OK;
    }

    //remove last ","
    queryS.remove(queryS.size()-1,1);
    queryS.append(" where id=?");

#ifdef QUERY_DEBUG
    qDebug()<<"query "<<queryS;
#endif
    QSqlQuery q(databs);
    q.prepare(queryS);

    for(entryIter i=entries.begin();i!=entries.end();i++)
    {
        entry *e=i.value();
        if(e->hasChanged() )
        {
            q.addBindValue( e->newValue() );
        }
    }

    q.addBindValue(_id);
    if(!q.exec())
    {
        clearNewValue();
        setError( q.lastError() );
        return Basic::DBERR;
    }
//     saveDataLocaly();
    
    return Basic::OK;
}

int database::dbPrivate::baseRecord::insert()
{
    saveAllRelated();
    int ret=doInsert();
    saveValue();
    return ret;
}

int database::dbPrivate::baseRecord::doInsert()
{
    clearError();
    saveDataLocaly();
    
    QString values("VALUES (");
    QString queryS="INSERT INTO "+table()+" (";
    QMap<QString, QVariant>::const_iterator i;

    for(constEntryIter i= entries.constBegin(); i!=entries.constEnd(); i++)
    {
        const entry *e=i.value();
        queryS.append(e->name()+",");
        values.append("?,");
    }
    
    //remove last ","
    queryS.remove(queryS.size()-1,1);
    values.remove(values.size()-1,1);
    
    queryS.append(") "+values +")");    
#ifdef QUERY_DEBUG
    qDebug()<<"query "<<queryS;
#endif
    QSqlQuery q(databs);
    q.prepare(queryS);

    for(constEntryIter i= entries.constBegin(); i!=entries.constEnd(); i++)
    {     
        const entry *e=i.value();
        q.addBindValue( e->value() );        
    }

    if(!q.exec())
    {
        setError(q.lastError() );
        return Basic::DBERR;
    }

    _newId=q.lastInsertId();
    return Basic::OK;
}

int database::dbPrivate::baseRecord::selectAll()
{
    int error;
    if(!isSelected() )
    {
        int error=select();
        if(error!=Basic::OK)
        {
            return error;
        }
    }
    
    for(entryIter it=entries.begin(); it!=entries.end(); it++)
    {
        baseRecord *b=getRelatedEntry(it.value() );
        if(b!=0)
        {
            
            error =b->selectAll();
            if(error!=Basic::OK)
            {
                setError("some related selection return with an error");
                return error;
            }
        }
    }
    return Basic::OK;
}


int database::dbPrivate::baseRecord::select()
{
    int ret;
    if(_id.isValid() )
    {
        ret=selectFromId();
    }
    else
    {
        saveAllRelated();
        ret = selectFromUnique();
    }
    saveValue();
    return ret;
}

int database::dbPrivate::baseRecord::selectFromId()
{    
    clearNewValue();
    clearError();
    QString queryS=selectStr();
    queryS.append(" WHERE id=?");
#ifdef QUERY_DEBUG
    qDebug()<<"SELECT "<<queryS;
#endif
    QSqlQuery q(databs);
    q.prepare(queryS);
    q.addBindValue(_id);
    int ret= execSelect(q);
//     saveValue();
    return ret;
}

int database::dbPrivate::baseRecord::selectFromUnique()
{
    clearError();
    
//     saveDataLocaly();
    QString queryS=selectStr();
    queryS.append(" WHERE ");
    
    entryIter i=nextUnique(entries.begin() );
    if(i==entries.end() )
    {
        setError("No unigue entries");
        return Basic::DBERR;
    }
    
    for(entryIter i=entries.begin();i!=entries.end();i++)
    {        
        entry *e=i.value();
        if(e->isUnique() )
        {
            queryS.append(e->name()+"=? AND ");
        }
    }
    //remove last AND
    queryS.resize(queryS.size()-5);
    
#ifdef QUERY_DEBUG
    qDebug()<<"SELECT "<<queryS;
#endif    
    QSqlQuery q(databs);
    q.prepare(queryS);
    
    for(constEntryIter i=entries.constBegin();i!=entries.constEnd();i++)
    {
        const entry *e=i.value();
        if(e->isUnique() )
        {
            q.addBindValue(e->chosenValue() );
        }
    }
    
    return execSelect(q);
}

int database::dbPrivate::baseRecord::execSelect(QSqlQuery &q)
{
    if(!q.exec() )
    {
        qDebug()<<"can't exec";
        setError(q.lastError() );
        return Basic::DBERR;
    }
    
    if(q.size()>1)
    {
        setError("More than one rows returned after selection");
        return Basic::DBERR;
    }
    
    if(!q.next() )
    {
        qDebug()<<"not in db";
        return Basic::NOTINDB;
    }
    
    QSqlRecord rec=q.record();
    _newId=rec.value(0);
    int i=1;
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        QVariant v=rec.value(i);
        entry *e=it.value();
        
        if(e->value()!=v)
        {
            e->clearData();
            e->setValue(v);
        }
        i++;
    }
    _isSelected=true;
    return Basic::OK;
}

QString database::dbPrivate::baseRecord::selectStr()
{
    QString queryS("SELECT id");
    for(constEntryIter i= entries.constBegin(); i!=entries.constEnd(); i++)
    {        
        QString s=i.value()->name();
        if(s.isEmpty() )
        {
            setError("Unkown entry name");
            return QString();
        }
        queryS.append(","+s);
    }
    
    queryS.append(" FROM "+table());
    return queryS;
}

int database::dbPrivate::baseRecord::save()
{
    int ret=doSave();
    saveDataLocaly();
    saveValue();
    return ret;
}


int database::dbPrivate::baseRecord::doSave()
{
    int err=saveAllRelated();
    if(err!=Basic::OK)
    {
        setError("some related enties couldn't save its value");
        return err;
    }

    if(_hasChanged )
    {
        if(_id.isNull() || _needNewId )
        {
            int err=selectFromUnique();
            if(err==Basic::NOTINDB)
            {
                err=doInsert();
                return err;
            }
        }
        else
        {
            return doUpdate();
        }
    }
    
    return Basic::OK;
}


void database::dbPrivate::baseRecord::saveDataLocaly()
{
    for(entryIter i= entries.begin(); i!=entries.end(); i++)
    {
        i.value()->saveValue();
    }
}

void database::dbPrivate::baseRecord::setDatabase(QSqlDatabase &d)
{
    databs=d;
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        baseRecord *b=getRelatedEntry(it.value());
        if(b!=0)
        {
            b->setDatabase(d);
        }
    }
}


database::dbPrivate::baseRecord::~baseRecord()
{
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        delete it.value();
    }
    
    entries.clear();
}

void database::dbPrivate::baseRecord::clearId()
{
    _id=QVariant();
}

database::dbPrivate::baseRecord::entryIter database::dbPrivate::baseRecord::nextUnique ( database::dbPrivate::baseRecord::entryIter it )
{
    if(it==entries.end() )
    {
        return it;
    }
        
    while(it!=entries.end() )
    {
        if(it.value()->isUnique() )
        {
            return it;
        }
        it++;
    }
    return it;
}

int database::dbPrivate::baseRecord::saveAllRelated()
{
    int ret=Basic::OK;
    for(entryIter it=entries.begin();it!=entries.end();it++)
    {
        baseRecord *b=getRelatedEntry(it.value());
        if(b!=0)
        {
            ret=b->doSave();
            if(ret!=Basic::OK)
            {
                return ret;
            }
            
            if( b->hasChanged() )
            {
                _hasChanged=true;
                if(b->isUnique() )
                {
                    _needNewId=true;
                }
            }
        }
    }
    return ret;
}

bool database::dbPrivate::baseRecord::isSelected() const
{
    return _isSelected;
}

void database::dbPrivate::baseRecord::setSelected ( bool b )
{
    _isSelected=b;
}

QSqlError database::dbPrivate::baseRecord::lastError()
{
    return _lastError;
}

QString database::dbPrivate::baseRecord::lastErrorStr()
{
    return _lastError.text();
}

void database::dbPrivate::baseRecord::clearError()
{
    _lastError=QSqlError ();
}

void database::dbPrivate::baseRecord::setError ( QString s )
{
              QSqlError r(s,QString(),QSqlError::UnknownError);    
            setError(r);
}

void database::dbPrivate::baseRecord::setError ( QSqlError r )
{
    _lastError=r;
    //qDebug<<_lastError.text();
}


void database::dbPrivate::baseRecord::setTable ( QString s )
{
    _table=s;
}

QString database::dbPrivate::baseRecord::table() const
{
    return _table;
}


