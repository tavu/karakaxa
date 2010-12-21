#include"treeViewDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
#include<player.h>
#include<KIcon>
#include<QFontMetrics>
#include<trackView.h>
using namespace player;

#define ITEM_SIZE 20
// #define FONT_SIZE 9
#include<QPixmap>
#include <kicon.h>
#include <kiconeffect.h>
#include <QVariant>

#include<QStyle>

#include<QStylePainter>
treeViewDelegate::treeViewDelegate(QObject *parent)    
    :QItemDelegate(parent),    
    rating(-1),
    ITEM_HEIGH(17),
    FONT_SIZE(15)
{
  ratingPainter.setEnabled( true );
  ratingPainter.setIcon(KIcon("favorites") );
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
	painter->restore();
        return;
    }

    QRect r=option.rect;
    r.setWidth(r.width()-4);
    r.setX(r.x()+2);

    painter->restore();
    QPixmap pic=decoration(option,index);

    if (!pic.isNull() )
    {
        QApplication::style()->drawItemPixmap(painter,option.rect,Qt::AlignLeft,pic );
        r.setWidth(r.width()-pic.width());
        r.setX(r.x()+pic.width());
    }
    QString text = option.fontMetrics.elidedText(index.data(Qt::DisplayRole).toString(),Qt::ElideRight,r.width() );
    painter->drawText( r,Qt::AlignLeft, text);

}

QWidget* treeViewDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column()==rating)
    {
	player::starWidget *w=new  player::starWidget(parent);
	w->setPixmapSize(sizeHint(option,index).height());
	connect(w,SIGNAL(ratingChanged(int) ),this, SLOT(commitEditor()));
	return w;
	
    }    
    return QItemDelegate::createEditor(parent,option,index);    
}

void treeViewDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
     if(index.column()==rating)
     {
	starWidget *s=static_cast<starWidget*>(editor);
	s->setRating(index.data().toInt() );
     }
     QItemDelegate::setEditorData(editor,index);
}

QSize treeViewDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{       
    QSize ret=QItemDelegate::sizeHint ( option,index );
    return ret;
    
    
    ret.setHeight(ITEM_HEIGH);
    return ret;
    return QSize(ITEM_SIZE,ITEM_SIZE);
}

int treeViewDelegate::itemHeigh() const
{
    return ITEM_HEIGH;
}

void treeViewDelegate::setItemHeigh(int k)
{
    ITEM_HEIGH=k;
}


void treeViewDelegate::setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const
{
    if (index.column() == rating) 
    {
        player::starWidget *s = qobject_cast<player::starWidget *>(editor);        
	model->setData(index, QVariant(s->rating() ) );
    } 
    else 
    {
        QItemDelegate::setModelData(editor, model, index);
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

	case QVariant::Pixmap:        pixmap = qvariant_cast<QPixmap>(value);
	    break;


	default:
	    pixmap = QPixmap();
    }
 
    return pixmap;
}

QPixmap treeViewDelegate::toPixmap(const QStyleOptionViewItem &option, const QIcon &icon) const
{
    QIcon::Mode mode   = option.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled;
    QIcon::State state = option.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
    const QSize size = icon.actualSize(option.decorationSize, mode, state);
    return icon.pixmap(size, mode, state);
}

void treeViewDelegate::commitEditor()
{
    player::starWidget *editor = qobject_cast<player::starWidget *>(sender());
    emit commitData(editor);
}