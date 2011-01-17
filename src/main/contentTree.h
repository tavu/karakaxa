#ifndef CONTENTTREE_H
#define CONTENTTREE_H
#include<QTreeWidget>
class contentTree :public QTreeWidget
{
    Q_OBJECT
public:
    contentTree(QWidget *parent=0) :QTreeWidget(parent) {}
    inline const QSize sizeHint() {
        return QSize(130,200);
    }

    void contextMenuEvent(QContextMenuEvent *e);
};
#endif
