#ifndef ALBUM_DELEGATE_H
#define ALBUM_DELEGATE_H

#include<QStyledItemDelegate>

class albumDelegate :public QStyledItemDelegate
{
    public:
        albumDelegate(QObject *parent=0);
        virtual QSize       sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        
         protected:
        void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
        void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect,const QModelIndex & index ) const;
        void drawAlbumDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect,  const QModelIndex & index ) const;
};

#endif