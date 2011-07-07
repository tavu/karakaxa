#ifndef AUDIOFILES
#define AUDIOFILES
// #include "fileCache.h"
#include<QVariant>
#include"tagsTable.h"
#include<QLinkedList>



// #include<player.h>
namespace audioFiles
{
 class 	fileTags;
 class  audioFile;
  
/*
WARNING
the enum MUST hold the fields in the exact order as in mysql's insert_track procedure

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
*/

enum errors
{
    OK=0		,
    NULL_FILE		,
    INVALID_FILE	,
    WRONG_FILETYPE	,
    NS_TAG		,
    EMPTY_RECORD	,
    TAGS_NOT_LOADED	,
    UNOWN		,
    NOTINDB		,
    DBERR		
};

extern const int BEST_COVER;



// const short FRAME_NUM =1 // COUNTER;
// const short TAGS_START=TRACK;
// const short TAGS_END=COUNTER;

struct _tagRecord
{
    QVariant 	value;
    int 	status;        
};
typedef struct _tagRecord tagRecord;

//an audio file list for many porposes
// #include"audioFile.h"
extern  QLinkedList<audioFile>	fileList;


fileTags* getFileTags(const QString path);

int coverMark(const QString &album, const QString &cover);

};

#include"fileTags.h"

#endif