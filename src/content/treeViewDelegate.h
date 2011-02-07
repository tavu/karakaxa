#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include<QItemDelegate>
#include<kratingpainter.h>
class treeViewDelegate :public QItemDelegate
{

    Q_OBJECT
    public:
	treeViewDelegate(QObject * parent = 0 );
	virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	int itemHeigh() const;
	void setItemHeigh(int k);
	virtual void setRatingColumn(const int n);
	int ratingColumn() const;
	QWidget* createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;
	void setEditorData(QWidget *editor,const QModelIndex &index) const;
	void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const;
    private:
	int rating;

/*	QPixmap decoration(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QPixmap toPixmap(const QStyleOptionViewItem& option, const QIcon& icon, const QModelIndex &index) const;
 */     
	
	int ITEM_HEIGH;
	int FONT_SIZE;
	QSize _sizeHint;
	
	KRatingPainter ratingPainter;
	
    private slots:
      void commitEditor();
};

#endif
