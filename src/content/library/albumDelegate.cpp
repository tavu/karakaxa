#include"albumDelegate.h"
#include<QApplication>
#include<QPainter>
#include<player.h>

#define TEXT_H 30
albumDelegate::albumDelegate(QObject* parent): QStyledItemDelegate(parent)
{
    sideSpace=2;
    topSpace=4;
    
}

void albumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
     QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );            

    /*
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
    */
    QPixmap pic=player::decor.decorationPixmap(option,index);
    QRect r=option.rect;
//     r.setX(r.x()+5);
//      r.setWidth(r.width()-10);
//     r.setY(r.y()+5);    
    
    QRect textR=r;
    textR.setY(r.y()+textR.height()-TEXT_H );
    textR.setHeight(TEXT_H);
    
//     QRect r=rr;
    r.setHeight(r.height()-TEXT_H);
    
//     r.setY(r.y()+40);
     pic=pic.scaled(r.size(), Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
    
    QString s=displayText(index.data(),QLocale("UTF-8") );
    
//     r.setHeight(r.height()-10);
//     QRect re=option.fontMetrics.boundingRect(rr,Qt::AlignTop|Qt::AlignBottom|Qt::TextWordWrap, s);
    
    QRect shadowR=r;
    shadowR.setX(r.x()+20);
    shadowR.setY(r.y()+20);
    painter->setOpacity(0.3);
//     painter->fillRect(shadowR,Qt::black);
    painter->setOpacity(1);
    QApplication::style()->drawItemPixmap(painter,r,Qt::AlignTop|Qt::AlignHCenter,pic );
    drawDisplay(painter,option,textR,s);
    
    
}

void albumDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const
{
    painter->save();
/*    
    QPen p(Qt::white);
     painter->setPen(p);*/
    
    text=text.simplified();
    if(text.isEmpty())
    {
	painter->setOpacity(0.5);
	text=tr("Uknown album");
    }
    painter->drawText( rect,Qt::AlignCenter|Qt::TextWordWrap|Qt::TextDontClip, text);
    painter->restore();
}