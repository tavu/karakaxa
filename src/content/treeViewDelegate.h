#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include<QItemDelegate>
class treeViewDelegate :public QItemDelegate
{

    public:
	treeViewDelegate(QObject * parent = 0 );
	virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	int itemHeigh() const;
	void setItemHeigh(int k);
	virtual void setRatingColumn(const int n);
	int ratingColumn() const;
    private:
	void drawStar(QPainter *painter,QRect rect,int num) const;
	int rating;

	QPixmap decoration(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QPixmap toPixmap(const QStyleOptionViewItem &option, const QIcon &icon) const;
      
	
	int ITEM_HEIGH;
	QSize _sizeHint;
};

#endif
