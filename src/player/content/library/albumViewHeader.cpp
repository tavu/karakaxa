#include"albumViewHeader.h"
#include<QPainter>
#include <QApplication>
#include<QDebug>
albumViewHeader::albumViewHeader(QWidget* parent) :views::treeViewHeader(parent)
{
//     setStyleSheet("QHeaderView::section {alignment: left; font: bold; }" );

     setDefaultAlignment(Qt::AlignLeft|Qt::AlignTop);
     setSortIndicatorShown(true);
     setClickable(true);
     setSelectionMode(QAbstractItemView::NoSelection);
     setStretchLastSection(false);
//      setResizeMode(QHeaderView::Fixed);
//      QString s=QString("QHeaderView::section{background-color: %1; font: bold; } QHeaderView{background-color: transparent;}");
//      s=s.arg(palette().highlight().color().lighter(200).name());
// //      s=s.arg("transparent");
//     QPalette p=palette();
//     QColor c;
//     c.setAlpha(0);
//     p.setColor(QPalette::Window,c);
//     p.setColor(QPalette::Base,c);
//     p.setColor(QPalette::Button,c);
    
    setStyleSheet("QHeaderView::section{ font: bold; } QHeaderView{background-color: transparent;} ");
//     connect(this,SIGNAL(sectionPressed(int)),this,SLOT(sortModel(int)));
//     setAutoFillBackground(false);
    
//     setOffsetToLastSection();
}

void albumViewHeader::paintSection(QPainter* painter, const QRect& _rect, int logicalIndex) const
{
    painter->save();
    QFont f=painter->font();
    f.setBold(true);
    painter->setFont(f);
//     QHeaderView::paintSection(painter,_rect,logicalIndex);
    QStyleOptionHeader opt;
    
    if(logicalIndex==sortIndicatorSection())
    {    
        if(sortIndicatorOrder()==Qt::AscendingOrder)
        {
            opt.sortIndicator=QStyleOptionHeader::SortUp;
        }
        else
        {
            opt.sortIndicator=QStyleOptionHeader::SortDown;
        }
//         opt.decorationAlignment=Qt::AlignRight|Qt::AlignHCenter;
        opt.rect=_rect;
        opt.rect.setX(_rect.x()+_rect.width() -20);
        opt.rect.setHeight(_rect.height() - 5);
        style()->drawPrimitive(QStyle::QStyle::PE_IndicatorHeaderArrow, &opt, painter);
    }
    opt.rect=_rect;
    opt.rect.setX(_rect.x()+_rect.width());
    opt.rect.setHeight(_rect.height() - 5);

    style()->drawPrimitive(QStyle::PE_IndicatorDockWidgetResizeHandle, &opt, painter);
    painter->restore();
    return ;
}
QSize albumViewHeader::sizeHint() const
{
    return views::treeViewHeader::sizeHint();
//     return QSize(25,1500);
}
