#include"myTreeView.h"
#include<QAction>

#include<QHeaderView>
#include<audioFiles.h>
#include<KIcon>

#include"treeViewHeader.h"
// #include"trackUrl.h"
#include"../playerNamespace/files/audioFiles.h"
#include<QDebug>

#define test qDebug()<<"TEEEST";
#include<KApplication>
#include<QSettings>
#include<player.h>

// class editTrack;
myTreeView::myTreeView(QWidget *parent,QString name)
        :QTreeView(parent)
{    
//      header =new treeViewHeader(this);
    setFrameShape(QFrame::NoFrame);
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
    setMouseTracking(true);
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
            //after the drag we get no mouse released event due to a bug
            //we  create that event manualy
            QMouseEvent *e=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(-1,-1),Qt::NoButton,Qt::LeftButton,Qt::NoModifier);
            mouseReleaseEvent (e);
        }
        else
        {
	    headerRepaint();
            QTreeView::mouseMoveEvent(event);
        }
    }
    else
    {
	headerRepaint();
        QTreeView::mouseMoveEvent(event);
    }
}

void myTreeView::performDrag()
{
    QModelIndexList list=selectedIndexes();
    
    if (list.isEmpty() )	return;
    
    QList<QUrl> urls;
    qSort(list.begin(), list.end());
    QModelIndexList::const_iterator it=list.begin();

    while (it!=list.end() )
    {
	int r=(*it).row();
	QUrl u=it->data(URL_ROLE).toUrl();
	if(u.isValid() )
	{
	    urls.append(u);
	}

        while ( it!=list.end() && (*it).row()==r )
        {
            it++;
        }

    }
    
    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(decor.tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction);
}

void myTreeView::setModel ( QAbstractItemModel * model )
{
    QTreeView::setModel(model);   
    if(delegate->ratingColumn()>-1)
    {
	connect(model,SIGNAL(rowsInserted ( const QModelIndex, int, int )),this ,SLOT(updateStarWidget(QModelIndex, int, int) ) );
    }
}


void myTreeView::fileEdit()
{
  /*
    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    trackUrl *mod=dynamic_cast<trackUrl*>(model() );
    if (mod==0)
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
            player::editTrack(mod->url(i.row()).toLocalFile() );
        }
    }
    */
  
    QModelIndex index=currentIndex();
    QUrl u=index.data(URL_ROLE).toUrl();
    
    if(u.isValid())
    {
	player::editTrack(u.toLocalFile() );
    }  
}

void myTreeView::contextMenuEvent(QContextMenuEvent *e)
{
    emit(showContextMenu(indexAt(e->pos()) ) ); 
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
        
    KSharedConfigPtr config=player::config.configFile();
    KConfigGroup group( config, objectName() );
    group.writeEntry( "state", QVariant(header()->saveState() ));
    group.config()->sync(); 
    
    
}

void myTreeView::readSettings()
{
    KSharedConfigPtr config=player::config.configFile();
    KConfigGroup group( config, objectName() );
    header()->restoreState(group.readEntry( "state", QByteArray() ) );
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

void myTreeView::updateStarWidget(QModelIndex parent, int start, int end)
{    
    for(int i=start;i<=end;i++)
    {
	QModelIndex item=model()->index(i,ratingColumn(),parent );
	bool b;
	item.data().toInt(&b);
	
	if(b)
	{
	    openPersistentEditor(item);
	}
    }
}



void myTreeView::commitData ( QWidget * editor ) 
{
  qDebug()<<"editttt";
  
  
//     trackUrl *m=dynamic_cast<trackUrl*>(model());
//     
//     if(m!=0)
//     {
// 	QModelIndexList list=selectedIndexes();
// 
// 	if (!list.isEmpty() )
// 	{
// 	    foreach(QModelIndex i,list)
// 	    {
// 		if (i.column()==list.at(0).column() )
// 		{
// 		    m->urlList<<m->url(i.row());
// 		}
// 	    }
// 	}
//     }
//     QTreeView::commitData(editor);
   
    audioFiles::fileList.clear();
    QModelIndexList list=selectedIndexes();
    if (!list.isEmpty() )	
    {
	foreach(QModelIndex i,list)	
	{	
	    if (i.column()==list.at(0).column() )	
	    {	
		QUrl u=i.data(URL_ROLE).toUrl();
		if(u.isValid() )
		{
		    audioFile f(u.toLocalFile());
		    audioFiles::fileList.append(f);
		}
	    }
	}
    }
    
    QTreeView::commitData(editor);
}


void myTreeView::closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint )
{
    qDebug()<<"closing editor";
    audioFiles::fileList.clear();
    QTreeView::closeEditor(editor,hint);   
}

void myTreeView::headerRepaint()
{
    QModelIndex index=indexAt( viewport()->mapFromGlobal(QCursor::pos() )  );
    
    int mouseColumn=index.column();
    
    if(mouseColumn!=header()->property("highlight") )
    {      	
	mouseColumn=index.column();
	header()->setProperty("highlight",QVariant(mouseColumn) );
	QWidget * viewport = header()->viewport();
	viewport->update();
    }   
}

void myTreeView::leaveEvent (QEvent *) 
{
//       Q_UNUSED(event);
  
     QWidget * viewport = header()->viewport();
     header()->setProperty("highlight",QVariant(-1) );
     viewport->update();
}