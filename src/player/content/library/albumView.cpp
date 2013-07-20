#include"albumView.h"
#include<QScrollBar>
#include<QPainter>
#include<QDebug>
#include<QPaintEvent>

albumView::albumView(QWidget* parent): QAbstractItemView(parent)
{
    rowHeight=20;
    albumOffset=20;
    albumWidth=80;
    albumMinHeight=100;
    albumInfoHeight=40;
    
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
    setAutoFillBackground(true);
    verticalScrollBar()->setPageStep(rowHeight);
    space=10;
    //the setModel function will set it to true
    hashIsDirty=false;
}

void albumView::setModel(QAbstractItemModel* m)
{
    hashIsDirty=true;
    QAbstractItemView::setModel(m);
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
    QPoint point(_point);
    point.rx() += horizontalScrollBar()->value();
    point.ry() += verticalScrollBar()->value();
    
    
    QRect rect;
    int i;
    for(i=0;i<albumRects.size();i++)
    {
        QRect &r=albumRects[i].rect;
        if (r.contains(point))
        {
            rect=r;
            break;
        }
    }
        
    if(rect.isEmpty())
    {
        return QModelIndex(); 
    }
    
return model()->index(i,0);
    
}

bool albumView::isIndexHidden(const QModelIndex& index) const
{
    if(index.parent().isValid() )
    {
        int row=index.parent().row();
        if(!albumRects[row].isExpanded)
        {
            return false;
        }
    }
    
    return false;
}

QModelIndex albumView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

void albumView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
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

}



QRegion albumView::visualRegionForSelection(const QItemSelection& selection) const
{
    return QRegion();
}


void albumView::calculateRectsIfNecessary() const
{
    if (!hashIsDirty)
        return;
    
    QRect prevRect(10,10,0,0);
    for (int row = 0; row < model()->rowCount(); ++row) 
    {        
        int height=0;
        if(expanded.contains(row))
        {
            QModelIndex index=model()->index(row,0);
            int rowCount=model()->rowCount(index);
            height=(rowCount+1)*rowHeight +albumInfoHeight;
        
            if(height<albumMinHeight)
            {
                height=albumMinHeight;
            }
            qDebug()<<"EXPAN "<<height;
        }
        else
        {
            height=albumMinHeight;
        }
        QRect albumR;        
        
        //albuR is bellow the previous album
        albumR.setX(10);
        albumR.setY(prevRect.y()+prevRect.height() );
        albumR.setWidth(viewport()->width() );        
        albumR.setHeight(height);
        albumRects[row].rect=albumR;
        
        qDebug()<<"ITEM R "<<albumR.x()<<" "<<albumR.y()<<" "<<albumR.height()<<" "<<albumR.width();
        prevRect=albumR;
    }
    
    
//     horizontalScrollBar()->setRange(0, width());
    verticalScrollBar()->setRange(0, qMax(0, prevRect.bottomLeft().y() -viewport()->height() ) );
    
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
    
    if(!index.parent().isValid())
    {
        r=albumRect(index);
    }
    else
    {
        r=itemRect(index);
    }
    
    r=viewportRectForRow(r);
//     qDebug()<<"ITEM R "<<r.x()<<" "<<r.y()<<" "<<r.height()<<" "<<r.width();
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

QRect albumView::itemRect(const QModelIndex& index) const
{
    calculateColumnRects(index.parent());
    int albumRow=index.parent().row();
    QRect r=albumRects[albumRow].rect;    
        
    r.setY(r.y()+index.row()*rowHeight +albumInfoHeight);
    r.setX(albumOffset+albumWidth +columnWidth[index.column()]);
    r.setHeight(rowHeight);
    
    r.setWidth(columnWidth[index.column()+1]-columnWidth[index.column()]);
    
//     qDebug()<<"ITEM R "<<r.x()<<" "<<r.y()<<" "<<r.height()<<" "<<r.width();
    return r;
}

QRect albumView::albumRect(const QModelIndex& index) const
{
    QRect r=albumRects[index.row()].rect;
    r.setWidth(albumWidth);
    return r;
}


void albumView::rowsInserted(const QModelIndex &parent, int start,int end)
{    
//     hashIsDirty = true;
 /*   QAbstractItemView::rowsInserted(parent, start, end);
    if(parent.isValid() && isExpanded(parent))
    {
        hashIsDirty = true;
    }
    qDebug()<<"S "<<start<<" "<<end;
    if(!parent.isValid())
    {
        for(int i=start;i<=end;i++)
        {
            struct albumInfo al;
            al.isExpanded=false;
            al.rect=QRect(0,0,0,0);
            albumRects.insert(i,al);
        }
         hashIsDirty = true;
    }
    */
    hashIsDirty = true; 
    calculateColumnRects(parent);    
}

void albumView::calculateColumnRects(const QModelIndex& index) const
{
    if(!index.isValid() )
        return ;
    
    if(!model()->hasChildren(index) )
        return ;
        
    
    int columns=model()->columnCount(index);
    
    if(columns+1==columnWidth.size() )
        return ;
    
    qDebug()<<"C "<<columns<<" "<<index.data();
    
    columnWidth.clear();
    for(int i=0;i<=columns;i++)
    {
        columnWidth<<(150*i);
    }
}


void albumView::rowsAboutToBeRemoved(const QModelIndex &parent,int start, int end)
{
    hashIsDirty = true;
    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void albumView::paintEvent(QPaintEvent* e)
{
    calculateRectsIfNecessary();
    QAbstractItemView::paintEvent(e);
//     qDebug()<<"paint";
    QPainter painter(viewport());
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    QStyleOptionViewItem option = viewOptions();
    for (int row = 0; row < model()->rowCount(); ++row) 
    {
        QModelIndex index = model()->index(row, 0); 
        drawAlbumText(&painter,index);
        QStyleOptionViewItem option = viewOptions();
        option.rect = visualRect(index);
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
            QStyleOptionViewItem option = viewOptions();
            QModelIndex in=model()->index(row,j,index);
            option.rect = visualRect(in);
            itemDelegate()->paint(p, option, in);            
        }
    }
}


void albumView::setExpanded(const QModelIndex& index, bool expanded)
{
    if(model()==0)
        return ;
        
    
    if( model()->hasChildren(index) )
    {
        if(model()->canFetchMore(index))
            model()->fetchMore(index);
        
//         calculateRectsIfNecessary();
        this->expanded.insert(index.row());
        hashIsDirty=true;
        qDebug()<<"EDOO";
        calculateRectsIfNecessary();
    }
}

void albumView::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
//     QAbstractItemView::currentChanged(current, previous);
    
    setExpanded(current,!isExpanded(current));
}

bool albumView::isExpanded(const QModelIndex& index)
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
}

void albumView::resizeEvent(QResizeEvent *e)
{
    hashIsDirty = true;
    updateGeometries();
    
}

void albumView::scrollContentsBy(int dx, int dy)
{
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
    QRect r=albumRects[index.row() ].rect;    
            
    r.setX(albumOffset+albumWidth);
    r.setHeight(rowHeight);
    r.setWidth(viewport()->width());
    return r;
}