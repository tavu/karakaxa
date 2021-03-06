#ifndef NPLDELEGATE_H
#define NPLDELEGATE_H

#include<QStyledItemDelegate>
#include<QLabel>
#include<core.h>
#include<QFrame>
class nplDelegate :public QStyledItemDelegate
{
    public:
        nplDelegate(QObject * parent = 0 );
        void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        QRect drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;

    protected:
        void drawContent(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif
