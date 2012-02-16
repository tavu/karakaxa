#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include<QStyledItemDelegate>
#include<QPen>
//#include"../editors/tagEditor.h"
// #include"../playerNamespace/rattingWidget/kratingpainter.h"
// #include "myTreeView.h"

namespace views
{

class treeViewDelegate :public QStyledItemDelegate
{

    Q_OBJECT
    public:
        treeViewDelegate(QAbstractItemView *parent);
        virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        int itemHeigh() const;
        void setItemHeigh(int k);
        QWidget* createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;

        void setEditorData(QWidget *editor,const QModelIndex &index) const;
        void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const;
	
    private:
        int rating;
        void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/* index */) const;
	
        int ITEM_HEIGH;
//         int FONT_SIZE;
        QSize _sizeHint;
//         QFont font;
//         mutable QPen pen;
//         bool _paintValidRole;
	
    private slots:
        void commitEditor();
};//class

};//namespace
#endif
