#ifndef PLAYLIST_CONTENT_H
#define PLAYLIST_CONTENT_H

#include<core.h>
#include<models/filePlaylistModel.h>
#include<viewsFunc.h>

#include<KIcon>
#include<QStackedWidget>
#include<QAction>

#include"smartPlaylistCreator/smartPlaylistCreator.h"

// #include"myStandardModel.h"
#include"playlistItem.h"
#include"folderItem.h"
#include"items.h"
#include"smplaylistItem.h"
#include<KLineEdit>
#include<core.h>
#include<QSortFilterProxyModel>
#include<views.h>
#include<queries/fileQueryGrt.h>


class playlistContent :public core::abstractContent
{
    Q_OBJECT
    public:
        playlistContent(QWidget *parent=0);
        ~playlistContent()
        {
             writeSettings();
        }
        QString name() const;
        void activated(const int n);

        QIcon icon() const
        {
            return views::decor->playListIcon();
        }	  
	  
    private:
        QAction 		        *backAction;
        QAction 		        *forwardAction;
        QStackedWidget       	*stack;

        views::treeView         *treeV;
        views::treeView	        *trackV;
        views::filePlaylistModel  	*plModel;
        standardModel	        *smpModel;

        standardModel	        *treeModel;
        playlistFolder	        *plHead;
        folderItem		        *smHead;

        QSortFilterProxyModel	*proxyM;
        QSortFilterProxyModel	*trackProxy;

        QLabel 		            iconL;
        QLabel		            textL;
        QString		            textS;

        //actions
        QAction 		        *removeAction;
        QAction		            *addFolderAction;
        QAction		            *createSmpAction;
        QAction		            *editSmpAction;
        QAction 		        *renameAction;
    
        QAction		            *searchAction;

        KLineEdit 		        *searchLine;

        QDomDocument 		    doc;

        bool			        needUpdate;
        void 			        toolBarInit();

        database::filesQueryGrt	    *quer;
        views::trackModelItem	*smItem;

        QByteArray              plState;
        QByteArray              smpState;

        void                    readSettings();
	  
    public slots:
        void back();
        void forward();
        void search();
        void activationSlot(QModelIndex in);
        void dataChanged(QModelIndex,QModelIndex);

        void addFolderSlot();
        void createSmpSlot();
        void editSmpSlot();
        void removeSlot();
        void renameFolderSlot();
        void writeSettings();
        void contextMenuSlot(QModelIndex index);
        void contextMenuForTracks(QModelIndex index, QModelIndexList list);
        standardItem* head(standardItem* item);
};

#endif
