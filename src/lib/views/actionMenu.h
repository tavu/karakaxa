#ifndef ACTIONMENU_H 
#define ACTIONMENU_H

#include"decoration/decoration.h"
#include<QAction>

namespace views
{

class actionMenu :public QObject
{
    public:
	actionMenu();
	
	QAction* clearPlaylist()
	{
	    return clearPlaylistA;
	}
	
	QAction* sufflePlaylist()
	{
	    return sufflePlaylistA;
	}
	
	QAction* nextSong()
	{
	    return nextA;
	}	
	
	
    private:
	QAction *clearPlaylistA;
	QAction *sufflePlaylistA;
	
	QAction *playPauseA;
	QAction *nextA;
	QAction *previousA;
};

extern actionMenu *menus;
};
#endif
