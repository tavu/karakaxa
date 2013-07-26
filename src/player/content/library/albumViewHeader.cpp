#include"albumViewHeader.h"
#include<QPainter>
#include <QApplication>
#include<QDebug>
albumViewHeader::albumViewHeader(QWidget* parent): QHeaderView(Qt::Horizontal, parent)
{
//     setStyleSheet("QHeaderView::section {alignment: left; font: bold; }" );
    pal=palette();
     setDefaultAlignment(Qt::AlignLeft|Qt::AlignTop);
     QString s=QString("QHeaderView::section{background-color: %1; font: bold; } QHeaderView{background-color: transparent;}");
     s=s.arg(palette().highlight().color().lighter(200).name());
//      s=s.arg("transparent");
    QPalette p=palette();
    QColor c;
    c.setAlpha(0);
    p.setColor(QPalette::Window,c);
    p.setColor(QPalette::Base,c);
    p.setColor(QPalette::Button,c);
    
    setStyleSheet("QHeaderView::section{ font: bold; } QHeaderView{background-color: transparent;} ");
    
//     setAutoFillBackground(false);
}

void albumViewHeader::paintSection(QPainter* painter, const QRect& _rect, int logicalIndex) const
{
    painter->save();
    QFont f=painter->font();
    f.setBold(true);
    painter->setFont(f);
//     QHeaderView::paintSection(painter,_rect,logicalIndex);
    QStyleOptionHeader opt;
    opt.rect=_rect;
    opt.rect.setX(_rect.x()+_rect.width());
    opt.rect.setHeight(_rect.height() - 5);
/*
    opt.position = QStyleOptionHeader::Middle;
    opt.state & QStyle::State_Active; 
    opt.rect=_rect;
    opt.rect.setX(_rect.x()+_rect.width());
    opt.palette=QPalette();
    opt.state |= QStyle::State_Enabled;
    opt.section =logicalIndex;
    */

    style()->drawPrimitive(QStyle::PE_IndicatorDockWidgetResizeHandle, &opt, painter);
    
//     style()->drawPrimitive(QStyle::PE_FrameFocusRect, &opt, painter, this);
    painter->restore();
//     QApplication::style()->drawControl(QStyle::State_Sibling, &opt, painter);

    return ;
}

void albumViewHeader::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
}
