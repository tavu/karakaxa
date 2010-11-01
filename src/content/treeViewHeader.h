#ifndef SONGHEADER_H
#define SONGHEADER_H
#include<QHeaderView>
#include<QContextMenuEvent>
#include<QMenu>
#include"QTreeView"
#include<player.h>
// #include <Q3PopupMenu>
class treeViewHeader :public QHeaderView
{
    Q_OBJECT
public:
    treeViewHeader(QTreeView *parent=0);
    ~treeViewHeader();


// 	 virtual int sectionSizeHint(int column);
    void setNotHide(int n);
    int notHide();

// 	 int sectionSizeHint(int s) const;

private:
    QMenu *menu;
    QAction *hide;
    QAction *selectColumn;

    QTreeView *treeV;

    int notHid;
    int columnClicked;

    void mousePressEvent(QMouseEvent *e);
    void createMenu();

protected slots:
    void hideClickedColumn();
    virtual void selectColumnW();
    void toggleHideColumn(int);

};

#endif
