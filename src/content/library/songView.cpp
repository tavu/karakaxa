#include"songView.h"
#include"songModel.h"
#include <nplaylist.h>

class editTrack;
songView::songView(QWidget *parent,QString name)
        :myTreeView(parent,name)
// 	stars(0)
{
    createMenu();
    connect(this,SIGNAL(doubleClicked  ( const QModelIndex) ),this,SLOT(play(const QModelIndex) ) );
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

    trackUrl *Model=dynamic_cast<trackUrl*>(model() );

    if(Model==0)
    {
	qDebug()<<"ah bah";
	return ;
    }
    
    foreach(QModelIndex i,list)
    {
        if (i.column()==TITLE)
        {
	    KUrl u=Model->url(i.row());
	    if(!u.isEmpty() )
	    {
		qDebug()<<"bah ah";
		player::editTrack(u.toLocalFile() );
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

    nplList list;
    for (int i=0;i<model()->rowCount();i++)
    {
	  QModelIndex index=model()->index(i,0);
         list<<nplTrack::getNplTrack(model()->data(index,URL_ROLE).toUrl() );
    }
    npList.clear();
    npList.insertSlot(list,0);
    
    engine.play(index.row() );
}


