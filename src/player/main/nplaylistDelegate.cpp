#include"nplaylistDelegate.h"
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

nplDelegate::nplDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
{
}

void nplDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{    
    
    painter->setRenderHint(QPainter::Antialiasing, true);
 
    if(npList()->getPlayingPos()==index.row() )
    {
// 	   painter->save();
	   QPointF a(option.rect.topLeft() );
	   QPointF b(option.rect.bottomLeft() );
	   a.setY(a.y()+option.rect.height()/3);
	   b.setY(b.y()-option.rect.height()/3);

       
	   QLinearGradient grad( a,b );            
	   if (option.state & QStyle::State_Selected)
	   {
 		  grad.setColorAt( 0.0, views::decor->palette().highlight().color().lighter(110) );
 		  grad.setColorAt( 0.8, views::decor->palette().highlight().color().lighter(100) );
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
	   //painter->setOpacity(1);
 	   painter->fillRect(option.rect,grad );

	   QPen pen(Qt::white);
	   pen.setWidth(3);
	   painter->setPen(pen);
 	   //painter->setOpacity(1);
   	   painter->drawRoundedRect (option.rect, 3,3);
       
// 	   painter->restore();
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

    return ;
}

void nplDelegate::drawContent(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
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
    if(p.isNull() )
    {
        core::status->addErrorP("nplDelegate:nplPointer is null");
        painter->restore();
        return ;
    }
    
    int track=p->tag(TRACK).toInt();
    
    if(track!=0)
    {
	   QString s=QString::number(track);
	   s.append(" -  ");
	   QRect r=drawDisplay(painter,option,up,s);   
 	   //painter->drawText( up,Qt::AlignLeft|Qt::AlignVCenter,s,&r);
 	   up.setX(up.x()+r.width() );
    }

    QFont f=option.font;
    f.setBold(true);
    painter->setFont(f);
    QString s=p->tag(TITLE).toString();
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



QSize nplDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
//     return QSize();
    return QSize(10000,45);
}

QRect nplDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const
{
    if (option.state & QStyle::State_Selected)
    {
        painter->setPen(Qt::white);
    }
    else
    {
        painter->setPen(Qt::black);
    }
    QString elideText=option.fontMetrics.elidedText(text,Qt::ElideRight,rect.width() );
    
    QRect r=option.fontMetrics.boundingRect(elideText);
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignVCenter |Qt::ElideRight, elideText,&r);

    return r;    
}

