#ifndef ACTIONMENU_H 
#define ACTIONMENU_H

#include"decoration/decoration.h"
#include<QAction>

namespace views
{

class actionMenu :public QObject
{
    Q_OBJECT
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

        QAction* repeatPlaylist();
	
    private:
        QAction *clearPlaylistA;
        QAction *sufflePlaylistA;
        QAction *repeatPlaylistA;

        QAction *playPauseA;
        QAction *nextA;
        QAction *previousA;

    private slots:
        void repeatPlaylistSlot(bool repeat);
};

extern actionMenu *menus;
};
#endif
