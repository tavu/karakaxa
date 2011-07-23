#include"albumDelegate.h"
#include<QApplication>
#include<QPainter>
#include<views.h>
#define TEXT_H 30
albumDelegate::albumDelegate(QObject* parent): QStyledItemDelegate(parent)
{    
}

void albumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );            

    QPixmap pic=views::decor->decorationPixmap(option,index);
    QRect r=option.rect;
    
    r.setY(r.y()+10);
    r.setHeight(r.height()-2*option.fontMetrics.height()-5);
    r.setX(r.x()+10);
    r.setWidth(r.width()-10);   
    
    pic=pic.scaled(r.size(), Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
                           
    QRect shadowR=r;
    QPoint p=r.topLeft();
    p.setX(p.x()+2);
    p.setY(p.y()+2);
    shadowR.moveTopLeft(p);
    QPainterPath shadowPath;
    painter->setRenderHint(QPainter::Antialiasing, true);
    shadowPath.addRoundedRect(shadowR,1,1);
    
    painter->setOpacity(0.5);    
    painter->fillPath(shadowPath,Qt::black);

    painter->setOpacity(1);
    QApplication::style()->drawItemPixmap(painter,r,Qt::AlignCenter,pic );
    
    
    QRect textR=r;
    textR.setY(r.y()+textR.height()+2);
    textR.setHeight(2*option.fontMetrics.height());
    
    QString s=displayText(index.data(),QLocale("UTF-8") );    
    drawDisplay(painter,option,textR,s);        
}

void albumDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,QRect& rect, QString& text) const
{
    painter->save();

    text=text.simplified();
    if(text.isEmpty())
    {
	painter->setOpacity(0.5);
	text=tr("Uknown album");
    }
    
    painter->drawText( rect,Qt::AlignTop|Qt::AlignHCenter|Qt::TextWordWrap|Qt::TextIncludeTrailingSpaces|Qt::ElideRight, text,&rect);
    painter->restore();
}

QWidget* albumDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    return new albumEditor(parent);
}

void albumDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
     albumEditor *e= static_cast<albumEditor*>(editor);
  
	QVariant value = index.model()->data(index, Qt::DecorationRole);	
	
     e->setPixmap(qvariant_cast<QPixmap>(value) );
	e->setText(index.data(Qt::DisplayRole).toString() );
}

void albumEditor::paintEvent(QPaintEvent* event)
{
//     QWidget::paintEvent(event);
    QPainter *painter=new QPainter(this);
           

    
    QRect r=rect();
    
    r.setY(r.y()+10);
    r.setHeight(r.height()-100-5);
    r.setX(r.x()+10);
    r.setWidth(r.width()-10);   
    
    QPixmap pix=pic.scaled(r.size(), Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
                           
    QRect shadowR=r;
    QPoint p=r.topLeft();
    p.setX(p.x()+2);
    p.setY(p.y()+2);
    shadowR.moveTopLeft(p);
    QPainterPath shadowPath;
    painter->setRenderHint(QPainter::Antialiasing, true);
    shadowPath.addRoundedRect(shadowR,1,1);
    
    painter->setOpacity(0.5);    
    painter->fillPath(shadowPath,Qt::black);

    painter->setOpacity(1);
    QApplication::style()->drawItemPixmap(painter,r,Qt::AlignCenter,pix );
    
    
    QRect textR=r;
    textR.setY(r.y()+textR.height()+2);
    textR.setHeight(100);
    
//     QString s=displayText(index.data(),QLocale("UTF-8") );    
//     drawDisplay(painter,option,textR,s); 
    
    painter->drawText( textR,Qt::AlignTop|Qt::AlignHCenter|Qt::TextWordWrap|Qt::TextIncludeTrailingSpaces|Qt::ElideRight, text,&textR);
    
    delete painter;
}

