#include"contentTree.h"
#include<player.h>
#include<QContextMenuEvent>
using namespace player;

contentTree::contentTree(QWidget *parent) 
    :QTreeWidget(parent)
{
//     setRootIsDecorated(false);
//   this->setStyleSheet("QTreeView::branch:open:has-children:has-siblings { border-image: none ;image: url(branch-open.png);" );
 }
void contentTree::contextMenuEvent(QContextMenuEvent *e)
{
    QModelIndex i=indexAt(e->pos());
    abstractContent *a=contentHandlr.content(i);
        
    if (a!=0 )
    {
        a->showMenu( e->globalPos() );
    }
}

void contentTree::drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const
{
//     QModelIndex c=index.child(0,0);
    if(index.model()->hasChildren(index) )
    {
	QPointF points[3];
	if(isExpanded(index) )
	{
	    QPixmap p("branch-open.png");
	    QRect r=rect;
	    r.setSize(p.size() );
// 	    painter->drawPixmap(r,p);
	}
	else
	{

// 	    painter->drawPolygon(points,3);
	}
      
  	QTreeWidget::drawBranches(painter,rect,index ) ;
    }
//     QTreeWidget::drawBranches(painter,rect,index ) ;
}