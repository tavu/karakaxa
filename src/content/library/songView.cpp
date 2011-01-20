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

    const songModel *model=static_cast<const songModel*>(list.at(0).model() );

    foreach(QModelIndex i,list)
    {
        if (i.column()==TITLE)
        {
            player::editTrack(model->url(i.row()).toLocalFile() );
        }
    }
}

void songView::play(const QModelIndex index)
{
    const trackUrl *Model=dynamic_cast<const trackUrl*>(model() );
    
    if(Model==0)
    {
	return;
    }    
    npList.clear();

    nplList list;
    for (int i=0;i<model()->rowCount();i++)
    {
         list<<nplTrack::getNplTrack(Model->url(i).toLocalFile());
    }
    npList.insertSlot(list,0);
    
    engine.play(index.row() );
}


