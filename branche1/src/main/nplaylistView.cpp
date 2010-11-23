#include"nplaylistView.h"
#include<QApplication>

#include<player.h>
#include"nplaylistModel.h"
#include<QtAlgorithms>
#include <QItemSelection>

// #include<QList >
using namespace player;
#include<QSet>

nplaylistView::nplaylistView(QWidget *parent)
//      :QListView(parent)
        :QListView(parent)
{

    setDragDropMode( QAbstractItemView::DragDrop );
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    createMenu();

    setDropIndicatorShown(true);
    setDragEnabled( true );

    connect(this,SIGNAL(doubleClicked(QModelIndex ) ),this, SLOT(play(const QModelIndex) ) );
}

void nplaylistView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListView::mousePressEvent(event);
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
            QListView::mouseMoveEvent(event);
    }
    else
        QListView::mouseMoveEvent(event);
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

//      npList.clearReorder();
    QList<QUrl> urls;
    QList<int> rowL;

    for (int i=0;i<list.size();i++)
    {
        int r=list.at(i).row();
        rowL.append(r);

        urls.append(KUrl(npList.getTrack(r)->path())) ;
    }

    qSort(rowL.begin(), rowL.end());

    m->setReorder(rowL);

    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);


    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap("audio-x-generic") );

    drag->exec(Qt::MoveAction);
    QItemSelectionModel *sm=selectionModel();
    sm->clear();

    m->clearReorder();

    QItemSelection sel;

//      sel.select(npList.index(*rowL.begin()),npList.index(rowL.size()+ *rowL.begin()) );
//      m->select(sel,QItemSelectionModel::Select);
}

int nplaylistView::sizeHintForColumn(int column) const
{
    return -1;
}

void nplaylistView::createMenu()
{
    menu=new QMenu(this);

    removeAction=new QAction(tr("&Remove track"),this);
    connect(removeAction,SIGNAL(triggered( bool)),this,SLOT(remove() ) );
    menu->addAction(removeAction);

    duplicateAction=new QAction(tr("&Duplicate track"),this);
    connect(duplicateAction,SIGNAL(triggered( bool)),this,SLOT(duplicate() ) );
    menu->addAction(duplicateAction);

}

void nplaylistView::duplicate()
{
    QList<nplTrack*> l;
    QModelIndexList list=selectedIndexes();

    QModelIndexList::const_iterator it=list.begin();

    npList.duplicate( (*it).row());
}

void nplaylistView::remove()
{
    QList<nplTrack*> l;
    QModelIndexList list=selectedIndexes();

    QModelIndexList::const_iterator it=list.begin();

    QList<int> rowL;

    while (it!=list.end() )
    {
        rowL.append( (*it).row() );
        it++;

    }
    qSort(rowL.begin(), rowL.end());
    int n=0;

    QList<int>::const_iterator i=rowL.begin();
    while (i!=rowL.end() )
    {
        npList.remove(*i-n);
        i++;
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
// 	  npList.remove((*it).row());
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
        if (selectedIndexes().size()>1	  )
        {
            duplicateAction->setDisabled (true);
        }
        else
        {
            duplicateAction->setDisabled (false);
        }
        menu->popup( e->globalPos() );
    }
}
void nplaylistView::dragEnterEvent ( QDragEnterEvent * event )
{
    event->accept();
}

void nplaylistView::play(const QModelIndex &i)
{
    engine.play(i.row() );
}
