#include"nplaylistView.h"
#include<QApplication>

// #include<player.h>
#include"nplaylistModel.h"
#include<QtAlgorithms>
#include <QItemSelection>
#include<core.h>
#include<views.h>

#include<set>
#define FONT_SIZE 10

#include<nplaylistDelegate.h>

nplaylistView::nplaylistView(QWidget *parent)
        :views::treeView(parent)
{
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setDragDropMode( QAbstractItemView::DragDrop );
    setDragDropOverwriteMode(false);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setUniformRowHeights(true);
//     setHeaderHidden(true);
    setDropIndicatorShown(true);
    setDragEnabled( true );

    _removeAction=new QAction(KIcon("list-remove"),tr("&Remove track"),this);
    connect(_removeAction,SIGNAL(triggered( bool)),this,SLOT(remove() ) );
    connect( engine ,SIGNAL(trackChanged ( QString) ),viewport(), SLOT(update()) );
    
    
}

void nplaylistView::mouseDoubleClickEvent(QMouseEvent* event)
{
//     views::treeView::mouseDoubleClickEvent(event);       
    QModelIndex index=indexAt (event->pos() );
    play(index);
    event->accept();
}

Qt::DropActions nplaylistView::supportedDropActions () const
{
    // returns what actions are supported when dropping
    return Qt::CopyAction | Qt::MoveAction;
}

QAction* nplaylistView::goToCurrent()
{
     QAction *action=new QAction(views::decor->icon("show-playing-track"),tr("show playing track"),this);
     connect(action,SIGNAL(triggered(bool)),this,SLOT(goToCurrentTrack()) );
     return action;
}

void nplaylistView::goToCurrentTrack()
{
    int pos=core::npList->getPlayingPos();
    QModelIndex index=model()->index(pos,0,QModelIndex());
    scrollTo(index,QAbstractItemView::PositionAtCenter);
}



int nplaylistView::sizeHintForColumn(int column) const
{
    Q_UNUSED(column);
    return -1;
}

QMenu* nplaylistView::createMenu()
{
    QMenu *menu=new QMenu(this);
    QPalette pal=views::decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    menu->setPalette(pal);        
    
    menu->addAction(_removeAction);

    duplicateAction=new QAction(tr("&Duplicate track"),this);
    connect(duplicateAction,SIGNAL(triggered( bool)),this,SLOT(duplicate() ) );
    menu->addAction(duplicateAction);
    
    return menu;
}

void nplaylistView::duplicate()
{
    nplList l;
    QModelIndexList list=selectedIndexes();
    qSort(list.begin(), list.end());

    foreach(QModelIndex index,list)
    {
	   if(index.column()==0 )
	   {
		  nplPointer p=npList->getTrack(index.row());
		  l<<nplPointer(p->clone() );
	   }
    }

    npList->insert(l,list.last().row()+1);
}

void nplaylistView::remove()
{
    QList<nplTrack*> l;
    QModelIndexList list=selectedIndexes();
    set<int> rowL;

    for(int i=0;i<list.size();i++)
    {
        rowL.insert(list.at(i).row() );
    }
    int n=0;
    
    set<int>::iterator it;
    for(it=rowL.begin();it!=rowL.end();it++)
    {
        npList->remove(*it-n);
        n++;
    }
}

void nplaylistView::contextMenuEvent(QContextMenuEvent *e)
{
    if (indexAt(e->pos()).isValid() )
    {
	   QMenu *menu=new QMenu(this);	
	   QPalette pal=views::decor->palette();	
	   pal.setColor(QPalette::Base,pal.color(QPalette::Window) );	
	   menu->setPalette(pal);        	      
		
	   menu->addAction(_removeAction);	    

	   duplicateAction=new QAction(views::decor->icon("duplicate4"),tr("&Duplicate track"),this);
	   connect(duplicateAction,SIGNAL(triggered( bool)),this,SLOT(duplicate() ) );	    	 
	   menu->addAction(duplicateAction);
	 
	   QMenu *m=new QMenu(tr("More"),menu );

	   m->setPalette(menu->palette());
	   menu->addMenu(m);
	   
	   QModelIndexList list=selectedIndexes();
	   QList<QUrl>urls=views::treeView::getUrls(list);
	   
	   core::contentHdl->contextMenu(m,currentIndex().data(URL_ROLE).toUrl(),urls);
		  
	   menu->exec( e->globalPos() );
	   delete menu;
    }
}


void nplaylistView::play(const QModelIndex &index)
{
	if(index.isValid() )
	{
	   engine->play(index.row() );
	}
}

