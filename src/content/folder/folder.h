#ifndef FOLDERCONTENT_h
#define FOLDERCONTENT_h
#include<player.h>
#include<QFileSystemModel>
#include<QTreeView>
#include<QHeaderView>
#include<QVBoxLayout>
#include<QSortFilterProxyModel>
#include <kfileplacesmodel.h>
#include<KUrlNavigator>

#include"../treeViewHeader.h"
#include <QToolBar>
#include<QListView>
#include"../myTreeView.h"
#include<KToolBar>
#include<KDirModel>
#include "myFileSystemModel.h"
// #include"folderProxyModel.h"
// #include"myFileSystemModel.h"
// #include <kfileplacesmodel.cpp>
class folderContent :public abstractContent
{
    Q_OBJECT
public:
    folderContent(QWidget *parent=0);
    const QList<QString> getChildren();

    QString name() const;


private:

    myFileSystemModel *model;
    KDirModel *dirModel;
    QSortFilterProxyModel  *proxyM;

    KFilePlacesModel *navigatorModel;
    myTreeView *view;
    treeViewHeader *viewHeader;
    KUrlNavigator *navigator;


    KToolBar *toolBar;
    //actions
    QAction *upAction;
    QAction *backAction;
    QAction *forwardAction;


public slots:

    void writeSettings();
    void readSettings();
    void cd(KUrl);
    void up();
    void back();
    void forward();
    void setDir(const QModelIndex index);
    
  private slots:
    void cleanup();
    

    
};

#endif
