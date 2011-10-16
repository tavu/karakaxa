#ifndef NOWPLAYLISTDELEGATE_H
#define NOWPLAYLISTDELEGATE_H

#include<QStyledItemDelegate>
#include<QLabel>
#include<core.h>
#include<QFrame>
class nowPlaylistDelegate :public QStyledItemDelegate
{
public:
    nowPlaylistDelegate(QObject * parent = 0 );
    void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;    

private:
    void drawDropIndicator(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void drawContent(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif
