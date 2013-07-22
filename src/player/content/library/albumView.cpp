#include"albumView.h"
#include <Basic/tagsTable.h>
#include<QScrollBar>
#include<QPainter>
#include<QDebug>
#include<QPaintEvent>
#include <QHeaderView>
#include"albumDelegate.h"

#define DECOR_SIZE QSize(80,80)

albumView::albumView(QWidget* parent): QAbstractItemView(parent)
{
    rowHeight=20;
    albumOffset=20;
    albumWidth=80;
    albumMinHeight=100;
    albumInfoHeight=40;
    
    setItemDelegate(new albumDelegate(this) );
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
    setAutoFillBackground(true);
    verticalScrollBar()->setPageStep(rowHeight);
    space=10;
    //the setModel function will set it to true
    hashIsDirty=false;
    setMouseTracking(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(this,SIGNAL(activated(QModelIndex)),this,SLOT(acivateIndex(QModelIndex)) );
    header=new albumViewHeader(this );
    header->setVisible(false);
//     header->setResizeMode(QHeaderView::Fixed);
    
//     header->setStyleSheet("QAbstractItemView::item {background-color: transparent; }");
    
    connect(horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(hideHeader()) );
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(hideHeader()) );
    
    connect(header,SIGNAL(geometriesChanged()),this,SLOT(columnsUpdated()) );
    connect(header,SIGNAL(sectionResized(int,int,int)),this,SLOT(columnsUpdated()) );
    connect(header,SIGNAL(sectionMoved(int,int,int)),this,SLOT(columnsUpdated()) );
}

void albumView::hideHeader()
{
    header->setVisible(false);
}


void albumView::setModel(QAbstractItemModel* m)
{
    if(model()!=0)
        disconnect(model());
        
    QAbstractItemView::setModel(m);
    connect(m,SIGNAL(modelReset() ),this,SLOT(resetSlot()) );
    connect(m,SIGNAL(layoutAboutToBeChanged()),this,SLOT(resetSlot()) );
    
    header->setModel(m);         
    header->setMovable(true);

    columnsUpdated();
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
//     qDebug()<<"EDOO";
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
    
    QRect r=itemsRect(i.key());
    QModelIndex parent=model()->index(i.key(),0);

    if(!r.contains(point))
        return parent;
    
    int height=point.ry() -r.topLeft().ry()  ;
    int itemRow=height/rowHeight ;
 
    int k=header->logicalIndexAt(point);

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
    
//     if()
    return index;
    
}

void albumView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
    return ;
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
}

void albumView::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags)
{
    if(model()==0)
        return ;
    
    QRect rectangle = rect.translated(horizontalScrollBar()->value(),verticalScrollBar()->value()).normalized();
    
    calculateRectsIfNecessary();
    
    QHashIterator<int, QRect> i(albumRects);
    
    int firstRow = model()->rowCount();
    int lastRow = -1;
    
    while (i.hasNext()) 
    {
        i.next();
        if (i.value().intersects(rectangle)) 
        {
            firstRow = firstRow < i.key() ? firstRow : i.key();
            lastRow = lastRow > i.key() ? lastRow : i.key();
        }
    }
    
    if (firstRow != model()->rowCount() && lastRow != -1) 
    {
        QItemSelection selection(
                model()->index(firstRow, 0, rootIndex()),
                model()->index(lastRow, 0, rootIndex()));
        selectionModel()->select(selection, flags);
    }
    else 
    {
        QModelIndex invalid;
        QItemSelection selection(invalid, invalid);
        selectionModel()->select(selection, flags);
    }

}


QRegion albumView::visualRegionForSelection(const QItemSelection& selection) const
{
    return QRegion();
}


void albumView::calculateRectsIfNecessary() const
{
    if (!hashIsDirty)
        return;
    
    int prevHeight = -10;
    for (int row = 0; row < model()->rowCount(); ++row) 
    {        
        int height=0;
        if(expanded.contains(row))
        {
            QModelIndex index=model()->index(row,0);
            int rowCount=model()->rowCount(index);
            height=(rowCount)*rowHeight +albumInfoHeight;
        
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
        
        albumR.setWidth(qMax(viewport()->width(),header->length() ) );        
        albumR.setHeight(height);
        albumRects[row]=albumR;
        prevHeight=albumR.y()+albumR.height();
    }
    
    verticalScrollBar()->setRange(0, qMax(0, prevHeight -viewport()->height() ) );
//     horizontalScrollBar()->setRange(0, width());
    updateScrollBars();
    
    hashIsDirty=false;
    viewport()->update();
}

QRect albumView::visualRect(const QModelIndex& index) const
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

    r=viewportRectForRow(r);
    return r;
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
    r.setY(r.y()+albumInfoHeight);
    return r;
}

QRect albumView::itemRect(const QModelIndex& index) const
{
    QRect r=itemsRect(index.parent().row() );

    int width=header->sectionSize(index.column());
    r.setY(r.y()+index.row()*rowHeight);
    r.setX(header->sectionViewportPosition(index.column()) +r.x() );
    r.setHeight(rowHeight);
    r.setWidth(width);
    
    return r;
}

QRect albumView::albumRect(const QModelIndex& index) const
{
    QRect r=albumRects[index.row()];
    return r;
}

void albumView::rowsInserted(const QModelIndex &parent, int start,int end)
{
    hashIsDirty = true; 
    QAbstractItemView::rowsInserted(parent,start,end);
}

void albumView::rowsAboutToBeRemoved(const QModelIndex &parent,int start, int end)
{
    hashIsDirty = true;
    expanded.clear();
    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void albumView::paintEvent(QPaintEvent* e)
{
    calculateRectsIfNecessary();
    QPoint mousePoint=viewport()-> mapFromGlobal(QCursor::pos());
    hoverIndex=indexAt(mousePoint);
    

    QAbstractItemView::paintEvent(e);
    QPainter painter(viewport());
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    QStyleOptionViewItemV4 option = QStyleOptionViewItemV4(viewOptions() );
    for (int row = 0; row < model()->rowCount(); ++row) 
    {
        QModelIndex index = model()->index(row, 0); 
        QStyleOptionViewItemV4 option = styleOptions(index);      
        itemDelegate()->paint(&painter, option, index);
        drawChildren(index,&painter);
    
    }
}

void albumView::drawChildren(const QModelIndex& index, QPainter* p)
{
    if(!isExpanded(index))
        return ;
    for (int row = 0; row < model()->rowCount(index); ++row) 
    {
        for(int j=0;j<model()->columnCount(index); j++)
        {            
            QModelIndex in=model()->index(row,j,index);
            QStyleOptionViewItemV4 option = styleOptions(in);
            if(row==0)
            {
                if(!header->isVisible() || !header->underMouse() )
                {
                    p->save();
//                     header->paintSection(p,option.rect,j);
                     paintHeader(p,&option,j);
                                        p->restore();
                }
            }
            else
            {
                itemDelegate()->paint(p, option, in);            
            }
        }
    }
}

void albumView::setExpanded(const QModelIndex& index, bool expanded)
{
    if(model()==0 || !index.isValid())
        return ;
        
    if(!model()->hasChildren(index) )
        return ;
    
    if( (isExpanded(index) && expanded ) || ( !isExpanded(index) && !expanded) )
        return ;
    
    hashIsDirty=true;
    if(expanded)
    {
        this->expanded.insert(index.row());
        if(model()->canFetchMore(index))
        {
            model()->fetchMore(index);
        }
    }
    else
    {
        this->expanded.remove(index.row());
    }
    calculateRectsIfNecessary();
}

void albumView::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    QAbstractItemView::currentChanged(current, previous);
    viewport()->update();
    
}

bool albumView::isExpanded(const QModelIndex& index) const
{
    if(model()==0 || !index.isValid())
        return false;
    
    if(!model()->hasChildren(index) )
        return false;
    
//     calculateRectsIfNecessary();
    return expanded.contains(index.row() );
}


void albumView::updateGeometries()
{
    calculateRectsIfNecessary();
    updateScrollBars();
}

void albumView::resizeEvent(QResizeEvent *e)
{
    hashIsDirty = true;
    updateGeometries();
    
}

void albumView::scrollContentsBy(int dx, int dy)
{
//     header->setVisible(false);
    scrollDirtyRegion(10*dx, 5*dy);
    viewport()->scroll(10*dx, 5*dy);
}

void albumView::drawAlbumText(QPainter* painter,const QModelIndex & index ) const
{
    painter->save();
    QRect r=albumTextRect(index);
    r=viewportRectForRow(r);
    QFont f=font();
    f.setBold(true);
//     f.setPixelSize(15);
    painter->setFont(f);
    
    QString text=index.data(Qt::DisplayRole).toString();
    text=text.trimmed();
    if(text.isEmpty())
    {
        painter->setOpacity(0.5);
        text=tr("Uknown album");
    }
    painter->drawText( r,Qt::AlignLeft|Qt::AlignTop, text);
    painter->restore();
}

QRect albumView::albumTextRect(const QModelIndex &index)const
{        
    calculateRectsIfNecessary();
    QRect r=albumRects[index.row() ];    
            
    r.setX(albumOffset+albumWidth);
    r.setHeight(rowHeight);
    r.setWidth(viewport()->width());
    return r;
}

QStyleOptionViewItemV4 albumView::styleOptions(const QModelIndex& index) const
{
    QStyleOptionViewItemV4 opt = QStyleOptionViewItemV4(viewOptions() );
    
    
    if (selectionModel()->isSelected(index))
            opt.state |= QStyle::State_Selected;
     
    QModelIndex parent=index.parent();
    
    int columns=model()->columnCount(parent);
    if(columns==1)
    {
        opt.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
    }
    else if(index.column()==model()->columnCount(index.parent() )-1 )
    {
        opt.viewItemPosition = QStyleOptionViewItemV4::End;
    }
    else if(index.column()==0)
    {
        opt.viewItemPosition = QStyleOptionViewItemV4::Beginning;
    }
    else
    {
        opt.viewItemPosition = QStyleOptionViewItemV4::Middle;
    }
    opt.rect = visualRect(index);
    
    //we use pseudo-inactive role at the model from DISABLE_ROLE at index.data
    //Thus all the indexes are active
    opt.state & QStyle::State_Active;    
    QPalette::ColorGroup cg=QPalette::Active;
    opt.palette.setCurrentColorGroup(cg);
    
    if(hoverIndex.isValid() && hoverIndex.row()==index.row() && hoverIndex.parent()==index.parent()  )
        opt.state |= QStyle::State_MouseOver;
     else
        opt.state &= ~QStyle::State_MouseOver;
    
//     if(currentIndex()==index)
//         opt.state |= QStyle::State_HasFocus;
    
//     opt.state |= QStyle::State_DownArrow;
    opt.decorationSize=DECOR_SIZE;
    
    if(isAlbum(index) )
    {
        opt.displayAlignment=Qt::AlignLeft|Qt::AlignTop;
        opt.font.setBold(true);
    }
    else
    {
        opt.displayAlignment=Qt::AlignLeft|Qt::AlignVCenter;
    }
    
    return opt;
}

void albumView::resetSlot()
{
    albumRects.clear();
    expanded.clear();
    hashIsDirty=true;   
}

void albumView::mouseMoveEvent(QMouseEvent* event)
{
    QAbstractItemView::mouseMoveEvent(event);
    
    QModelIndex in=indexAt(event->pos());
    
    if(in.isValid() && in.parent().isValid() && in.row()==0 )
    {
        QRect r=itemsRect(in.parent().row());
        r.setHeight(rowHeight);
        r=viewportRectForRow(r);
//         header->setGeometry(r );
        header->move(r.topLeft());
        header->resize(r.size());
        header->setVisible(true);
    }
    else
        header->setVisible(false);
    
    viewport()->update();
}

void albumView::mousePressEvent(QMouseEvent *event)
{
    QAbstractItemView::mousePressEvent(event);
    setCurrentIndex(indexAt(event->pos()));
}

bool albumView::isAlbum(const QModelIndex& index) const
{
    return !index.parent().isValid();
}

void albumView::acivateIndex(const QModelIndex& index)
{
    setExpanded(index,!isExpanded(index));
}

void albumView::columnsUpdated()
{
    hashIsDirty=true;
    calculateRectsIfNecessary();
    updateScrollBars();
}

void albumView::updateScrollBars() const
{
    horizontalScrollBar()->setRange(0, qMax(0, header->length()-viewport()->width() ) );
//     verticalScrollBar()->setRange(0, qMax(0, prevHeight -viewport()->height() ) );
}

void albumView::paintHeader(QPainter *painter,QStyleOptionViewItem *opt, int logicalIndex)
{
//     QStyleOptionViewItemV4 opt = QStyleOptionViewItemV4(viewOptions() );    
    
    painter->save();
//     style()->drawPrimitive(QStyle::PE_IndicatorDockWidgetResizeHandle, opt, painter);
    
    QString text=model()->headerData(logicalIndex,Qt::Horizontal).toString();
    QFont f=painter->font();
    f.setBold(true);
    painter->setFont(f);
    painter->drawText( opt->rect,Qt::AlignLeft|Qt::AlignTop, text);
    painter->restore();
//     style()->drawControl()
    
//     painter->setOpacity(0.5);
//     
// //     rect.setY(rect.y() -2);
//     QPen pen;
//     pen.setWidth(2);
//     pen.setColor(palette().window().color() );
//     painter->setPen(pen);
//     
// //     painter->drawLine(rect.topRight(),rect.bottomRight());
//     painter->drawLine(rect.bottomLeft(),rect.bottomRight());

    
//     painter->restore();
}
