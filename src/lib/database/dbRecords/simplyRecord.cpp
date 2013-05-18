#include"simplyRecord.h"
#include "columnEntry.h"


#include<Basic/tagsTable.h>

database::dbPrivate::simpleRecord::simpleRecord(int t) :baseRecord(tableFromType(t)),_type(t)
{
    entry *name=new columnEntry("name","varchar(255)",true);
    addEntry(0,name);
}


int database::dbPrivate::simpleRecord::type() const
{
    return _type;
}

QString database::dbPrivate::simpleRecord::tableFromType(int t)
{
    using namespace Basic;
    switch (t)
    {
        case COMPOSER:
        {
            return QString("composers");
        }
        case GENRE:
        {
            return QString("genres" );
        }
        case COMMENT:
        {
            return QString("comment");
        }
        default:
        {
            return QString();
        }
    }
}
