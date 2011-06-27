#include"contentTree.h"
#include<core.h>
#include<QContextMenuEvent>
using namespace core;

contentTree::contentTree(QWidget *parent) 
    :QTreeView(parent)
{ 
    setAnimated(true);    
    QString s(" QTreeView { icon-size: 20px; } QTreeView::item { height: 25px; }");
    setStyleSheet(s);
    setRootIsDecorated(true);
    setExpandsOnDoubleClick(false);
 }
void contentTree::contextMenuEvent(QContextMenuEvent *e)
{
    QModelIndex i=indexAt(e->pos());
    abstractContent *c=contentHdl->content(i);           
    if (c!=0 )
    {
        c->showMenu( e->globalPos() );
    }
}

void contentTree::drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const
{
    QTreeView::drawBranches(painter,rect,index ) ;
}