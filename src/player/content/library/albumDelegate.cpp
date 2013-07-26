#include"albumDelegate.h"

#include<QApplication>
#include<views/decoration/decoration.h>
#include<QPainter>
#include <QHeaderView>
#include<views/models/urlRole.h>

#define ALBUM_SIZE 100
#define HEADER_SIZE 20
#include<QDebug>

albumDelegate::albumDelegate(QAbstractItemView *parent) :views::editorDelegate(parent)
{
}

void albumDelegate::paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{    
    painter->save();
    QRect r=option.rect;
    
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    drawDisplay(painter,&option,r,index);
    painter->restore();
}

void albumDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem *option, QRect& rect,const QModelIndex &index) const
{
//     painter->save();
    const QStyleOptionViewItemV2 *opt=static_cast<const QStyleOptionViewItemV2 *>(option);
    if(!(opt->features & QStyleOptionViewItemV2::HasDisplay) )
        return;
    
    painter->setFont(option->font);
    rect.setWidth(rect.width()-2);
    rect.setX(rect.x()+5);
    QString text=index.data(Qt::DisplayRole).toString();
    
//     QString     
    text=option->fontMetrics.elidedText(text, Qt::ElideRight, rect.width());
    
    painter->drawText( rect,option->displayAlignment, text);
    
}

void albumDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column()==Basic::RATING)
    {
        QRect r=option.rect;
        r.adjust(1,1,-1,-1);
        editor->setGeometry(r);
        return ;
    }
    views::editorDelegate::updateEditorGeometry(editor, option, index);
}
