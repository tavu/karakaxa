#ifndef TAGS_TABLE_H
#define TAGS_TABLE_H

namespace Basic
{

enum tagsEnum
{
    TRACK=0         ,
    TITLE           ,
    ALBUM           ,
    ARTIST          ,
    LEAD_ARTIST     ,
    COMMENT         ,
    GENRE           ,
    COMPOSER        ,
    LENGTH          ,
    RATING          ,
    YEAR            ,
    BITRATE         ,
    PATH            ,
    COUNTER         ,
    
    //non visible types
    ID,
    ALBUM_ID,
    ALBUM_ARTIST,
    FILES,
    INVALID,
    IMAGE,
    ARTIST_IMAGE,
    LYRICS,
    ALBUM_ARTIST_ID,
};

const int FRAME_NUM=COUNTER+1;



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
    NOT_SELECTED ,
    NULL_ID,
    NOT_UNIQUE_ENTRIES,
    INVALID_RELATION
};

};//namespace



#define TAGS_START TRACK
#define TAGS_END   COUNTER
#endif
