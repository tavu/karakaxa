#include"nplaylistDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
// #include<player.h>
#include<KIcon>
#include<nowPlayList/nplaylist.h>
#include<views.h>

using namespace core;

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
         
    if(option.state & QStyle::State_MouseOver)
    {
	   int dropIn=property("dropIn").toInt();
	   if(dropIn!=-1 )
	   {
		  painter->save();
		  QPen pen(views::decor->palette().highlight().color() );	
		  pen.setWidth(2);	
		  painter->setPen(pen);	
		  
		  if(dropIn == 1 )
		  {
			 painter->drawLine(rect.topLeft(),rect.topRight());
		  }
		  else if(dropIn == 2 )
		  {
			 painter->drawLine(rect.bottomLeft(),rect.bottomRight());
		  }
		  painter->restore();
	   }
    }
    else if(index.row()==index.model()->rowCount()-1 )//if its the last index
    {
	   if(property("dropIn").toInt()==3 )
	   {
		  painter->save();
		  QPen pen(views::decor->palette().highlight().color() );
		  pen.setWidth(2);	
		  painter->setPen(pen);
		  painter->drawLine(rect.bottomLeft(),rect.bottomRight());
		  painter->restore();
	   }
	   
    }
    

    int align;
    
    if(index.column()==0)
    {
	   align=Qt::AlignCenter;
	   painter->save();
	   QPen pen(option.palette.linkVisited().color() );	
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
        
    if (npList->isPlaying(index.row() ) )
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
	  painter->restore();
	  return ;
    }
    
    
    nplPointer t=npList->getTrack(index.row() );
    
    if(!t->isValid() )
    {
	 painter->setOpacity(0.5);
    }
    
//     QApplication::style()->drawItemText(painter,rect,align,QApplication::palette (),true,text);

    drawDisplay(painter,option,rect,text,align);
       
    painter->restore();
    
    int dropIn=property("dropIn").toInt();    
}

QSize nplDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(100,20);
}

void nplDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text,int align) const
{
    painter->save();

    text=text.simplified();

    QString elideText=option.fontMetrics.elidedText(text,Qt::ElideRight,rect.width() );
    
    painter->drawText( rect,align|Qt::ElideRight, elideText,&rect);
    painter->restore();
}
