#include"treeViewDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
#include<KIcon>
#include<QFontMetrics>
#include"../decoration/decoration.h"
#include"../ratingWidget/ratingWidget.h"
#include"urlRole.h"
#define ITEM_SIZE 20
// #define FONT_SIZE 9
#include<QPixmap>
#include <kicon.h>
#include <kiconeffect.h>
#include <QVariant>
#include<QStyle>
#include<editMultFiles.h>
#include"../editors/textEditor.h"
#include<QDebug>
#include<QStylePainter>
#include<QMetaProperty>

#include<QModelIndexList>


views::treeViewDelegate::treeViewDelegate(QAbstractItemView *parent)
    :editorDelegate(parent) ,
     ITEM_HEIGH(18)
{

}

void views::treeViewDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setOpacity(0.8);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(option.palette.window().color());
    painter->setPen(pen);
    painter->drawLine(option.rect.topRight(),option.rect.bottomRight());

    painter->restore();

    painter->save();

//     painter->setFont(font);

    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    if (option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText().color());
    }

    QAbstractItemView *view=static_cast<QAbstractItemView*>(parent() );
    if( view->indexWidget(index) !=0 )
    {
        painter->restore();
        return ;
    }


    QRect r=option.rect;
    r.setWidth(r.width()-4);
    r.setX(r.x()+2);

    QPixmap pic=decor->decorationPixmap(option,index);

    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,r,Qt::AlignLeft,pic );
        r.setWidth(r.width()-pic.width());
        r.setX(r.x()+pic.width());
    }

    QVariant var=index.data(Qt::DisplayRole);
    if(!var.isNull() )
    {
        QString text = option.fontMetrics.elidedText(var.toString(),Qt::ElideRight,r.width() );

        if( index.flags() & !Qt::ItemIsEnabled || index.data(DISABLE_ROLE).toBool() || index.data(OPACITY_ROLE).toBool() )
        {
            painter->setOpacity(0.5);
        }
        else
        {
            painter->setOpacity(1);
        }
        painter->drawText( r,Qt::AlignLeft|Qt::AlignVCenter, text);
    }
    painter->restore();
}

QSize views::treeViewDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QSize ret=index.data(Qt::SizeHintRole).toSize();

    if(ret.isEmpty() )
        return QSize(option.rect.width(),ITEM_HEIGH);

    return ret;
}

int views::treeViewDelegate::itemHeigh() const
{
    return ITEM_HEIGH;
}

void views::treeViewDelegate::setItemHeigh(int k)
{
    ITEM_HEIGH=k;
}