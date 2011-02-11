#include"albumDelegate.h"
#include<QApplication>
#include<QPainter>
#include<player.h>
albumDelegate::albumDelegate(QObject* parent): QStyledItemDelegate(parent)
{
    
}

void albumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    
    QPixmap pic=player::decor.decorationPixmap(option,index);
    
    QRect r=option.rect;
    r.setY(r.y()+4);
    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,r,Qt::AlignTop|Qt::AlignHCenter,pic );
        r.setY(r.y()+pic.height()+1);
    }
    QString s=displayText(index.data(),QLocale("UTF-8") );
    drawDisplay(painter,option,r,s);
    
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