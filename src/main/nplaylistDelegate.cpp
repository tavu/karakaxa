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

    int align;
    
    if(index.column()==0)
    {
	align=Qt::AlignCenter;
	painter->save();
	QPen pen(Qt::black );	
	pen.setWidth(1);	  
	painter->setOpacity(0.2);
	painter->setPen(pen);
 	painter->drawLine(rect.topRight(),rect.bottomRight() );
	painter->restore();
    }
    else
    {
      	rect.setX(rect.x()+2);
	align=Qt::AlignVCenter|Qt::AlignLeft;
    }
        
    if (npList.isPlaying(index.row() ) )
    {
        
	if (option.state & QStyle::State_Selected)    
	{
	    painter->setPen(option.palette.link().color());
	    painter->setBrush(option.palette.link().color());
	}
	else    
	{
	    painter->setPen(option.palette.linkVisited().color());
	    painter->setBrush(option.palette.linkVisited().color());
	}
	
        font.setBold(true);

	if( index.column()==0 )
	{
	    align=Qt::AlignVCenter|Qt::AlignLeft;
	    QPolygonF pol;
	    pol<<QPoint(10,7.5)<<QPoint(5,12)<<QPoint(5,3);

	    pol.translate(option.rect.x(),option.rect.y()+2 );
	    painter->drawPolygon(pol,Qt::WindingFill);
	    rect.setX(rect.x()+12);
	}

    }
    else if (option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText().color());
    }
    
    painter->setFont(font);
    if(index.column()==0 && text==QString("0") )
    {
// 	text=QString("-");
	
	  painter->restore();
	  return ;
    }
    nplPointer t=player::npList.getTrack(index.row() );
    
    if(!t->isValid() )
    {
	painter->setOpacity(0.5);
    }
    QApplication::style()->drawItemText(painter,rect,align,QApplication::palette (),true,text);
    
    
//     painter->drawText( option.rect,Qt::AlignVCenter|align, text);
    painter->restore();

}

QSize nplDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(100,20);
}
