#ifndef TAGSTABLE_H
#define TAGSTABLE_H

#include<QString>
#include<QStringList>
#include<QVariant>

/*
WARNING
the enum MUST hold the fields in the exact order as in mysql's insert_track procedure
*/
namespace audioFiles
{

enum tagsEnum
{
    TRACK=0	,
    TITLE	,
    ALBUM	,
    ARTIST	,
    LEAD_ARTIST	,
    COMMENT	,
    GENRE	,
    COMPOSER	,
    LENGTH	,
    RATING	,
    YEAR	,
    BITRATE	,
    PATH	,
    COUNTER
};
};//namespace

#define FRAME_NUM COUNTER+1

#define TAGS_START TRACK
#define TAGS_END   COUNTER
#endif
