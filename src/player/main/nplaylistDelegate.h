#ifndef NPLDELEGATE_H
#define NPLDELEGATE_H

#include<QStyledItemDelegate>

class nplDelegate :public QStyledItemDelegate
{
public:
    nplDelegate(QObject * parent = 0 );
    virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif
