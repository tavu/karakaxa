#include"contentTree.h"
#include<player.h>
#include<QContextMenuEvent>
using namespace player;

void contentTree::contextMenuEvent(QContextMenuEvent *e)
{
    QModelIndex i=indexAt(e->pos());
    abstractContent *a=contentHandlr.content(i);

    if (i.isValid() )
    {
        a->showMenu( e->globalPos() );
    }
}
