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
    TRACK=0		    ,
    TITLE			,
    ALBUM			,
    ARTIST		    ,
    LEAD_ARTIST	    ,
    COMMENT		    ,
    GENRE			,
    COMPOSER		,
    LENGTH		    ,
    RATING		    ,
    YEAR			,
    BITRATE		    ,
    PATH			,
    COUNTER
};

const int FRAME_NUM=COUNTER+1;
//we set a number to values below different from the tagsEnum numbers
const int ALBUM_ID=FRAME_NUM;
const int ALBUM_ARTIST=FRAME_NUM+1;
const int FILES=FRAME_NUM+2;
const int INVALID=FRAME_NUM+3;




struct changes
{
  int       tag;
  QVariant  value;
  int       error;
};
typedef struct changes tagChanges;
typedef QList<tagChanges> tagChangesL;

enum errors
{
    OK=0            ,
    NULL_FILE       ,
    INVALID_FILE    ,
    WRONG_FILETYPE  ,
    NS_TAG          ,
    EMPTY_RECORD    ,
    TAGS_NOT_LOADED ,
    UNOWN       ,
    NOTINDB     ,
    DBERR,
    NOT_SELECTED
};

};//namespace



#define TAGS_START TRACK
#define TAGS_END   COUNTER
#endif
