#ifndef ALBUMDELEGATE_H
#define ALBUMDELEGATE_H
#include <qstyleditemdelegate.h>

class albumDelegate :public QStyledItemDelegate
{
    public:
	albumDelegate(QObject *parent=0);
    
    protected:
	void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;
	int sideSpace;
	int topSpace;
};
#endif