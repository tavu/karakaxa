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
#include"../editors/editMultFiles.h"
#include<QDebug>
#include<QStylePainter>
#include<QMetaProperty>

#include<QModelIndexList>
Q_DECLARE_METATYPE(QModelIndexList)

views::treeViewDelegate::treeViewDelegate(QAbstractItemView *parent)
    :QStyledItemDelegate(parent),    
    ITEM_HEIGH(18),
    FONT_SIZE(11)
{
    font.setPointSize(FONT_SIZE);            
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

    QAbstractItemView *view=static_cast<QAbstractItemView*>(parent() );
    if( view->indexWidget(index) !=0 )
    {
        painter->restore();
        return ;
    }

    
    QRect r=option.rect;
    r.setWidth(r.width()-4);
    r.setX(r.x()+2);

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

        if( index.flags() & Qt::ItemIsEnabled  )
        {
            painter->setOpacity(1);
        }
        else
        {
            painter->setOpacity(0.5);
        }
        painter->drawText( r,Qt::AlignLeft|Qt::AlignVCenter, text);
    }
    painter->restore();
}


QWidget* views::treeViewDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{    
    bool b;
    int tag=index.data(TAG_ROLE).toInt(&b);

    if(!b)
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }

    QWidget *w = views::tagEditor::getEditor(tag,parent);
    if(w!=0)
    {
        w->setProperty("tag",tag);
    }
//         connect(w,SIGNAL(valueChanged(QVariant) ),this, SLOT(commitEditor()));

    return w;    
}

void views::treeViewDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
     QStyledItemDelegate::setEditorData(editor,index);
}

QSize views::treeViewDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{       
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
    QModelIndexList list=qvariant_cast<QModelIndexList>(property("modelList") );
    
    if(list.isEmpty() )
    {
        QStyledItemDelegate::setModelData(editor,model,index); 
        return ;
    }

    bool b;
    int tag=index.data(TAG_ROLE).toInt(&b);

    if(!b)
    {
        QStyledItemDelegate::setModelData(editor,model,index); 
        return ;
    }

    QList<audioFiles::audioFile> l;
    int column=index.column();
    foreach(QModelIndex i,list)
    {
        if (i.column()==column )
        {
            l<<audioFiles::audioFile(i.data(URL_ROLE).toUrl() );
        }
    }

    //we dont need a new thread to edit just one item
    if(l.size()==1)
    {
        QStyledItemDelegate::setModelData(editor,model,index);
        return ;
    }

    editMultFiles::editFiles *thr=new editMultFiles::editFiles(parent());
    thr->setFiles(l);
    thr->setTag(tag );

    QByteArray n = editor->metaObject()->userProperty().name();

    //QAbstractItemView *v
    thr->setValue( editor->property(n) );
    QAbstractItemView *view=static_cast<QAbstractItemView*>(parent() );
    connect(thr,SIGNAL(finished()),view,SLOT(reset()));
    thr->start();
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


void views::treeViewDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
//     return ;
    QSize s=sizeHint(option,index);      
    QRect r=option.rect;
    r.setSize(s);
    editor->setFixedSize(s);
}
