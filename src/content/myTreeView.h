#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include<QTreeView>
#include <QModelIndex>
#include<QMouseEvent>
#include<QApplication>
#include<KUrl>
#include<QMenu>
#include"treeViewDelegate.h"
#include"treeViewHeader.h"
// #include"editTrack.h"
class myTreeView :public QTreeView
{
    Q_OBJECT
public:

    myTreeView(QWidget *parent=0,QString name=QString());

    virtual void	setModel ( QAbstractItemModel * model );

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void setRatingColumn(const int n);
    virtual int ratingColumn() const;
    virtual void setNotHide(int n);
    virtual int notHide();


protected:
    QPoint startPos;
    QMenu *menu;
    treeViewDelegate *delegate;

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void performDrag();
    virtual void createMenu();
    virtual void contextMenuEvent(QContextMenuEvent *e);


private:
    //actions
    QAction *append;
    QAction *edit;
    QAction *delet;
    QAction *editTr;

private slots:
    virtual void fileEdit();

public slots:
    virtual void writeSettings();
    virtual void readSettings();
};
#endif
