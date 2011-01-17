#ifndef  PLAYER_NAMESPACE_H
#define  PLAYER_NAMESPACE_H

#include<QString>
#include<QPalette>
#include"files/tagsTable.h"
#include"nowPlayList/nplClass.h"
namespace player
{


class database;
class playerIcon;
//      class errorStatus;
class soundEngine;
class nowPlaylist;
class contentHandler;
class PlayerConfigure;
class coverWidget;
class nplaylist;

class audioFile;
class tagsTable;
class m3up;
class pStatusBar;
class decoration;
class starWidget;
//      class myPointer;


extern database 		db;
extern nplaylist 		npList;
extern soundEngine 		engine;
extern contentHandler 		*contentHandlr;
extern PlayerConfigure 		config;

extern QPalette			pal;
extern pStatusBar		statusBar;
extern decoration 		decor;


QString 	folder(QString path) ;
QString 	titleFromPath(const QString &path);
QString 	prettyLength(int l);
QString 	prettySize(int n);
QString		tagName(player::tagsEnum t);
int     	tagSize(player::tagsEnum t);
bool   		isStream(const QString s);
bool   		isStream(const QUrl url);
bool 		isDirectory(const QString &url);
bool		isPlaylist(const QString &url);
bool 		isAudio(const QString &url);

QString 	format(QString path);

void 		editTrack(const QString &s);
};


#endif
