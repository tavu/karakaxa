#ifndef ALBUM_DELEGATE_H
#define ALBUM_DELEGATE_H

#include<views/models/editorDelegate.h>

class albumDelegate :public views::editorDelegate
{
    public:
        albumDelegate(QAbstractItemView *parent=0);        
        
    protected:
        void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
        void drawDisplay(QPainter* painter, const QStyleOptionViewItem *option, QRect& rect,const QModelIndex & index ) const;
        void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
        
};

#endif