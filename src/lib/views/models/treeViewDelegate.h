#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include<QStyledItemDelegate>
#include"editorDelegate.h"
namespace views
{

class treeViewDelegate :public editorDelegate
{

    Q_OBJECT
    public:
        treeViewDelegate(QAbstractItemView *parent);
        virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        int itemHeigh() const;
        void setItemHeigh(int k);
	
    private:
        int rating;
	
        int ITEM_HEIGH;
        QSize _sizeHint;
};//class

};//namespace
#endif
