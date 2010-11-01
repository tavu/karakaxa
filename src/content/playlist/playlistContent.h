#ifndef PLAYLIST_CONTENT_H
#define PLAYLIST_CONTENT_H

#include<player.h>
#include<KToolBar>
#include<KIcon>
#include<QStackedWidget>

#include"smartPlaylist.h"
class playlistContent :public abstractContent
{
//      Q_OBJECT
public:
    playlistContent(QWidget *parent=0);
    QString name() const;
    void update(const int n);

private:

    QWidget *buttonWidget;

    KToolBar *toolBar;
// 	 KToolBar *toolBar1;
// 	 KToolBar *toolBar2;

    QAction *backAction;
    QAction *forwardAction;
    QStackedWidget *stack;

    QTreeView *treeV;
    QTreeView *trackV;

    smartPlaylist *smartPl;

    //functions
// 	  void buttonInit();
    void toolBarInit();

    void smartInit();
};

#endif
