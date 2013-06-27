#include"songView.h"

class editTrack;
songView::songView(QWidget *parent,QString name)
        :treeView(parent,name)
{
    createMenu();
}

void songView::contextMenuEvent(QContextMenuEvent *e)
{
    if (indexAt(e->pos()).isValid() )
    {
        menu->popup( e->globalPos() );
    }
}

inline void songView::createMenu()
{
    appendAction=new QAction(tr("&Queue track"),this);
    editAction=new QAction(tr("Edit"),this);
    editTrAction=new QAction(tr("&Edit track details"),this);
    deletAction=new QAction(tr("&Delete"),this);

    menu=new QMenu(this);
    menu->addAction(appendAction);
    menu->addAction(editAction);
    menu->addAction(deletAction);
    menu->addSeparator();
    menu->addAction(editTrAction);

    connect(editTrAction,SIGNAL(triggered()),this,SLOT(fileEdit() ) );
    connect(editAction,SIGNAL(triggered()),this,SLOT(openEditor() ) );
}

void songView::openEditor()
{
//     QModelIndexList list=selectedIndexes();
          
    QModelIndex i=currentIndex();    
    edit(i);
}

void songView::fileEdit()
{
    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    
    foreach(QModelIndex i,list)
    {
        if (i.column()==Basic::TITLE)
        {
	    QUrl u=model()->data(i,URL_ROLE).toUrl();
	    if(!u.isEmpty() )
	    {
// 		qDebug()<<"bah ah";
// 		::editTrack(u.toLocalFile() );
	    }
        }
    }
}

void songView::play(const QModelIndex index)
{
//     const trackUrl *Model=dynamic_cast<const trackUrl*>(model() );
    
/*    if(Model==0)
    {
	return;
    }*/     

    core::nplList list;
    for (int i=0;i<model()->rowCount();i++)
    {
        QModelIndex index=model()->index(i,0);
         list<<core::nplTrack::getNplTrack(model()->data(index,URL_ROLE).toUrl() );
    }
    core::npList()->clear();
    core::npList()->insert(0,list);
    
    core::engine()->play(index.row() );
}


