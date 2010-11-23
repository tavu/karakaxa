#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include <QStandardItemModel>
#include"smartPlaylistCreator.h"
class smartPlaylist :public QObject
{
    Q_OBJECT
public:
    smartPlaylist(QTreeView *treeV,QTreeView *trackV,KToolBar *tb);
    ~smartPlaylist();
// 	  trackView();
// 	  treeView();
// 	  KToolBar* toolBar();

private:
    KToolBar *tb;
    QToolBar *toolBar;
    QStandardItemModel *model;

    QTreeView *treeV;
    QTreeView *trackV;


private slots:
    void addPl();
    void newPl(QString,QString);

public slots:
    void start();
};

#endif
