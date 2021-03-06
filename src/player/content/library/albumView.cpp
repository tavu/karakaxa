#include"albumView.h"
#include <Basic/tagsTable.h>
#include<QScrollBar>
#include<QPainter>
#include<QDebug>
#include<QPaintEvent>
#include <QHeaderView>
#include"albumDelegate.h"
#include<QApplication>
#include<views/models/treeView.h>
#include<views/decoration/decoration.h>
#include<views/models/urlRole.h>
#include<core/nowPlayList/nplaylist.h>
#include<core/engine/engine.h>



#include<views/models/urlRole.h>

#define DECOR_SIZE QSize(80,80)
#define HEADER_OFFSET albumOffset + albumWidth

albumView::albumView(QString name,QWidget* parent): QAbstractItemView(parent)
{
    rowHeight=20;
    albumOffset=20;
    albumWidth=80;
    albumMinHeight=100;
    albumInfoHeight=40;
    space=10;
    
    hashIsDirty=false;
    setMouseTracking(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    header=new albumViewHeader(viewport() );
    header->setVisible(false);
//     QRect r=viewportRectForRow(headerRect(-1));
    
    readSettings();
    columnResizeTimer.setInterval(500);
    columnResizeTimer.setSingleShot(true);
//     header->setGeometry(r);
//     header->move(r.topLeft());
//     header->setFixedHeight(r.height());
//     header->move(r.topLeft());
    header->setNotHide(Basic::TITLE);

    header->setMovable(true);
    header->setClickable(true);
    header->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    setEditTriggers(QAbstractItemView::SelectedClicked);
    
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragDropMode(QAbstractItemView::DragOnly);
    verticalScrollBar()->setSingleStep(rowHeight);
    horizontalScrollBar()->setSingleStep(500);
    
    setItemDelegate(new albumDelegate(this) );
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
    setAutoFillBackground(true);
    verticalScrollBar()->setPageStep(rowHeight*10);
    horizontalScrollBar()->setPageStep(500);
    
    connect(horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(hideHeader()) );
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(hideHeader()) );
    
    connect(header,SIGNAL(geometriesChanged()),this,SLOT(columnsUpdated()) );
    connect(header,SIGNAL(sectionResized(int,int,int)),this,SLOT(columnResized(int)) );
    connect(header,SIGNAL(sectionMoved(int,int,int)),this,SLOT(columnsUpdated()) );
    connect(header,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this,SLOT(sortModel(int,Qt::SortOrder)));
    
    connect(&columnResizeTimer,SIGNAL(timeout()),this,SLOT(columnsUpdated()) );
    connect(this,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(doubleClickedSlot(const QModelIndex&)));
    
    setObjectName(name);    
}

albumView::~albumView()
{
    writeSettings();
}


void albumView::setModel(QAbstractItemModel* m)
{
    if(model()!=0)
    {
        disconnect(model());        
        _headerState=header->saveState();
    }
    else
    {
        readSettings();
    }
        
    hashIsDirty=true;
    QAbstractItemView::setModel(m);
    connect(m,SIGNAL(modelReset() ),this,SLOT(resetSlot()) );
    connect(m,SIGNAL(layoutAboutToBeChanged()),this,SLOT(resetSlot()) );
    
    header->setModel(m);         
    header->restoreState(_headerState);
//     header->setResizeMode()
    header->stretchSectionCount();
    
    QRect r=viewportRectForRow(headerRect(-1));
    header->setGeometry(r);
    header->setStretchLastSection(false);
    
    columnsUpdated();
    
    if(m->canFetchMore(QModelIndex() ))
    {
        m->fetchMore(QModelIndex());
    }
    
    for(int row=0;row<m->rowCount();row++)
    {
        QModelIndex in=m->index(row,0);
        if(isExpanded(in))
        {
            m->fetchMore(in);
        }
    }
    
}


int albumView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

int albumView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

QModelIndex albumView::indexAt(const QPoint& _point) const
{
    if(model()==0)
        return QModelIndex();
    
    QPoint point(_point);
//     int pos=point.rx();
    point.rx() += horizontalScrollBar()->value();
    point.ry() += verticalScrollBar()->value();
    
    
    QRect rect;
    QHashIterator<int, QRect> i(albumRects);
    while (i.hasNext()) 
    {    
        i.next();        
        if (i.value().contains(point))
        {   
            rect=i.value();
            break;
        }
    }
        
    if(rect.isNull())
    {
        return QModelIndex(); 
    }    
    
    rect=itemsRect(i.key());
    QModelIndex parent=model()->index(i.key(),0);

    if(!rect.contains(point))
    {
        rect=albumRect(parent);
        if(rect.contains(point) )
        {
            return parent;
        }
        return QModelIndex();
        
    }
    
    int height=point.ry() -rect.topLeft().ry()  ;
    int itemRow=height/rowHeight ;
 
    QPoint p=header->mapFromParent(_point);
//     QPoint p=header->mapFrom(viewport(),point);
    int k=header->logicalIndexAt(p);

    return model()->index(itemRow,k,parent);
}

bool albumView::isIndexHidden(const QModelIndex& index) const
{
    if(index.parent().isValid() )
    {        
        if(!isExpanded(index.parent() ) )
        {
            return true;
        }
    }
    
    return false;
}

QModelIndex albumView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex index = currentIndex();
    
    return index;
    
}

void albumView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
    return ;
#if 0
    QRect viewRect = viewport()->rect();
    QRect itemRect = visualRect(index);

    if (itemRect.left() < viewRect.left())
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()
                + itemRect.left() - viewRect.left());
    else if (itemRect.right() > viewRect.right())
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()
                + qMin(itemRect.right() - viewRect.right(),
                       itemRect.left() - viewRect.left()));
    if (itemRect.top() < viewRect.top())
        verticalScrollBar()->setValue(verticalScrollBar()->value() +
                itemRect.top() - viewRect.top());
    else if (itemRect.bottom() > viewRect.bottom())
        verticalScrollBar()->setValue(verticalScrollBar()->value() +
                qMin(itemRect.bottom() - viewRect.bottom(),
                     itemRect.top() - viewRect.top()));
    viewport()->update();
    
#endif
}

void albumView::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags)
{
    if (flags & QItemSelectionModel::Clear)
            selectionModel()->clear();

    if(model()==0)
        return ;

    calculateRectsIfNecessary();
    QPoint tl(qMin(rect.left(), rect.right()), qMin(rect.top(), rect.bottom()));
    QPoint br(qMax(rect.left(), rect.right()), qMax(rect.top(), rect.bottom()));   
    
    QModelIndex topLeft = indexAt(tl);
    QModelIndex bottomRight = indexAt(br);
    
    if(topLeft.parent()!=bottomRight.parent())
        return ;
    
    
//     if (!topLeft.isValid() || !bottomRight.isValid()) 
//         return;
    /*   
    if(isAlbum(topLeft) && !isExpanded(topLeft) )
    {
        return ;
    }*/
    
    QItemSelection selection(topLeft,bottomRight);
    selectionModel()->select(selection, flags);
    viewport()->update();
    return ; 
}


QRegion albumView::visualRegionForSelection(const QItemSelection& selection) const
{
    QRegion region;    
    QModelIndexList l=selection.indexes();
    foreach(QModelIndex index,l)
    {
        region+=visualRect(index);
    }
    return region;
}


void albumView::calculateRectsIfNecessary() const
{
    if (!hashIsDirty)
        return;
    
    if(model()==0)
        return ;
    
    int prevHeight = -10;
    for (int row = 0; row < model()->rowCount(); ++row) 
    {        
        int height=0;
        QModelIndex index=model()->index(row,0);
        if(expanded.contains(index.data(ID_ROLE).toInt()))
        {            
            int rowCount=model()->rowCount(index);            
            height=(rowCount+2)*rowHeight +albumInfoHeight;//one extra row for the header
        
            if(height<albumMinHeight)
            {
                height=albumMinHeight;
            }
        }
        else
        {
            height=albumMinHeight;
        }
        QRect albumR;        
        
        //albuR is bellow the previous album
        albumR.setX(0);
        albumR.setY(prevHeight +albumOffset  );
        
        albumR.setWidth(qMax(viewport()->width(),header->length()+HEADER_OFFSET ) );        
        albumR.setHeight(height);
        albumRects[row]=albumR;
        prevHeight=albumR.y()+albumR.height();
    }
    
    verticalScrollBar()->setRange(0, qMax(0, prevHeight -viewport()->height() ) );
//     horizontalScrollBar()->setRange(0, width());
//     updateScrollBars();
    
    hashIsDirty=false;
    viewport()->update();
}

QRect albumView::indexRect(const QModelIndex& index) const
{
    QRect r;
    
    if (!index.isValid())
        return r;
    
        
    if(isIndexHidden(index))
        return r;
    
    calculateRectsIfNecessary();
    
    if(isAlbum(index))
    {
        r=albumRect(index);
    }
    else
    {
        r=itemRect(index);
    }
    
    return r;
}

QRect albumView::visualRect(const QModelIndex& index) const
{
    return viewportRectForRow(indexRect(index) );   
}


QRect albumView::viewportRectForRow(QRect rect) const
{        
    if (!rect.isValid())
        return rect;
    
    return QRect(rect.x() - horizontalScrollBar()->value(),
                  rect.y() - verticalScrollBar()->value(),
                  rect.width(), rect.height());
}

QRect albumView::itemsRect(int parentRow) const
{
    QModelIndex parentIndex=model()->index(parentRow,0);  
    if(!isExpanded(parentIndex))
        return QRect();
    
    QRect r(albumRects[parentRow] );
    r.setX(r.x() + albumOffset+albumWidth);
    r.setY(r.y()+albumInfoHeight + rowHeight);
    return r;
}

QRect albumView::headerRect(int row) const
{    
//     qDebug()<<"W "<<header->width();
    if(row==-1)
    {
        QRect r;
        r.setX(r.x()+HEADER_OFFSET);
        r.setY(albumInfoHeight );
        r.setHeight(rowHeight);
//         r.setWidth(r.width());
//         r.setWidth(albumOffset + albumWidth+r.width());
//         r.setWidth(header->sizeHint().width());
        return r;
    }
    
    QModelIndex parentIndex=model()->index(row,0);  
    if(!isExpanded(parentIndex))
        return QRect();

    
    QRect r(albumRects[row] );
    r.setX(r.x() + albumOffset + albumWidth);
    r.setY(r.y()+albumInfoHeight );
    r.setHeight(rowHeight);
//     r.setWidth(r.width());
//     r.setWidth(albumOffset + albumWidth+r.width());
//     r.setWidth(header->sizeHint().width());
//     r.setWidth(header->sizeHint().width());
    return r;
}


QRect albumView::itemRect(const QModelIndex& index) const
{
    /*
    QRect r=itemsRect(index.parent().row() );

    int width=header->sectionSize(index.column());
    r.setY(r.y()+index.row()*rowHeight);
    r.setX(header->sectionViewportPosition(index.column()) +r.x() );
    r.setHeight(rowHeight);
    r.setWidth(width);
    */
    return itemRect(index.row(),index.column(),index.parent().row() );
}

QRect albumView::itemRect(int row, int column, int parentR) const
{
    QRect r=itemsRect(parentR);

    int width=header->sectionSize(column);
    r.setY(r.y()+row*rowHeight);
    r.setX(header->sectionViewportPosition(column) +r.x() );
    r.setHeight(rowHeight);
    r.setWidth(width);
    return r;

}

QRect albumView::albumRect(const QModelIndex& index) const
{
    QRect r=albumRects[index.row()];
    if(!isExpanded(index) )
    {
        return r;
    }
    
    r.setHeight(albumMinHeight);
    r.setWidth(albumMinHeight);
    return r;
}

void albumView::rowsInserted(const QModelIndex &parent, int start,int end)
{   
    QAbstractItemView::rowsInserted(parent,start,end); 
//     return ;
    hashIsDirty = true; 
    calculateRectsIfNecessary();
    
    if(isAlbum(parent) && isExpanded(parent))
    {
        
        for(int i=start;i<=end;i++)
        {
            QModelIndex index=model()->index(i,Basic::RATING,parent);
            openPersistentEditor(index);
        }
    }
    else
    {
        for(int i=start;i<=end;i++)
        {
            QModelIndex index=model()->index(i,0,parent);
            int id=index.data(ID_ROLE).toInt();
            if(storeExpanded.contains(id) )
            {
                setExpanded(index,true);
            }
        }
    }
}

void albumView::rowsAboutToBeRemoved(const QModelIndex &parent,int start, int end)
{
    hashIsDirty = true;
//     expanded.clear();
    
    if(!parent.isValid())
    {
        for(int i=start;i<=end;i++)
        {
            QModelIndex index=model()->index(i,0);
            int id=index.data(ID_ROLE).toInt();
            
            if(expanded.contains(id))
            {
                expanded.remove(id);
                storeExpanded.insert(id);
            }
        }
    }
    
    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void albumView::paintEvent(QPaintEvent* e)
{
//     qDebug()<<"PAINT";
    calculateRectsIfNecessary();
    mousePoint=viewport()-> mapFromGlobal(QCursor::pos());
    hoverIndex=indexAt(mousePoint);
    
    QAbstractItemView::paintEvent(e);
    
    QPainter painter(viewport());
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    for (int row = 0; row < model()->rowCount(); ++row) 
    {
        QModelIndex index = model()->index(row, 0); 
        QStyleOptionViewItemV4 option = styleOptions(index);      
//         itemDelegate()->paint(&painter, option, index);
        drawAlbum(&painter,option,index);
        drawChildren(index,&painter);
    }
}

void albumView::drawChildren(const QModelIndex& index, QPainter* p)
{
    if(!isExpanded(index))
        return ;

    
    for(int i=0;i<model()->columnCount(index); i++)
    {    
        if(header->isSectionHidden(i))
            continue; 
                        
        QRect r=itemRect(-1,i,index.row());
        r=viewportRectForRow(r);
        paintHeader(p,r,i);
    }
    
    QRect r=headerRect(index.row());
    r=viewportRectForRow(r);

    QStyleOptionFrameV3 option;
    option.lineWidth=r.width();
    option.midLineWidth=r.width();
    option.state |= QStyle::State_Sunken;
    r.setY(r.y()+r.height() );
    option.rect=r;
    option.frameShape=QFrame::HLine;
    
    style()->drawControl(QStyle::CE_ShapedFrame,&option,p);    
    
    
    for (int row = 0; row < model()->rowCount(index); ++row) 
    {
        for(int j=0;j<model()->columnCount(index); j++)
        {            
            if(header->isSectionHidden(j))
                continue;            
            
            QModelIndex in=model()->index(row,j,index);
            QStyleOptionViewItemV4 option = styleOptions(in);
            itemDelegate()->paint(p ,option,in);
        }
    }
}

void albumView::drawAlbum(QPainter* painter, QStyleOptionViewItemV4& option, const QModelIndex& index) const
{
    painter->save();
    if(option.state & QStyle::State_MouseOver )
    {
        style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    }
    
    option.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
    QRect r=option.rect;    
    r.setX(r.x()+space);
    r.setY(r.y()+space);    
    QPixmap pic=views::decor->decorationPixmap(option,index);
    pic=pic.scaled(option.decorationSize, Qt::KeepAspectRatio,  Qt::SmoothTransformation);
    QRect shadowR=r;
    shadowR.setWidth(pic.width());
    shadowR.setHeight(pic.height());
    QPoint p=r.topLeft();
    p.setX(p.x()+2);
    p.setY(p.y()+2);
    shadowR.moveTopLeft(p);
    QPainterPath shadowPath;
    shadowPath.addRoundedRect(shadowR,1,1);
        
    painter->setOpacity(0.5);    
    painter->fillPath(shadowPath,Qt::black);
    painter->setOpacity(1);
    style()->drawItemPixmap(painter,r,Qt::AlignLeft|Qt::AlignTop,pic ); 
    r.setX(r.x()+pic.width()+space +2);

    //draw text
    QString text=index.data(Qt::DisplayRole).toString(); 
    if(text.isEmpty())
    {
        text=tr("Unknown album");
        painter->setOpacity(0.5);
    }

    painter->setFont(option.font);
    painter->drawText( r,option.displayAlignment, text);

    
#if 0    
    int w=option.fontMetrics.boundingRect(text).width();
//     r.setWidth(w+space);
    r.setHeight(rowHeight);

    option.rect=r;
//     option.rect.setX(r.x()-5);
//     option.rect.setY(r.y()-5);
    option.displayAlignment=Qt::AlignLeft|Qt::AlignTop;
    option.decorationAlignment=Qt::AlignRight|Qt::AlignTop;
    
    
    if(option.state & QStyle::State_Selected )
    {
//         style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    }

    
    painter->setFont(option.font);
    painter->drawText( r,option.displayAlignment, text);
    
    
    r.setX(r.x()+w+20);   
    r.setWidth(space);
    option.rect=r;

    painter->setOpacity(1);
    if(isExpanded(index))
        style()->drawPrimitive(QStyle::PE_IndicatorArrowDown,&option,painter);
    else
        style()->drawPrimitive(QStyle::PE_IndicatorArrowRight,&option,painter);
        
#endif    
    painter->restore();    

    
}

void albumView::hideHeader() //this is a slot
{
    header->setVisible(false);
}

void albumView::setExpanded(const QModelIndex& index, bool expanded)
{
    if(model()==0 || !index.isValid())
        return ;
        
    if(!model()->hasChildren(index) )
    {
        return ;
    }
    
    if(isExpanded(index) == expanded )
        return ;
    
    hashIsDirty=true;
    if(expanded)
    {
        this->expanded.insert(index.data(ID_ROLE).toInt());
        if(model()->canFetchMore(index))
        {
            model()->fetchMore(index);
        }
    }
    else
    {   
        int id=index.data(ID_ROLE).toInt();
        this->expanded.remove(id);
        storeExpanded.remove(id);
        
    }
    updateGeometries();
}

void albumView::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    QAbstractItemView::currentChanged(current, previous);
//     setExpanded(current,true);
    
}

bool albumView::isExpanded(const QModelIndex& index) const
{
    if(model()==0 || !index.isValid())
        return false;
    
    if(!model()->hasChildren(index) )
        return false;
    
//     calculateRectsIfNecessary();
    return expanded.contains(index.data(ID_ROLE).toInt() );
}


void albumView::updateGeometries()
{
    calculateRectsIfNecessary();
    QAbstractItemView::updateGeometries();
//     updateScrollBars();
}

void albumView::resizeEvent(QResizeEvent *e)
{
    hashIsDirty = true;
    updateGeometries();
    
}

void albumView::scrollContentsBy(int dx, int dy)
{
    scrollDirtyRegion(dx, dy);
    viewport()->scroll(dx, dy);
}

QStyleOptionViewItemV4 albumView::styleOptions(const QModelIndex& index) const
{
    QStyleOptionViewItemV4 opt = QStyleOptionViewItemV4(viewOptions() );
    
    if(isAlbum(index))
    {
#if 0        
        if (selectionModel()->isSelected(index))
        {
            opt.state |= QStyle::State_Selected;
            opt.showDecorationSelected=true;
        }
#endif        
        opt.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
        opt.rect= viewportRectForRow(albumRects[index.row()] );
//          opt.rect = visualRect(index);
        if(hoverIndex==index  )
        {
            opt.state |= QStyle::State_MouseOver;
        }

        opt.displayAlignment=Qt::AlignLeft|Qt::AlignTop;
        opt.decorationSize=DECOR_SIZE;
        opt.font.setBold(true);
            
    }
    else
    {
        QModelIndex parent=index.parent();
        int columns=header->count();
        int pos=header->sectionPosition(index.column());
        
        if(columns==1)
        {
            opt.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
        }
        else if(pos==columns )
        {
            opt.viewItemPosition = QStyleOptionViewItemV4::End;
        }
        else if(pos==0)
        {
            opt.viewItemPosition = QStyleOptionViewItemV4::Beginning;
        }
        else
        {
            opt.viewItemPosition = QStyleOptionViewItemV4::Middle;
        }
        
        opt.rect = visualRect(index);
        
        if (selectionModel()->isSelected(index))
        {
            opt.state |= QStyle::State_Selected;
        }
        else if(hoverIndex.isValid() && hoverIndex.row()==index.row() && hoverIndex.parent()==index.parent()  )
        {
            opt.state |= QStyle::State_MouseOver;
        }
        
        if(indexWidget(index)!=0)
            opt.features=QStyleOptionViewItemV2::None;
        else
            opt.features=QStyleOptionViewItemV2::HasDisplay;
        
        opt.displayAlignment=Qt::AlignLeft|Qt::AlignVCenter;        
    }
    

    //we use pseudo-inactive role at the model from DISABLE_ROLE at index.data
    //Thus all the indexes are active
    opt.state & QStyle::State_Active;    
    QPalette::ColorGroup cg=QPalette::Active;
    opt.palette.setCurrentColorGroup(cg);

    opt.fontMetrics=QFontMetrics(opt.font);
    
    return opt;
}

void albumView::resetSlot()
{
    albumRects.clear();
//     expanded.clear();
    hashIsDirty=true;   
}


void albumView::mouseMoveEvent(QMouseEvent* event)
{
    QAbstractItemView::mouseMoveEvent(event);
    //TODO more efficient method
    if(model()==0)
        return;
    
    int i;    
    for( i=0;i<model()->rowCount();i++)
    {
        QRect r=headerRect(i);
        r=viewportRectForRow(r);
        if(r.contains(event->pos()) )
        {
            QModelIndex index=model()->index(i,0);
            headerRow=i;
            header->setRootIndex(index);
            header->setGeometry(r);
//             header->move(r.topLeft());
            header->setVisible(true);
            update();
            break;
        }
    }
    if(i==model()->rowCount() )
    {
        header->setVisible(false);
    }
    viewport()->update();
    return ;
}

void albumView::mousePressEvent(QMouseEvent *event)
{    
    QAbstractItemView::mousePressEvent(event);
//     setCurrentIndex(indexAt(event->pos()));
}

bool albumView::isAlbum(const QModelIndex& index) const
{
    if(!index.isValid())
        return false;
    
    return !index.parent().isValid();
}

void albumView::columnsUpdated()
{
//     qDebug()<<"IPPP "<<header->stretchSectionCount();
//     header->setFixedWidth(header->sizeHint().width());
    hashIsDirty=true;
//     calculateRectsIfNecessary();
    updateGeometries ();
    updateScrollBars();
}

void albumView::columnResized(int i)
{
    hashIsDirty=true;
    columnResizeTimer.start();
}

void albumView::updateScrollBars() const
{
     horizontalScrollBar()->setRange(0, qMax(0, HEADER_OFFSET+header->length() -viewport()->width() ) );
//     verticalScrollBar()->setRange(0, qMax(0, prevHeight -viewport()->height() ) );
}

void albumView::paintHeader(QPainter *painter,QRect &rect, int logicalIndex)
{
    painter->save();
    rect.setX(rect.x()+2);
    if(logicalIndex==header->sortIndicatorSection() )
    {
        rect.setWidth(rect.width()-20);
    }
    
    QString text=model()->headerData(logicalIndex,Qt::Horizontal).toString();
    QFont f=painter->font();
    f.setBold(true);
    painter->setFont(f);
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignTop, text);
    

    painter->restore();
}

QList< QUrl > albumView::getUrls(const QModelIndexList& list) const
{
    QSet<QUrl> urlSet;
    
    foreach(QModelIndex index,list)
    {        
        if(isAlbum(index))
        {
            QSet<QUrl> l=getChildrenUrls(index);
            urlSet.unite(l);
        }
        else
        {
            QUrl u=index.data(URL_ROLE).toUrl();
            if(u.isValid() )
            {
                urlSet.insert(u);
            }
        }
    }
    return urlSet.toList();
}


void albumView::startDrag(Qt::DropActions supportedActions)
{
    QModelIndexList list=selectedIndexes();

    QList<QUrl> urls;
        
    urls=getUrls(list);

    if(urls.isEmpty() )
    {
        return ;
    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(urls);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(views::decor->tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction|Qt::MoveAction);

}

void albumView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QAbstractItemView::selectionChanged(selected, deselected);    
    return ;
#if 0
    QModelIndexList l=selectionModel()->selectedIndexes();
    foreach(QModelIndex index,l)
    {
        if(isAlbum(index) )
        {
//             QModelIndex parent=topLeft;        
            QModelIndex topLeft=model()->index(0,0,index);
            QModelIndex bottomRight=model()->index(model()->rowCount(index)-1,model()->columnCount(index)-1,index);
            QItemSelection selection(topLeft,bottomRight);        
            selectionModel()->select(selection, QItemSelectionModel::Select);
        }        
    }
    viewport()->update();
#endif
}

void albumView::mouseReleaseEvent(QMouseEvent* event)
{
    QModelIndex current=currentIndex();
    QAbstractItemView::mouseReleaseEvent(event);    
//     return ;    
    if(event->button()==Qt::LeftButton) 
    {
        QModelIndex index=indexAt(event->pos());
        if(!current.isValid() || current==index )
        {
            setExpanded(index,!isExpanded(index));
        }
    }
}

QSet<QUrl> albumView::getChildrenUrls(const QModelIndex& parent) const
{
    QSet<QUrl> l;
    
    if(model()==0)
        return l;
    
    if(!model()->hasChildren(parent))
    {
        return l;
    }
    
    if(model()->canFetchMore(parent) )
        model()->fetchMore(parent);
    
    
    for(int i=0;i<model()->rowCount(parent);i++)
    {
        QModelIndex in=model()->index(i,0,parent);
        QUrl u=in.data(URL_ROLE).toUrl();

        if(u.isValid() )
        {
            l.insert(u);
        }
    }
    return l;
}

void albumView::doubleClickedSlot(const QModelIndex &index)
{
    int row=0;
    QModelIndex parent;
    if(!isAlbum(index))
    {
        parent=index.parent();
        row=index.row();
    }
    
    QList<QUrl> urls=getChildrenUrls(parent).toList();
    
    core::nplList list;
    foreach(QUrl u,urls)
    {             
        core::nplPointer t=core::nplTrack::getNplTrack(u);
        list<<t;
    }
    
    if(list.isEmpty() )
    {
        return ;
    }
    
    core::npList()->clear();
    core::npList()->insert(0,list);

   
    core::engine()->play(row );
    
}

void albumView::sortModel(int logicalIndex, Qt::SortOrder order)
{
    model()->sort(logicalIndex,order);
}


void albumView::writeSettings()
{
    if (objectName().isEmpty() )
    {
        return ;
    }

    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, objectName() );
    group.writeEntry( "state", QVariant(header->saveState() ));
    group.config()->sync();
}

void albumView::readSettings()
{
    if(objectName().isEmpty())
        return ;
    
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, objectName() );
    _headerState=group.readEntry( "state", QByteArray() );
}

void albumView::contextMenuEvent(QContextMenuEvent *e)
{
    QAbstractItemView::contextMenuEvent(e);
    emit showContextMenu(indexAt(e->pos() ),selectedIndexes() );
}

void albumView::editCurrent()
{
    edit( currentIndex() );
}