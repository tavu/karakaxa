#include"albumRecord.h"
#include<Basic/tagsTable.h>
#include"albumRecord.h"
#include"artistRecord.h"
#include"columnEntry.h"
database::dbPrivate::albumRecord::albumRecord() :baseRecord(QString("albums") )
{
    entry *name=new columnEntry("name","varchar(255)");
    name->setUnique(true);
    addEntry(0,name);    
    
    entry *image=new columnEntry("image","varchar(255)");    
    image->setName("image");
    addEntry(Basic::IMAGE,image);
        
    entry *artist=new artistRecord();
    artist->setUnique(true);
    artist->setName("artist");
    addEntry(Basic::ALBUM_ARTIST,artist );
}

int database::dbPrivate::albumRecord::type() const
{
    return Basic::ALBUM;
}
