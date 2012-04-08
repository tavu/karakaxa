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
#include"folderProxyModel.h"
#include"myFileSystemModel.h"
#include<KLineEdit>
#include<models/filePlaylistModel.h>
//#include "folderView.h"
// #include <kfileplacesmodel.cpp>

class folderContextMenu;

class folderContent :public core::abstractContent
{
    Q_OBJECT
    public:
        folderContent(QWidget *parent=0);
        ~folderContent()
        {
            writeSettings();
        }
        const QList<QString> getChildren();

        QString name() const;

        QIcon icon() const
        {
            return KIcon("folder-sound");
        }


    private:
        void                loaded();
        void                unloaded();        
        void                readSettings();
        void                saveStates();

        void                goToPl(KUrl url);
        void                goToFolder(KUrl url);

        KToolBar            *folderToolBar;
        QAction *           folderToolBarAction;
        
        folderContextMenu   *m;
        myFileSystemModel   *model;
        KDirModel           *dirModel;
        folderProxyModel    *proxyM;

        KFilePlacesModel    *navigatorModel;
        views::treeView     *view;    
        KUrlNavigator       *navigator;

        //actions
        QAction             *upAction;
        QAction             *backAction;
        QAction             *forwardAction;
        QAction             *newPlAction;

        KLineEdit           *searchLine;
        views::filePlaylistModel      *playlistM;

        QByteArray          folderModelState;
        QByteArray          playlistMState;
        
    public slots:
        void cd(KUrl);
        void up();
        void back();
        void forward();
        void newPl();
        void setDir(const QModelIndex index);

    private slots:
        void cleanup();
        void writeSettings();
        void showUrl(KUrl);
        void showContexMenuSlot(QModelIndex index, QModelIndexList list);
        void edit();
};

class folderContextMenu :public core::abstractMenu
{
    Q_OBJECT
    public:
	
        folderContextMenu(folderContent *c)
        :abstractMenu(), f(c) , _show(true)
        {
            act=new QAction(KIcon("folder"),tr("go to folder"),this);
            connect(act,SIGNAL(triggered() ),this,SLOT(cd() ) );
        }
        ~folderContextMenu()
        {
            delete act;
        }

        virtual bool canShow()
        {
            if(url().isLocalFile() && _show  )
            {
                return true;
            }

            return false;
        }

        QAction* action()
        {
            return act;
        }

        void setShow(bool b)
        {
            _show=b;
        }
    
    private:      
        folderContent *f;
        QAction *act;
        bool _show ;

    private slots:
        void cd()
        {
            f->cd(core::folder(url().toLocalFile()) );
            core::contentHdl->setCurrentContent(f);
        }
	
};








#endif
