#include"albumDelegate.h"
#include<QApplication>
#include<QPainter>
#include<player.h>
albumDelegate::albumDelegate(QObject* parent): QStyledItemDelegate(parent)
{
    sideSpace=2;
    topSpace=4;
    
}

void albumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );            
//     QPoint topLeft(
    int f=option.fontMetrics.height()*2+8;
    QRect r(option.rect.x()+sideSpace,option.rect.y()+topSpace,option.rect.width()-sideSpace,option.rect.height()-f);
    QPixmap pic=player::decor.decorationPixmap(option,index);
    pic=pic.scaled(r.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QRect rect=option.rect;    
    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,r,Qt::AlignTop|Qt::AlignHCenter,pic );
        rect.setY(r.y()+r.height()+1);
    }
    QString s=displayText(index.data(),QLocale("UTF-8") );
    drawDisplay(painter,option,rect,s);
    
}

void albumDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const
{
    painter->save();
    text=text.simplified();
    if(text.isEmpty())
    {
	painter->setOpacity(0.5);
	text=tr("Uknown album");
    }
    painter->drawText( rect,Qt::AlignTop|Qt::AlignHCenter|Qt::TextWordWrap, text);
    painter->restore();
}