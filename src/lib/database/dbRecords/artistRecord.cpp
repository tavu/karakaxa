#include"artistRecord.h"
#include <Basic/tagsTable.h>
#include "columnEntry.h"

database::dbPrivate::artistRecord::artistRecord() :baseRecord(QString("artists"))
{
    entry *name=new columnEntry("name","varchar(255)");
    name->setUnique(true);
    addEntry(0,name);
    
    entry *image=new columnEntry("image","varchar(255)");    
    addEntry(Basic::IMAGE,image);
}

int database::dbPrivate::artistRecord::type() const
{
    return Basic::ARTIST;
}

