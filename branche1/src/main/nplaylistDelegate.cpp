#include"nplaylistDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
#include<player.h>
#include<KIcon>
using namespace player;
#define FONT_SIZE 10
#define ITEM_SIZE 10

nplDelegate::nplDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
{
}

void nplDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();

    QRect rect=option.rect;
    QFont font=painter->font();
    font.setPointSize(FONT_SIZE);

    painter->setRenderHint(QPainter::Antialiasing, true);

    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    QString text = index.data(Qt::DisplayRole).toString();

    if (npList.isPlaying(index.row() ) )
    {
        if (option.state & QStyle::State_Selected)
        {
            painter->setPen(option.palette.linkVisited().color());
            painter->setBrush(option.palette.linkVisited().color());
        }
        else
        {
            painter->setPen(option.palette.highlight().color());
            painter->setBrush(option.palette.highlight().color());
        }

        font.setBold(true);

        QPolygonF pol;
        pol<<QPoint(10,7.5)<<QPoint(5,12)<<QPoint(5,3);

        pol.translate(option.rect.x(),option.rect.y() );
        painter->drawPolygon(pol,Qt::WindingFill);
        rect.setX(rect.x()+12);

    }
    else if (option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText().color());
    }

    painter->setFont(font);
    QApplication::style()->drawItemText(painter,rect,Qt::AlignLeft,QApplication::palette (),true,text);
//      painter->drawText( option.rect,Qt::AlignLeft, text);
    painter->restore();

}

QSize nplDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(100,20);
}
