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
	
//         void init();
        
//         static actionMenu* instance();
        
    private:        
        QAction *clearPlaylistA;
        QAction *sufflePlaylistA;
        QAction *repeatPlaylistA;

        QAction *playPauseA;
        QAction *nextA;
        QAction *previousA;
        
//         static void clear();
//         static actionMenu* _instance;
        
    private slots:
        void repeatPlaylistSlot(bool repeat);
};

extern actionMenu *menus;
};
#endif
