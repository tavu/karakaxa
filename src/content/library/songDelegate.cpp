#include"songDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
#include<player.h>
#include<KIcon>
#include<QFontMetrics>
#include<trackView.h>
using namespace player;
#define FONT_SIZE 9
#define ITEM_SIZE 9
#include<QPixmap>
#include <kicon.h>
#include <kiconeffect.h>

songDelegate::songDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
{

}

void songDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();


    if (index.row()%2==1)
    {
        painter->save();
        painter->setOpacity(0.1);
        painter->fillRect(option.rect,player::pal.window());
// 	  painter->restore();
    }


    QPen pen;

    painter->setOpacity(0.8);
    pen.setWidth(1);
    pen.setColor(player::pal.window() );
    painter->setPen(pen);
    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());

    painter->setOpacity(0.1);
    pen.setWidthF(4);
    pen.setColor(player::pal.window() );
    painter->setPen(pen);
    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());

    painter->restore();
    painter->save();

    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    QFont font=painter->font();
    font.setPointSize(FONT_SIZE);
    painter->setFont(font);

    QFontMetrics fontMetric(font);

    if (option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText());
    }

    if (index.column()==TRV_RATING)
    {
        drawStar(painter,option.rect,index.data().toInt() );
        painter->restore();
        return;
    }

    QRect r=option.rect;
    r.setWidth(r.width()-4);

    r.setX(r.x()+2);

    QString text = fontMetric.elidedText(index.data(Qt::DisplayRole).toString(),Qt::ElideRight,r.width() );
    painter->drawText( r,Qt::AlignLeft, text);
    painter->restore();

}

QSize songDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(ITEM_HEIGHT ,ITEM_HEIGHT);
}

void songDelegate::drawStar(QPainter *painter,QRect rect,int num) const
{
//      if(num==0)
// 	  return ;

    int n=num/25;
    if (num%25>0 && n!=10) 	n++;

    KIcon icon("favorites");
    QPixmap activeStar=icon.pixmap();
    activeStar=activeStar.scaledToHeight(rect.height(),Qt::SmoothTransformation);

    QPixmap greyStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 1, QColor(), false );

    QPixmap halfStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 0.2, QColor(), false );

//      activeStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 0.8, QColor(), false );
    int i;
    for (i=0;i<n;i+=2)
    {
        painter->drawPixmap(rect.x()+(i/2)*rect.height(),rect.y(),activeStar );
    }

    if (n-i==-1)
    {
        int x=rect.x()+(i/2)*activeStar.width();
        int y=rect.y();
// 	  p=p.scaled(rect.height()-4,rect.height()-4,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        painter->drawPixmap(x ,y ,activeStar.width()/2, activeStar.height() ,activeStar, 0,0,activeStar.width()/2,activeStar.height() );
        painter->drawPixmap(x+activeStar.width()/2 ,y ,activeStar.width()/2, activeStar.height() ,greyStar, activeStar.width()/2,0,activeStar.width()/2,activeStar.height() );
        // 	  painter->drawPixmap(rect.x()+(i/2)*activeStar.width()+activeStar.width()/2,rect.y(),activeStar.width()/2,activeStar.height(),greyStar);

        i+=2;
    }

    while (i<10)
    {
        painter->drawPixmap(rect.x()+(i/2)*rect.height(),rect.y(),greyStar );
        i+=2;
    }
}
