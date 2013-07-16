#ifndef ARTISTDELEGATE_H
#define ARTISTDELEGATE_H
#include <qstyleditemdelegate.h>

class artistDelegate :public QStyledItemDelegate
{
    public:
	artistDelegate(QObject *parent=0);
        virtual QSize       sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    protected:
	void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;
};
#endif