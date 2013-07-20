#include"albumDelegate.h"

#include<QApplication>
#include<views/decoration/decoration.h>
#include<QPainter>
#include<views/models/urlRole.h>

#define ALBUM_SIZE 100
#define HEADER_SIZE 20
#include<QDebug>

albumDelegate::albumDelegate(QObject *parent) :QStyledItemDelegate(parent)
{
}

QSize albumDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(!index.parent().isValid())
    {
        return QSize(ALBUM_SIZE,ALBUM_SIZE );
    }
    if(index.row()==0)
    {
        return QSize(HEADER_SIZE,HEADER_SIZE);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

void albumDelegate::paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{    
    QRect r=option.rect;
    if(!index.parent().isValid() )
    {    
//         QApplication::style()->drawPrimitive( QStyle::CE_ItemViewItem, &option, painter );
        
        QPixmap pic=views::decor->decorationPixmap(option,index);
        
//         r.setY(r.y()+10);
//         r.setHeight(r.height()-10);
//         r.setX(r.x()+10);
//         r.setWidth(r.height() +10);   
        
        pic=pic.scaled(r.size(), Qt::KeepAspectRatio,  Qt::SmoothTransformation);
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
        QApplication::style()->drawItemPixmap(painter,r,Qt::AlignLeft|Qt::AlignTop,pic ); 
        r.setX(r.x()+pic.width()+10);
//         drawAlbumDisplay(painter,option,r,index);
        return ;
    }
  
  
    if(index.row()==0 )
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        painter->setOpacity(1);
        QPen pen;
        pen.setWidth(1);
        pen.setColor(option.palette.window().color());
        painter->setPen(pen);
//         painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.bottomLeft(),r.bottomRight());
        r.setX(r.x()+2);
        painter->restore();
    }
    

//     QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    
    drawDisplay(painter,option,r,index);
}

void albumDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect,const QModelIndex &index) const
{
    painter->save();
    if(index.data(BOLD_ROLE).toBool())
    {
        QFont f=option.font;
        f.setBold(true);
        painter->setFont(f);
    }
    rect.setWidth(rect.width()-10);
    QString text=index.data(Qt::DisplayRole).toString();
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignVCenter|Qt::ElideRight, text);
    painter->restore();
}

void albumDelegate::drawAlbumDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect,  const QModelIndex & index ) const
{
    rect.setY(rect.y()+10);
    painter->save();
    QFont f=option.font;
    f.setBold(true);
    painter->setFont(f);
    QString text=index.data(Qt::DisplayRole).toString();
    text=text.trimmed();
    if(text.isEmpty())
    {
        painter->setOpacity(0.5);
        text=tr("Uknown album");
    }
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignTop, text);
    painter->restore();
}
