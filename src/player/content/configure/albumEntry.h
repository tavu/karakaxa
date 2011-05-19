#ifndef ALBUM_ENTRY_H
#define ALBUM_ENTRY_H
#include<QString>
	
struct _albumEntry
{
    QString 	album;
    QString 	artist;
    int 	id;
    int 	val;
};
typedef struct _albumEntry albumEntry;
	
#endif