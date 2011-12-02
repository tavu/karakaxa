#include"actionMenu.h"
#include"../core/core.h"
using namespace core;
views::actionMenu::actionMenu()
{
    repeatPlaylistA=0;
    clearPlaylistA = new QAction( KIcon("edit-clear-list"),tr("clear"), this );
    connect(clearPlaylistA,SIGNAL(triggered( bool)),npList,SLOT(clear() ) );

    sufflePlaylistA = new QAction( KIcon("roll"),tr("suffle"), this );    
    connect(sufflePlaylistA,SIGNAL(triggered( bool)),npList,SLOT(suffle() ) );   
}

QAction* views::actionMenu::repeatPlaylist()
{
    if(repeatPlaylistA==0 )
    {
        repeatPlaylistA = new QAction( tr("playlist-repeat"), this );
        connect(repeatPlaylistA,SIGNAL(triggered(bool)),npList,SLOT(repeatToggle()) );
        connect(npList,SIGNAL(repeatChanged(bool)),this,SLOT(repeatPlaylistSlot(bool)) );
        repeatPlaylistSlot(npList->repeat() );
    }
    return repeatPlaylistA;    
}

void views::actionMenu::repeatPlaylistSlot(bool repeat)
{
    if(repeat)
    {
        repeatPlaylistA->setToolTip(tr("repeat playlist") );
        repeatPlaylistA->setIcon(decor->icon("repeat-playlist") );
    }
    else
    {
        repeatPlaylistA->setToolTip(tr("stop at last track") );             
        repeatPlaylistA->setIcon(decor->icon("not-repeat-playlist") );
    }
}



namespace views
{
    actionMenu *menus;
};