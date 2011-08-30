#include"treeView.h"
#include<QAction>

#include<QHeaderView>
#include<KIcon>
#include<kconfiggroup.h>
#include"treeViewHeader.h"
#include<QDebug>
#include"../../core/core.h"
#include"../decoration/decoration.h"
#include"treeViewDelegate.h"
#include"urlRole.h"
#include <decoration.h>
// class editTrack;

#include<QModelIndexList>
Q_DECLARE_METATYPE(QModelIndexList)


views::treeView::treeView(QWidget *parent,QString name)
        :QTreeView(parent)
{
//     setFrameShape(QFrame::NoFrame);
    setHeader(new treeViewHeader(this));
    setUniformRowHeights(true);
    setAlternatingRowColors(true);
      
    delegate=new treeViewDelegate(this);
    setItemDelegate(delegate);

    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setDragEnabled(true);
    setDragDropMode( QAbstractItemView::DragOnly );
    setRootIsDecorated(false);
    setSortingEnabled (true);
    
    setMouseTracking(true);

    if (!name.isEmpty() )
    {
        setObjectName(name);
        readSettings();
	   connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(writeSettings() ) ); 
    }
    setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(this,SIGNAL(doubleClicked  ( const QModelIndex) ),this,SLOT(play(const QModelIndex) ) );    

//     setStyleSheet("QTreeView::item { height: 40px; }");
}

void views::treeView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPos = event->pos();
    }

    QTreeView::mousePressEvent(event);
}

void views::treeView::mouseMoveEvent(QMouseEvent *event)
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

void views::treeView::performDrag()
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
    
    if(urls.isEmpty() )
    {
	return ;
    }
    
    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(decor->tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction);
}

void views::treeView::setModel ( QAbstractItemModel * model )
{
    QAbstractItemModel *m=QTreeView::model();
    QTreeView::setModel(model); 
    if(m!=0)
    {
	   disconnect(m, 0, this, 0);
    }
    
    if(delegate->ratingColumn()>-1)
    {
	connect(model,SIGNAL(rowsInserted ( const QModelIndex, int, int )),this ,SLOT(updateStarWidget(QModelIndex, int, int) ) );
 	connect(model,SIGNAL(modelReset () ),this ,SLOT(updateStarWidget() ) );
//  	connect(model,SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex& ) ),this,SLOT(dataChanged ( const QModelIndex &, const QModelIndex& ) ) );
    }
}

void views::treeView::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
//     qDebug()<<"ET";
     QTreeView::dataChanged(topLeft,bottomRight);
     return ;
     if(bottomRight.column()>ratingColumn() )
     {
	   for(int i=topLeft.row();i<=bottomRight.row();i++)
	   {
		  
		  QModelIndex item=model()->index(i,ratingColumn(),topLeft.parent() );
		  bool b;
		  item.data().toInt(&b);
	   
		  if(b)
		  {
		    openPersistentEditor(item);
		  }
	   }
     }
  
}

void views::treeView::contextMenuEvent(QContextMenuEvent *e)
{
    emit showContextMenu(indexAt(e->pos() ),selectedIndexes() ); 
}


void views::treeView::setRatingColumn(const int n)
{    
//     header()->setResizeMode ( n, QHeaderView::Fixed );
//     header()->resizeSection(n,delegate->itemHeigh()*5+1 );
    delegate->setRatingColumn(n);
}

int views::treeView::ratingColumn() const
{
    return delegate->ratingColumn();
}

void views::treeView::writeSettings()
{

    if (objectName().isEmpty() )
    {
        return ;
    }
        
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, objectName() );
    group.writeEntry( "state", QVariant(header()->saveState() ));
    group.config()->sync(); 
    
    
}

void views::treeView::readSettings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, objectName() );    
//     byteArr=group.readEntry( "state", QByteArray() );
    header()->restoreState(group.readEntry( "state", QByteArray() ) );
}

void views::treeView::setNotHide(int n)
{
    treeViewHeader *h=dynamic_cast<treeViewHeader*>(header() );

    if (h!=0)
    {
        h->setNotHide(n);
    }
}

int views::treeView::notHide()
{
    treeViewHeader *h=dynamic_cast<treeViewHeader*>(header() );

    if (h!=0)
    {
        return h->notHide();
    }
    return -2;
}

void views::treeView::updateStarWidget(QModelIndex parent, int start, int end)
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

void views::treeView::updateStarWidget()
{
    updateStarWidget(QModelIndex(),0,model()->rowCount() );
}


void views::treeView::commitData ( QWidget * editor ) 
{    

    qDebug()<<"commit";
    QModelIndexList list=selectedIndexes();
    QModelIndexList l;
    
    if (!list.isEmpty() )
    { 	
 	   int column=currentIndex().column();
 	   foreach(QModelIndex i,list)
 	   {
 		  if (i.column()==column )	
 		  {
 		    l<<i;
 		  }
 	   }
    }
        
    QVariant var=QVariant::fromValue(l);
    itemDelegate()->setProperty("modelList",var );  

    
    QTreeView::commitData(editor);
}


void views::treeView::closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint )
{
    qDebug()<<"closing editor";
    QTreeView::closeEditor(editor,hint);                
//     viewport()->update();
}

void views::treeView::headerRepaint()
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

void views::treeView::leaveEvent (QEvent *) 
{ 
     QWidget * viewport = header()->viewport();
     header()->setProperty("highlight",QVariant(-1) );
     viewport->update();
}

void views::treeView::play(const QModelIndex index)
{
    core::nplList list;
    int row=index.row();
    for (int i=0;i<model()->rowCount(index.parent() );i++)
    {
	 QModelIndex in=model()->index(i,0,index.parent() );
	 if(in.isValid() )
	 {
	    QUrl u=in.data(URL_ROLE).toUrl();
	    core::nplPointer t=core::nplTrack::getNplTrack(u);
	    if(!t.isNull() && t->isValid() )
	    {
		  list<<t;
	    }
	    else if(in.row()<index.row() )
	    {
		  row--;
	    }
	 }
    }
    
    core::npList->clear();
    core::npList->insert(list,0);
    
    if(list.size() != model()->rowCount(index.parent() ) )
    {
	core::status->addError(tr("Some media could not be inserted to playlist") );
    }
    
    core::engine->play(row );
}

