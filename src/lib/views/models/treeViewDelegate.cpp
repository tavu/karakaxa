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
#include"../editors/ratingEditor.h"
#include<QDebug>
#include<QStylePainter>

#include<QModelIndexList>
Q_DECLARE_METATYPE(QModelIndexList)

views::treeViewDelegate::treeViewDelegate(QObject *parent)    
    :QStyledItemDelegate(parent),    
    rating(-1),
    ITEM_HEIGH(18),
    FONT_SIZE(11),
    editorFactory(0),
    _paintValidRole(true)
{
  font.setPointSize(FONT_SIZE);            
  pen.setWidth(2);
}

void views::treeViewDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
     
	
	painter->setOpacity(0.8);    
     pen.setWidth(2);
     pen.setColor(option.palette.window().color() );
     painter->setPen(pen);
		
	painter->drawLine(option.rect.topRight(),option.rect.bottomRight());
	
   
	painter->restore();
    
	painter->save();
    
     painter->setFont(font);

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

//     painter->restore();
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
	 
	 if(_paintValidRole && index.data(VALID_ROLE).toInt()!=0 )
	 {
		painter->setOpacity(0.5);
	 }
	 painter->drawText( r,Qt::AlignLeft|Qt::AlignVCenter, text);
    }
    painter->restore();
}


QWidget* views::treeViewDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(editorFactory!=0)
    {
	   QWidget *w=editorFactory->createEditor(index,parent);
	   if(index.column()==rating)
	   {
// 		  w->setPixmapSize(sizeHint(option,index).height());
		  connect(w,SIGNAL(valueChanged(QVariant) ),this, SLOT(commitEditor()));
	   }
	   return w;
    }
    else if(index.column()==rating)
    {
	   ratingWidget *w=new  ratingWidget(parent);
	   w->setPixmapSize(sizeHint(option,index).height());
	   connect(w,SIGNAL(valueChanged(QVariant) ),this, SLOT(commitEditor()));
	   return w;	
    }
    return QStyledItemDelegate::createEditor(parent,option,index);    
}

void views::treeViewDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{

      tagEditor *e= qobject_cast<tagEditor*>(editor);  	
      if(e!=0)
      {
	  e->setValue(index.data() );
      }
      else 
      {	  
	  QStyledItemDelegate::setEditorData(editor,index);
      }
}

QSize views::treeViewDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{       
//     QSize ret=QStyledItemDelegate::sizeHint ( option,index );
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


void views::treeViewDelegate::setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const
{    
    if(editorFactory!=0 )
    { 	
	  tagEditor *e= static_cast<tagEditor*>(editor);     
	  qDebug()<<"seting data";		    	
	  QVariant  v=property("modelList");	  	  
	
	   QModelIndexList list=qvariant_cast<QModelIndexList>(v);      
	   
// 	   qDebug()<<list.at(0).data(URL_ROLE).toUrl();
	   editorFactory->setModelData(e,model,index,list);
    }
    else if(index.column()==ratingColumn() )
    {
	tagEditor *e= static_cast<tagEditor*>(editor);     
	qDebug()<<"seting data";
	model->setData(index,e->value(),Qt::EditRole);
    }
    else
    {
	QStyledItemDelegate::setModelData(editor,model,index);
// 	model->setData(index, QVariant(e->value() ) );
    }   
}

void views::treeViewDelegate::setRatingColumn(const int n)
{
    rating=n;
}

int views::treeViewDelegate::ratingColumn() const
{
    return rating;
}

void views::treeViewDelegate::commitEditor()
{
     QWidget *editor = qobject_cast<QWidget *>(sender());
     emit commitData(editor);
/*	
    if(editor->tag()!=audioFiles::RATING &&ratingColumn() >= 0)
    {
 	   emit closeEditor(editor);
    }
    */
}

void views::treeViewDelegate::setEditorFactory(views::tagEditorFactory* f)
{
    if(editorFactory!=0)
    {
	   delete editorFactory;
    }
    
    editorFactory=f;
    editorFactory->setParent(this);
    setRatingColumn(f->columnFromTag(audioFiles::RATING) );
}


void views::treeViewDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
//     return ;
    QSize s=sizeHint(option,index);      
    QRect r=option.rect;
    r.setSize(s);
    editor->setFixedSize(s);
}