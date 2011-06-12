#include"nplaylistView.h"
#include<QApplication>

// #include<player.h>
#include"nplaylistModel.h"
#include<QtAlgorithms>
#include <QItemSelection>
#include<core.h>
#include<views.h>

// #include<QList >
// using namespace player;
#include<set>

nplaylistView::nplaylistView(QWidget *parent)
//      :QListView(parent)
        :QTreeView(parent)
{
    setRootIsDecorated(false);
//     setHeaderHidden(true);
  
    setDragDropMode( QAbstractItemView::DragDrop );
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setDropIndicatorShown(true);
    setDragEnabled( true );

    connect(this,SIGNAL(doubleClicked(QModelIndex ) ),this, SLOT(play(const QModelIndex) ) );
}

void nplaylistView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QTreeView::mousePressEvent(event);
}

void nplaylistView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            performDrag();
        }
        else
            QTreeView::mouseMoveEvent(event);
    }
    else
        QTreeView::mouseMoveEvent(event);
}

Qt::DropActions nplaylistView::supportedDropActions () const
{
    // returns what actions are supported when dropping
    return Qt::CopyAction | Qt::MoveAction;
}

void nplaylistView::performDrag()
{

    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    nplModel *m=static_cast<nplModel *>(model());

//      npList->clearReorder();
    QList<QUrl> urls;
    set<int> rowL;

    for (int i=0;i<list.size();i++)
    {
        int r=list.at(i).row();
        rowL.insert(r);

        urls.append(KUrl(npList->getTrack(r)->path())) ;
    }

    m->setReorder(rowL);

    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);


    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(views::decor->tagIcon(-1).pixmap(48,48) );

    drag->exec(Qt::MoveAction);
//      QItemSelectionModel *sm=selectionModel();
//     sm->clear();
    selectionModel()->clear();
    
    m->clearReorder();

//     QItemSelection sel;

//      sel.select(npList->index(*rowL.begin()),npList->index(rowL.size()+ *rowL.begin()) );
//      m->select(sel,QItemSelectionModel::Select);
}

int nplaylistView::sizeHintForColumn(int column) const
{
    return -1;
}

QMenu* nplaylistView::createMenu()
{
    QMenu *menu=new QMenu(this);
    QPalette pal=views::decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    menu->setPalette(pal);        
    
    removeAction=new QAction(tr("&Remove track"),this);
    connect(removeAction,SIGNAL(triggered( bool)),this,SLOT(remove() ) );
    menu->addAction(removeAction);

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
//     qDebug()<<"S "<<list.size();

    foreach(QModelIndex index,list)
    {
	if(index.column()==0 )
	{
	    nplPointer p=npList->getTrack(index.row());
	    l<<nplPointer(p->clone() );
	}
    }

    npList->insert(l,list.last().row()+1 );

//     npList->duplicate( (*it).row());
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


void nplaylistView::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_A)
    {
        selectAll();
    }
//      QListView::keyPressEvent(event);
}


// void nplaylistView::remove()
// {
//
//      QModelIndexList list=selectedIndexes();
//
//      QModelIndexList::const_iterator it=list.begin();
//
//
//      while(it!=list.end() )
//      {
// // 	  int r=
// 	  npList->remove((*it).row());
// // 	  l<<t;
// 	  it++;
//
//      }
//      qDebug()<<"nplView re";
//
// }
void nplaylistView::contextMenuEvent(QContextMenuEvent *e)
{
    if (indexAt(e->pos()).isValid() )
    {
	QMenu *menu=new QMenu(this);	
	QPalette pal=views::decor->palette();	
	pal.setColor(QPalette::Base,pal.color(QPalette::Window) );	
	menu->setPalette(pal);        	      
	    
	removeAction=new QAction(tr("&Remove track"),this);	
	connect(removeAction,SIGNAL(triggered( bool)),this,SLOT(remove() ) );	
	menu->addAction(removeAction);	    
		
//         if (selectedIndexes().size()==1)
        {
	    duplicateAction=new QAction(tr("&Duplicate track"),this);	    
	    connect(duplicateAction,SIGNAL(triggered( bool)),this,SLOT(duplicate() ) );	    
	    menu->addAction(duplicateAction);
        }
	
	QMenu *m=new QMenu(tr("More"),menu );
	m->setPalette(menu->palette());
	menu->addMenu(m);
	core::contentHdl->contextMenu(m,currentIndex().data(URL_ROLE).toUrl(),!selectedIndexes().isEmpty());
	
        menu->exec( e->globalPos() );
	delete menu;
    }
}
void nplaylistView::dragEnterEvent ( QDragEnterEvent * event )
{
    event->accept();
}

void nplaylistView::play(const QModelIndex &i)
{
    core::engine->play(i.row() );
}
