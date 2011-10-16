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
    setAcceptDrops(true);
    setDragDropMode( QAbstractItemView::DragDrop );
    
     timer = new QTimer(this);
	timer->setSingleShot(true);
     connect(timer, SIGNAL(timeout()), this, SLOT(dropTime()) );
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

void contentTree::dragMoveEvent(QDragMoveEvent* event)
{    
    QModelIndex index=indexAt( viewport()->mapFromGlobal(QCursor::pos() )  );
    if(dropIndex!=index)
    {
	   timer->stop();
 	   dropIndex=index;	   
	   if(index.isValid() )
	   {
		timer->start(500);
	   }	   
	   
    }    
    
    QTreeView::dragMoveEvent(event);
}

Qt::DropActions contentTree::supportedDropActions () const
{
    // returns what actions are supported when dropping
    return Qt::CopyAction | Qt::MoveAction;
}

void contentTree::dragEnterEvent ( QDragEnterEvent * event )
{
    event->accept();
    return ;
    QTreeView::dragEnterEvent(event);
}

void contentTree::dragLeaveEvent ( QDragLeaveEvent* event )
{
	   timer->stop();
        QTreeView::dragLeaveEvent ( event );
}


void contentTree::dropTime()
{
//     if(dropIndex.isValid() )	   
    {
	 expand(dropIndex);
// 	 abstractContent* content=core::contentHdl->content(dropIndex);
	 core::contentHdl->itemChanger(dropIndex);
    }
}
