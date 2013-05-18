#include"records.h"
#include<QSqlRecord>
#include<QVariant>
database::trackRecord* database::fileRecordFromSql(const QSqlRecord& r)
{
    if(r.isEmpty())
    {
        return 0;
    }
    
    
    
    
        trackRecord *ret=new trackRecord();
    ret->artistId=r.value(0).toInt();
    ret->albumId=r.value(1).toInt();
    ret->number=r.value(2).toInt();
    ret->title=r.value(3).toString();
    ret->album=r.value(4).toString();
    ret->artist=r.value(5).toString();
    ret->leadArtist=r.value(6).toString();
    ret->comment=r.value(7).toString();
    ret->genre=r.value(8).toString();
    ret->composer=r.value(9).toString();
    ret->lenght=r.value(10).toInt();
    ret->rating=r.value(11).toInt();
    ret->year=r.value(12).toInt();
    ret->bitrate=r.value(13).toInt();
    ret->path=r.value(14).toString();
    ret->count=r.value(15).toInt();    
    
}
