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
}

void treeViewDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();

    if (index.row()%2==1)
    {
        painter->save();
        painter->setOpacity(0.2);
        painter->fillRect(option.rect,player::pal.window());
        painter->restore();
    }
    
    QPen pen;

//     pen.setWidthF(1.5);

    painter->setOpacity(0.8);
    pen.setWidth(1);
    pen.setColor(player::pal.window().color() );
    painter->setPen(pen);

    QPointF up(option.rect.topRight().x(),option.rect.topRight().y() );
    QPointF down(option.rect.bottomRight().x(),option.rect.bottomRight().y() );
    
    painter->drawLine(up,down);

    painter->setOpacity(0.1);
    pen.setWidthF(4);
    pen.setColor(player::pal.window().color() );
    painter->setPen(pen);

    painter->drawLine(up,down);

    painter->restore();
    painter->save();

    QFont font=painter->font();
    font.setPointSize(FONT_SIZE);
    painter->setFont(font);

//     QFontMetrics fontMetric(font);

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
    QPixmap pic=player::decor.decorationPixmap(option,index);

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
	text=text.simplified();
	painter->drawText( r,Qt::AlignLeft|Qt::AlignVCenter, text);
    }
//     style()->drawItemText(painter,r,Qt::AlignLeft|Qt::AlignVCenter,option.palette,true,text);

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

void treeViewDelegate::commitEditor()
{
    player::starWidget *editor = qobject_cast<player::starWidget *>(sender());
    emit commitData(editor);
}