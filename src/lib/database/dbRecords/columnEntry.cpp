#include"columnEntry.h"
#include <Basic/tagsTable.h>
#include<QDebug>
database::dbPrivate::columnEntry::columnEntry ( QString name, QString sqlType, bool unique ):entry()
{
    _name=name;
    _sqlType=sqlType;
    _unique=unique;
    _hasChanged=false;
    _valluChangesAllowed=true;
}

void database::dbPrivate::columnEntry::setValue(QVariant v)
{
    _value=v;
}

    
QVariant database::dbPrivate::columnEntry::value() const
{
    return _value;
}


void database::dbPrivate::columnEntry::changeValue(QVariant &v)
{
    if(_valluChangesAllowed)
    {
        if(v.isNull())
        {
            v=QVariant(QString(""));
        }
        else if(sqlType().startsWith("varchar")  )
        {
            QString s=v.toString();
            s=s.simplified();
            v=QVariant(s);
        }   
    }
    
    if(v!=_value)
    {
        _newValue=v;
        _hasChanged=true;
    }
    else
    {
        clearNewValue();
    }
}

bool database::dbPrivate::columnEntry::hasChanged() const
{
    return _hasChanged;
}


QVariant database::dbPrivate::columnEntry::newValue() const
{
    return _newValue;
}

int database::dbPrivate::columnEntry::saveValue()
{
    if(_hasChanged)
    {
        _value=_newValue;
    }
    _hasChanged=false;
    return Basic::OK;
}

QString database::dbPrivate::columnEntry::sqlType() const
{
    return _sqlType;
}

void database::dbPrivate::columnEntry::clearNewValue()
{
    _newValue.clear();
    _hasChanged=false;
}

void database::dbPrivate::columnEntry::clearData()
{
    clearNewValue();
    _value=QVariant();
}


