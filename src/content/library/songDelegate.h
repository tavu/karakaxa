#ifndef SONGDELEGATE_H
#define SONGDELEGATE_H

#include<QStyledItemDelegate>
#define ITEM_HEIGHT 20
class songDelegate :public QStyledItemDelegate
{
//      Q_OBJECT
public:
    songDelegate(QObject * parent = 0 );
    virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

private:
    void drawStar(QPainter *painter,QRect rect,int num) const;

// 	  mutable int ITEM_HEIGHT;

};

#endif
