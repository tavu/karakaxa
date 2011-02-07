#include"artistDelegate.h"
#include<QApplication>
#include<QPainter>
#include<player.h>
artistDelegate::artistDelegate(QObject* parent)
    :QStyledItemDelegate(parent)
{
    
}

void artistDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    
    QPixmap pic=player::decor.decorationPixmap(option,index);
    
    QRect r=option.rect;
    
    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,r,Qt::AlignVCenter|Qt::AlignLeft,pic );
        r.setX(r.x()+pic.width()+1);
    }
    QString s=index.data().toString();    
    drawDisplay(painter,option,r,s);
}

void artistDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const
{
    painter->save();
    text=text.simplified();
    if(text.isEmpty())
    {
	painter->setOpacity(0.5);
	text=tr("Unown album");
    }
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextWordWrap, text);
    painter->restore();
}
