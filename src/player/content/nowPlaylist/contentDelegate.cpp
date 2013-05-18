#include"contentDelegate.h"
#include<QPainter>
#include<QApplication>
#include<QPolygonF>
// #include<player.h>
#include<KIcon>
#include<nowPlayList/nplaylist.h>
#include<views.h>
#include<QGridLayout>

#include<qdrawutil.h>
#include<QApplication>
using namespace core;

#define FONT_SIZE 10
#define ITEM_SIZE 10

nowPlaylistDelegate::nowPlaylistDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
{
}

void nowPlaylistDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{    
    
    painter->setRenderHint(QPainter::Antialiasing, true);
 
//     QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    if(npList()->getPlayingPos()==index.row() )
    {
	   painter->save();
	   QPointF a(option.rect.topLeft() );
	   QPointF b(option.rect.bottomLeft() );
	   a.setY(a.y()+option.rect.height()/3);
	   b.setY(b.y()-option.rect.height()/3);
		    
	   QLinearGradient grad( a,b );            
	   if (option.state & QStyle::State_Selected)
	   {
 		  grad.setColorAt( 0.0, views::decor->palette().highlight().color().lighter(150) );        
 		  grad.setColorAt( 0.8, views::decor->palette().highlight().color().lighter(140) );
	   }
	   else if(option.state & QStyle::State_MouseOver)
	   {
		  grad.setColorAt( 0.0, views::decor->palette().highlight().color().lighter(130) );        
		  grad.setColorAt( 0.7, views::decor->palette().highlight().color().lighter(120) );
	   }
	   else
	   {
 		  grad.setColorAt( 0.0, views::decor->palette().highlight().color().lighter() );        
 		  grad.setColorAt( 0.7, views::decor->palette().highlight().color().lighter(130) );
	   }
  // 	 grad.setSpread(QLinearGradient::ReflectSpread);
	   painter->setOpacity(1);
 	   painter->fillRect(option.rect,grad );

	   QPen pen(Qt::white);
	   pen.setWidth(3);
	   painter->setPen(pen);
 	   painter->setOpacity(1);
   	   painter->drawRoundedRect (option.rect, 3,3);
	   
	   
	   
	   painter->restore();
    }
    else
    {
	   QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
	   painter->save();
	   painter->setOpacity(0.4);
	   qDrawShadeLine(painter,option.rect.bottomLeft(),option.rect.bottomRight(),option.palette);
	   painter->restore();
    }
    
    drawContent(painter,option,index);
    
    drawDropIndicator(painter,option,index);
    
    return ;
/*    
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
        
    if (npList()()->isPlaying(index.row() ) )
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
    
    
    nplPointer t=npList()()->getTrack(index.row() );
    
    if(!t->isValid() )
    {
	 painter->setOpacity(0.5);
    }
    
//     QApplication::style()->drawItemText(painter,rect,align,QApplication::palette (),true,text);

    drawDisplay(painter,option,rect,text,align);
       
    painter->restore();
    
    int dropIn=property("dropIn").toInt();    
    
    */
}

void  nowPlaylistDelegate::drawDropIndicator(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    painter->save();
    int dropIn=property("dropIn").toInt();         
    if(option.state & QStyle::State_MouseOver )
    {
	   if(dropIn!=-1 )	
	   {
		  QPen pen(views::decor->palette().highlight().color() );	
		  pen.setWidth(3);			
		  painter->setPen(pen);	
			 
		  if(dropIn == 1 )
		  {
			 painter->drawLine(option.rect.topLeft(),option.rect.topRight());
		  }
		  else if(dropIn == 2 )		
		  {
			 painter->drawLine(option.rect.bottomLeft(),option.rect.bottomRight());
		  }
	   }
    }
    else if(dropIn==3 && index.row()==index.model()->rowCount()-1 )
    {
	   QPen pen(views::decor->palette().highlight().color() );	
	   pen.setWidth(3);		
	   painter->setPen(pen);
	   painter->drawLine(option.rect.bottomLeft(),option.rect.bottomRight());		   
    }    
    painter->restore();
}

void nowPlaylistDelegate::drawContent(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{    
    painter->save();
    QPixmap pix=views::decor->tagIcon(-1).pixmap(40,40);    
    qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignLeft|Qt::AlignVCenter,pix);
    QRect r=option.rect;
    r.setX(r.x()+40);
    r.setWidth(r.width()-3);
    QRect up=r;
    QRect down=r;
    
    //we create two rects with half height each
    up.setBottom(up.y()+up.height()/2);
    down.setTop(up.bottom()+1);
    down.setBottom(down.bottom()-5);
    
    
    nplPointer p=npList()->getTrack(index.row() );
    
    int track=p->tag(Basic::TRACK).toInt();
    
    if(track!=0)
    {
	   QString s=QString::number(track);
	   s.append(" -  ");
	   QRect r=option.fontMetrics.boundingRect(s);
 	   painter->drawText( up,Qt::AlignLeft|Qt::AlignVCenter,s,&r);
 	   up.setX(up.x()+option.fontMetrics.boundingRect(s).width() );
    }

    QFont f=option.font;
    f.setBold(true);
    painter->setFont(f);
    QString s=p->tag(Basic::TITLE).toString();
    s=s.simplified();
    drawDisplay(painter,option,up,s);    
    
    painter->setFont(option.font);
    s=p->artist().toString();
    
    s=s.simplified();
    if(!s.isEmpty() )
    {
	   s.prepend("by ");
	   painter->setOpacity(0.6);
	   drawDisplay(painter,option,down,s);
    }
    
    painter->restore();
}



QSize nowPlaylistDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
//     return QSize();
    return QSize(10000,45);
}

void nowPlaylistDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const 
{
    QString elideText=option.fontMetrics.elidedText(text,Qt::ElideRight,rect.width() );    
    
    QRect r=option.fontMetrics.boundingRect(elideText);
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignVCenter |Qt::ElideRight, elideText,&r);  
}

