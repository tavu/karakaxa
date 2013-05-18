#ifndef AUDIOFILESFUNC_H
#define AUDIOFILESFUNC_H
// #include "fileCache.h"
#include<QVariant>
#include<QLinkedList>



// #include<player.h>
namespace audioFiles
{

class audioFile;
class fileTags;

extern const int BEST_COVER;

struct _tagRecord
{
    QVariant    value;
    int     status;
};
typedef struct _tagRecord tagRecord;

//an audio file list for many porposes
// #include"audioFile.h"
extern  QLinkedList<audioFile>  fileList;


fileTags* getFileTags(const QString path);

int coverMark(const QString &album, const QString &cover);

int bestCover( const QLinkedList< QString > &covers, QString album, QString& cover);


};


#endif 
