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
 
//     QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
    if(npList->getPlayingPos()==index.row() )
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
    
    */
}

void  nplDelegate::drawDropIndicator(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
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

void nplDelegate::drawContent(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{    
    painter->save();
    QPixmap pix=views::decor->tagIcon(-1).pixmap(40,40);    
    qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignLeft|Qt::AlignVCenter,pix);
    QRect r=option.rect;
    r.setX(r.x()+40);
    QRect up=r;
    QRect down=r;
    
    //we create two rects with half height each
    up.setBottom(up.y()+up.height()/2);
    down.setTop(up.bottom()+1);
    down.setBottom(down.bottom()-5);
    
    
    nplPointer p=npList->getTrack(index.row() );
    
    int track=p->tag(TRACK).toInt();
    
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
    return QSize(700,45);
}

void nplDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const 
{
    QString elideText=option.fontMetrics.elidedText(text,Qt::ElideRight,rect.width() );
    
    if(option.state & QStyle::State_Selected)
    {
		QPalette pal=option.palette;
		pal.setBrush(QPalette::Text, Qt::white);
    }
    
    QRect r=option.fontMetrics.boundingRect(elideText);
    painter->drawText( rect,Qt::AlignLeft|Qt::AlignVCenter |Qt::ElideRight, elideText,&r);  
}

void nplDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    
    editor->setFixedHeight(option.rect.height());
    
    qDebug()<<"UPE";
}

void nplDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    nplWidget *w=static_cast<nplWidget*>(editor);
    w->updateInfo();
}


nplWidget::nplWidget(QWidget* parent, int row): QFrame(parent)
{
//     setAutoFillBackground(true);
    pointer=npList->getTrack(row);  
    this->row=row;
    qDebug()<<"RR "<<row<<pointer->path();
        
    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    
    QFont font=titleL.font();
    font.setBold(true);
    titleL.setFont(font);
    
    QPalette pal=palette();
    QColor color(Qt::black);
    color.setAlpha(100);
    pal.setColor(QPalette::Text, color);
    artistL.setPalette(pal);
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::StyledPanel|QFrame::Raised);
    f->setFrameShape(QFrame::HLine);
        
    iconL.setPixmap(views::decor->tagIcon(-1).pixmap(40,40) );
    
    QGridLayout  *l=new QGridLayout (this);
    l->addWidget(&iconL,0,0,2,1,Qt::AlignLeft);
    l->addWidget(&trackL,0,1,Qt::AlignLeft);
    l->addWidget(&titleL,0,2,Qt::AlignLeft);
    l->setColumnStretch(2,1);
//     l->addWidget(spacer,0,3);
    l->addWidget(&artistL,1,1,1,-1,Qt::AlignLeft);
    l->addWidget(spacer,2,1,1,-1,Qt::AlignLeft);
    l->addWidget(f,2,0,2,-1);          
//     artistL.setDisabled(true);
    l->setContentsMargins(0,2,0,0);
//     l->setSpacing(0);
    l->setHorizontalSpacing(0);
    l->setVerticalSpacing(0);
//     updateInfo();
    
}

void nplWidget::updateInfo()
{
    int t=pointer->tag(TRACK).toInt();
    
    if(t==0)
    {
	 trackL.hide();
    }
    else
    {
	   trackL.setText(QString::number(t)+" " );
    }
    
    qDebug()<<"title "<<pointer->tag(TITLE);
    
    titleL.setText(pointer->tag(TITLE).toString() );
    QString s=pointer->artist().toString();
    s=s.simplified();
    if(s.isEmpty() )
    {
	   s=QString("Unknown");
    }
    artistL.setText("by "+s);
}
void nplWidget::setPlaying()
{
//  	 setFrameStyle(QFrame::StyledPanel|QFrame::Raised);
//       iconL.setPixmap(views::decor->play().pixmap(30,30));
}

void nplWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
//     QWidget::mouseDoubleClickEvent(event); 
    engine->play(row);
}

QWidget* nplDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    nplWidget *w=new nplWidget(parent,index.row() );
    return w;
}
