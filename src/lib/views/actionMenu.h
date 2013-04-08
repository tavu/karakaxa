#ifndef ACTIONMENU_H 
#define ACTIONMENU_H

#include"decoration/decoration.h"
#include<QAction>
#include <KToolBar>
#include<viewsFunc.h>
#include<engine/engine.h>
namespace views
{

class actionMenu :public QObject
{
    Q_OBJECT
    friend void cleanUp();
    public:

        QAction* clearPlaylist()
        {
            return clearPlaylistA;
        }

        QAction* sufflePlaylist()
        {
            return sufflePlaylistA;
        }

        QAction* next()
        {
            return nextA;
        }
        
        QAction* previous()
        {
            return previousA;
        }
        
        QAction* playPause()
        {
            return playPauseA;
        }

        QAction* volume()
        {
            return volumeAction;
        }
        QAction* quit()
        {
            return quitAction;
        }
        
        QAction* repeatPlaylist();
	
        static actionMenu* instance();
    private:
        QAction *clearPlaylistA;
        QAction *sufflePlaylistA;
        QAction *repeatPlaylistA;

        QAction *playPauseA;
        QAction *nextA;
        QAction *previousA;
        
        QAction *volumeAction;
        
        QAction *quitAction;
        
        static actionMenu *_instance;        
        actionMenu();
        
        
    private slots:
        void repeatPlaylistSlot(bool repeat);
        void stateChanged(Phonon::State state);
        void volumeC(qreal v);
};

inline actionMenu* menus()
{
    return actionMenu::instance();
}

};
#endif
