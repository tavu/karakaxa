#ifndef FOLDERCONTENT_h
#define FOLDERCONTENT_h

#include<QFileSystemModel>
#include<QTreeView>
#include<QHeaderView>
#include<QVBoxLayout>
#include<QSortFilterProxyModel>
#include <kfileplacesmodel.h>
#include<KUrlNavigator>

#include<core.h>
#include<views.h>
#include <QToolBar>
#include<QListView>
#include<KToolBar>
#include<KDirModel>
// #include"folderProxyModel.h"
#include"myFileSystemModel.h"
// #include <kfileplacesmodel.cpp>
class folderContent :public core::abstractContent
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
    views::treeView *view;
//     treeViewHeader *viewHeader;
    KUrlNavigator *navigator;


//     KToolBar *toolBar;
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
    void showUrl(KUrl);
    

    
};

#endif
