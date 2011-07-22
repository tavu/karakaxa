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
    
    if (index.row()%2==1)
    {
        painter->save();
        painter->setOpacity(0.2);
        painter->fillRect(option.rect,option.palette.window());
        painter->restore();
    }    
	     
	
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
	   int tag=editorFactory->tagFromIndex(index);
	   qDebug()<<"TAG "<<tag;
	   if(tag>-1)
	   {
		  
		  tagEditor *editor=editorFactory->createEditor(tag,parent);
		  connect(editor,SIGNAL(valueChanged(QVariant) ),this, SLOT(commitEditor()));
		  return editor;
	   }
    }
    else if(index.column()==rating)
    {
	   ratingWidget *w=new  ratingWidget(parent);
	   w->setPixmapSize(sizeHint(option,index).height());
	   connect(w,SIGNAL(valueChanged(QVariant) ),this, SLOT(commitEditor()));
	   return w;	
    }
    return 0;    
}

void views::treeViewDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
     tagEditor *e= static_cast<tagEditor*>(editor);
  
     e->setValue(index.data() );     
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
    tagEditor *e= static_cast<tagEditor*>(editor);
    model->setData(index, QVariant(e->value() ) );
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
//     qDebug()<<"geo";
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
    return ;
    QSize s=sizeHint(option,index);      
    QRect r=option.rect;
    r.setSize(s);
    editor->setFixedSize(s);
//     editor->setFixedHeight(s.height() );
//     editor->setGeometry(option.rect);
}