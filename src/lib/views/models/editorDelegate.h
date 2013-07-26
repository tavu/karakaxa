#ifndef EDITOR_DELEGATE_H
#define EDITOR_DELEGATE_H
#include <QStyledItemDelegate>

namespace views
{
class editorDelegate :public QStyledItemDelegate
{
    Q_OBJECT
    public:
        editorDelegate(QAbstractItemView *parent);
        QWidget* createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;

        void setEditorData(QWidget *editor,const QModelIndex &index) const;
        void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const;
    protected:
        void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/* index */) const;
        
    private slots:
        void commitEditor();
};
}
#endif