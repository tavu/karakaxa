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
#include <decoration/decoration.h>
#include<QMetaProperty>
// class editTrack;
 #include <QToolTip>
#include<QModelIndexList>
#include <QPainter>
Q_DECLARE_METATYPE(QModelIndexList)

views::treeView::~treeView()
{
    writeSettings();
}

views::treeView::treeView(QWidget *parent,QString name)
        :QTreeView(parent),_ratingColumn(-1),_playOnDoubleCl(true)
{
    setHeader(new treeViewHeader(this));
    setUniformRowHeights(true);
    setAlternatingRowColors(true);

    delegate=new treeViewDelegate(this);
    setItemDelegate(delegate);

    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setDragEnabled(true);
    setDragDropMode( QAbstractItemView::DragDrop );
    setRootIsDecorated(false);
    setSortingEnabled (true);

    setMouseTracking(true);

    if (!name.isEmpty() )
    {
        setObjectName(name);
        readSettings();
    }
    setEditTriggers(QAbstractItemView::SelectedClicked);
}

void views::treeView::rowsInserted(const QModelIndex& parent, int start, int end)
{
    QTreeView::rowsInserted(parent, start, end);

    if(ratingColumn()>-1)
        updateStarWidget(parent,start,end);

}

void views::treeView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QTreeView::mouseDoubleClickEvent(event);
    QModelIndex index=indexAt (event->pos() );

    if(_playOnDoubleCl)
        play(index);   
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
//	    QTreeView::mouseMoveEvent(event);
	    event->accept();
            performDrag();
//	    event->accept();
        }
        else
        {
            headerRepaint();
        }
    }
    else
    {
        headerRepaint();
    }
    event->accept();
}

void views::treeView::reset()
{
    QTreeView::reset();
    if(ratingColumn()>-1 )
        updateStarWidget();
}


void views::treeView::performDrag()
{
    QModelIndexList list=selectedIndexes();

    QList<QUrl> urls=getUrls(list);

    if(urls.isEmpty() )
    {
        return ;
    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(decor->tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction|Qt::MoveAction);

    if(reorderL.size() == 0)
    {
        return ;
    }

    QItemSelection sel;
    std::set<int>::const_iterator it=reorderL.begin();
    for(;it!=reorderL.end();it++)
    {
        QItemSelection s;
        s.select(model ()->index (*it, 0),model ()->index (*it, model()->columnCount()-1));
        sel.merge(s,QItemSelectionModel::SelectCurrent);
    }
//     selectionModel()->select (sel,QItemSelectionModel::Select );

    reorderL.clear();
}

void views::treeView::setModel ( QAbstractItemModel * model )
{
    QTreeView::setModel(model);
}



void views::treeView::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
     QTreeView::dataChanged(topLeft,bottomRight);
     if(ratingColumn()>-1)
     {
         updateStarWidget(topLeft.parent(),topLeft.row(),bottomRight.row());

     }
}

void views::treeView::contextMenuEvent(QContextMenuEvent *e)
{
    emit showContextMenu(indexAt(e->pos() ),selectedIndexes() );
}


void views::treeView::setRatingColumn(const int n)
{
    _ratingColumn=n;
}

int views::treeView::ratingColumn() const
{
    return _ratingColumn;
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
    if(model()==0)
    {
        return ;
    }
    updateStarWidget(QModelIndex(),0,model()->rowCount() );
}


void views::treeView::commitData ( QWidget * editor )
{
    QModelIndexList list=selectedIndexes();

    QVariant var=QVariant::fromValue<QModelIndexList>(list);
    itemDelegate()->setProperty("modelList",var );
    QTreeView::commitData(editor);
    return ;
}


void views::treeView::closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint )
{
    QTreeView::closeEditor(editor,hint);
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

void views::treeView::play(const QModelIndex &index)
{
    //return if item is disabled
    if( !(index.flags() & Qt::ItemIsEnabled) || index.data(DISABLE_ROLE).toBool() )
    {
        return ;
    }

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

    core::npList()->clear();
    core::npList()->insert(0,list);

    if(list.size() != model()->rowCount(index.parent() ) )
    {
        core::status->addError(tr("Some media could not be inserted to playlist") );
    }

    core::engine()->play(row );
}

QList<QUrl> views::treeView::getUrls(const QModelIndexList &list)
{
    QList<QUrl> urls;

    if(list.isEmpty() )
    {
	   return urls;
    }

    int k=list.at(0).column();

    foreach(QModelIndex index,list)
    {
	   if(index.column()==k)
	   {
          reorderL.insert(index.row() );
		  QUrl u=index.data(URL_ROLE).toUrl();

		  if(u.isValid() )
		  {
			 urls.append(u);
		  }
	   }
    }

    return urls;
}

void views::treeView::paintEvent(QPaintEvent * event)
{
    QPainter painter(viewport());
    drawTree(&painter, event->region());

    if(state() ==QAbstractItemView::DraggingState && showDropIndicator() )
    {
        DropIndicatorPosition pos=dropIndicatorPosition ();

        if(pos==AboveItem)
        {
            QModelIndex in=indexAt( viewport()->mapFromGlobal(QCursor::pos() )  );
            QRect rect=visualRect(in);
            rect.setX(viewport()->rect().x() );
            rect.setWidth(viewport()->rect().width());

            QPen pen(palette().highlight().color() );
            pen.setWidth(3);
            painter.setPen(pen);

            painter.drawLine(rect.topLeft(),rect.topRight());
        }
        else if(pos==BelowItem)
        {
            QModelIndex in=indexAt( viewport()->mapFromGlobal(QCursor::pos() )  );
            QRect rect=visualRect(in);
            rect.setX(viewport()->rect().x() );
            rect.setWidth(viewport()->rect().width());

            QPen pen(palette().highlight().color() );
            pen.setWidth(3);
            painter.setPen(pen);

            painter.drawLine(rect.bottomLeft(),rect.bottomRight());
        }
        else if(pos==OnViewport)
        {
            if(model()==0)
                return ;

            QModelIndex in=model()->index(model()->rowCount()-1,notHide(),QModelIndex()  );
            while(indexBelow(in).isValid() )
            {
                in=indexBelow(in);
            }
            QRect rect=visualRect(in);
            rect.setX(viewport()->rect().x() );
            rect.setWidth(viewport()->rect().width());

            QPen pen(palette().highlight().color() );
            pen.setWidth(3);
            painter.setPen(pen);


            painter.drawLine(rect.bottomLeft(),rect.bottomRight());
        }
        else if(pos==OnItem)
        {
            QModelIndex in=indexAt( viewport()->mapFromGlobal(QCursor::pos() )  );
            QRect rect=visualRect(in);

            QPen pen(palette().highlight().color() );
            pen.setWidth(2);
            painter.setPen(pen);


            painter.drawRect(rect);
        }

    }
}

Qt::DropActions views::treeView::supportedDropActions () const
{
    // returns what actions are supported when dropping
    return Qt::CopyAction | Qt::MoveAction;
}

void views::treeView::dropEvent(QDropEvent* event)
{
    if(event->source()!=this)
    {
        reorderL.clear();
    }
    QAbstractItemView::dropEvent(event);
}

std::set<int> views::reorderL;
