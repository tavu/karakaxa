#ifndef SONGVIEW_H
#define SONGVIEW_H

#include"../myTreeView.h"
class songView :public myTreeView
{
    Q_OBJECT
public:
    songView(QWidget *parent=0,QString name=QString("LibraryView"));

private:
    void contextMenuEvent(QContextMenuEvent *e);
    QMenu *menu;

    inline void createMenu();
    //actions
    QAction *append;
    QAction *edit;
    QAction *delet;
    QAction *editTr;

private slots:
    void fileEdit();
};
#endif
