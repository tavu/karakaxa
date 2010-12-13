#include"myTreeView.h"
#include<QAction>

#include<QHeaderView>

#include<KIcon>

#include"treeViewHeader.h"
#include"trackUrl.h"
#include<QDebug>

#define test qDebug()<<"TEEEST";
#include<KApplication>

// class editTrack;
myTreeView::myTreeView(QWidget *parent,QString name)
        :QTreeView(parent)
{
//      header =new treeViewHeader(this);
    setHeader(new treeViewHeader(this));
    setUniformRowHeights(true);
    
    delegate=new treeViewDelegate(this);
    setItemDelegate(delegate);



    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setDragEnabled(true);
    setDragDropMode( QAbstractItemView::DragOnly );
    setRootIsDecorated(false);
    setSortingEnabled (true);

    if (!name.isEmpty() )
    {
        setObjectName(name);
        readSettings();
    }

    connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(writeSettings() ) );


}

void myTreeView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPos = event->pos();
    }
    else if(event->button() == Qt::RightButton)
    {
	
    }


    QTreeView::mousePressEvent(event);
}

void myTreeView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            performDrag();
            //after the drag u gen no mouse released event due to a bug
            //i  create that event manualy
            QMouseEvent *e=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(-1,-1),Qt::NoButton,Qt::LeftButton,Qt::NoModifier);
            mouseReleaseEvent (e);
        }
        else
        {
            QTreeView::mouseMoveEvent(event);
        }
    }
    else
        QTreeView::mouseMoveEvent(event);
}

void myTreeView::performDrag()
{

    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    const trackUrl *model=dynamic_cast<const trackUrl*>(list.at(0).model() );

    if (model==0)
    {
        return ;
    }

    QList<QUrl> urls;
    qSort(list.begin(), list.end());
    QModelIndexList::const_iterator it=list.begin();

    while (it!=list.end() )
    {
        int r=(*it).row();
        urls.append(model->url(it->row())  );

        while ( it!=list.end() && (*it).row()==r )
        {
            it++;
        }

    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap("audio-x-generic") );

    drag->exec(Qt::CopyAction);
}

void myTreeView::setModel ( QAbstractItemModel * model )
{
    QTreeView::setModel(model);
}


void myTreeView::fileEdit()
{
    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    const trackUrl *model=dynamic_cast<const trackUrl*>(list.at(0).model() );
    if (model==0)
    {
        return ;
    }

//      editTrack *t=new editTrack(model->path(list.at(0) ) ,this);
//      player::contentHandlr->addWidget(t);

//      treeViewHeader *h=static_cast<treeViewHeader*>(header());
    foreach(QModelIndex i,list)
    {
        if (i.column()==0)
        {
            player::editTrack(model->url(i.row()).toLocalFile() );
        }
    }
}

void myTreeView::setRatingColumn(const int n)
{    
//     header()->setResizeMode ( n, QHeaderView::Fixed );
//     header()->resizeSection(n,delegate->itemHeigh()*5+1 );
    delegate->setRatingColumn(n);
}

int myTreeView::ratingColumn() const
{
    return delegate->ratingColumn();
}

void myTreeView::writeSettings()
{

    if (objectName().isEmpty() )
    {
        return ;
    }
    QSettings settings;

    settings.beginGroup(objectName());
    settings.setValue("state", QVariant(header()->saveState()) );
    settings.endGroup();
}

void myTreeView::readSettings()
{
    QSettings settings;
    settings.beginGroup(objectName());
    header()->restoreState(settings.value("state").toByteArray());
    settings.endGroup();
}

void myTreeView::setNotHide(int n)
{
    treeViewHeader *h=dynamic_cast<treeViewHeader*>(header() );

    if (h!=0)
    {
        h->setNotHide(n);
    }
}

int myTreeView::notHide()
{
    treeViewHeader *h=dynamic_cast<treeViewHeader*>(header() );

    if (h!=0)
    {
        return h->notHide();
    }
    return -2;
}
