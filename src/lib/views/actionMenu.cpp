#include"actionMenu.h"
#include"../core/core.h"
using namespace core;
views::actionMenu::actionMenu()
{
    clearPlaylistA = new QAction( KIcon("edit-clear-list"),tr("clear"), this );
    connect(clearPlaylistA,SIGNAL(triggered( bool)),npList,SLOT(clear() ) );

    sufflePlaylistA = new QAction( KIcon("roll"),tr("suffle"), this );    
    connect(sufflePlaylistA,SIGNAL(triggered( bool)),npList,SLOT(suffle() ) );
}


namespace views
{
    actionMenu *menus;
};