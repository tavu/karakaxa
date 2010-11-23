#include"treeViewDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
#include<player.h>
#include<KIcon>
#include<QFontMetrics>
#include<trackView.h>
using namespace player;
#define FONT_SIZE 9
#include<QPixmap>
#include <kicon.h>
#include <kiconeffect.h>
#include <QVariant>

#include<QStyle>

#include<QStylePainter>
treeViewDelegate::treeViewDelegate(QObject *parent)    
    :QItemDelegate(parent),    
    rating(-1),
    ITEM_HEIGH(15)
{
//     _sizeHint=Q
}

void treeViewDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();

    if (index.row()%2==1)
    {
        painter->save();
        painter->setOpacity(0.1);
        painter->fillRect(option.rect,player::pal.window());
        painter->restore();
    }


    QPen pen;

    pen.setWidthF(1.5);

    painter->setOpacity(0.8);
    pen.setWidth(1);
    pen.setColor(player::pal.window().color() );
    painter->setPen(pen);

    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());

    painter->setOpacity(0.1);
    pen.setWidthF(4);
    pen.setColor(player::pal.window().color() );
    painter->setPen(pen);

    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());

    painter->restore();
    painter->save();

    QFont font=painter->font();
    font.setPointSize(FONT_SIZE);
    painter->setFont(font);

    QFontMetrics fontMetric(font);

    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    if (option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText().color());
    }


    if (index.column()==rating)
    {
        QVariant var=index.data();

        if (!var.isNull() )
        {
            drawStar(painter,option.rect,index.data().toInt() );
        }
        painter->restore();
        return;
    }

    QRect r=option.rect;
    r.setWidth(r.width()-4);
    r.setX(r.x()+2);


//       painter->drawText( r,Qt::AlignLeft, text);


    painter->restore();
    QPixmap pic=decoration(option,index);

    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,option.rect,Qt::AlignLeft,pic );
        r.setWidth(r.width()-pic.width());
        r.setX(r.x()+pic.width());
    }
    QString text = fontMetric.elidedText(index.data(Qt::DisplayRole).toString(),Qt::ElideRight,r.width() );
    painter->drawText( r,Qt::AlignLeft, text);

}

QSize treeViewDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{       
    QSize ret=QItemDelegate::sizeHint ( option,index );
//     ret.setHeight(ITEM_HEIGH);
    return ret;
}

int treeViewDelegate::itemHeigh() const
{
    return ITEM_HEIGH;
}

void treeViewDelegate::setItemHeigh(int k)
{
    ITEM_HEIGH=k;
}


void treeViewDelegate::drawStar(QPainter *painter,QRect rect,int num) const
{
    if (num<0||num>255)
    {
        return ;
    }

    int n=num/25;
    if (num%25>0 && n!=10) 	n++;

    KIcon icon("favorites");
    QPixmap activeStar=icon.pixmap(rect.height());
//     activeStar=activeStar.scaledToHeight(rect.height(),Qt::SmoothTransformation);

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

void treeViewDelegate::setRatingColumn(const int n)
{
    rating=n;
}

int treeViewDelegate::ratingColumn() const
{
    return rating;
}

QPixmap treeViewDelegate::decoration(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QVariant value = index.model()->data(index, Qt::DecorationRole);
    QPixmap pixmap;

    switch (value.type())
    {
    case QVariant::Icon:
        pixmap =  toPixmap(option,qvariant_cast<QIcon>(value));
        break;

    case QVariant::Pixmap:
        pixmap = qvariant_cast<QPixmap>(value);
        break;

//          case QVariant::Color:
//               pixmap = toPixmap(option, qvariant_cast<QColor>(value));
//              break;

    default:
        pixmap = QPixmap();
    }

    /*
        if (!pixmap.isNull())
        {
            // If the item is selected, and the selection rectangle only covers the
            // text label, blend the pixmap with the highlight color.
            if (!option.showDecorationSelected && option.state & QStyle::State_Selected)
            {
                QPainter p(&pixmap);
                QColor color = option.palette.color(QPalette::Highlight);
                color.setAlphaF(0.5);
                p.setCompositionMode(QPainter::CompositionMode_SourceAtop);
                p.fillRect(pixmap.rect(), color);
            }

            // Apply the configured hover effect
            if ((option.state & QStyle::State_MouseOver) && index.column() == KDirModel::Name)
                pixmap = applyHoverEffect(pixmap);
        }
    */
    return pixmap;
}

QPixmap treeViewDelegate::toPixmap(const QStyleOptionViewItem &option, const QIcon &icon) const
{
    QIcon::Mode mode   = option.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled;
    QIcon::State state = option.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
    const QSize size = icon.actualSize(option.decorationSize, mode, state);
    return icon.pixmap(size, mode, state);
}
