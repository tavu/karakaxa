#include"folderView.h"
#include<KIcon>
#include<QDebug>
#include <func.h>
#include<models/urlRole.h>

void folderView::dropEvent(QDropEvent* event)
{
#if 0
    if(model()==0 || !event->mimeData()->hasUrls())
    {
        return;
    }

    QModelIndex index=indexAt(event->pos() );
    int row=-1,column=-1;
    DropIndicatorPosition pos=dropIndicatorPosition ();
    switch (pos)
    {
        case QAbstractItemView::AboveItem:
        {
            row = index.row();
            column = index.column();
            index = index.parent();
            break;
        }
        case QAbstractItemView::BelowItem:
        {
            row = index.row() + 1;
            column = index.column();
            index = index.parent();
            break;
        }
        case QAbstractItemView::OnViewport:
        {
            index=QModelIndex();
            break;
        }
        case QAbstractItemView::OnItem:
        {
            break;
        }
    }    
    Qt::DropAction action;

    event->accept();
    views::treeView::dropEvent(event);

    if(core::isPlaylist(index.data(URL_ROLE).toString()) )
    {
        model()->dropMimeData(event->mimeData(),Qt::CopyAction,row,column,index);
        return ;
    }

    QMenu menu;
    QAction *copyA=new QAction(KIcon("edit-copy"),tr("Copy here"),&menu);
    QAction *moveA=new QAction(KIcon("go-jump"),tr("move here"),&menu);

    menu.addAction(copyA);
    menu.addAction(moveA);
    QAction *a=menu.exec(QCursor::pos());

    if(a==0)
    {
        return ;
    }
    else if(a==copyA)
    {

        action=Qt::CopyAction;
    }
    else
    {
        action=Qt::MoveAction;
    }

    model()->dropMimeData(event->mimeData(),action,row,column,index);
#endif
    treeView::dropEvent(event) ;
}

