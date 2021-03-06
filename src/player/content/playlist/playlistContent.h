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
#include<views/models/libraryModel/tagItemHead.h>
#include<views/models/treeView.h>
#include<views/decoration/decoration.h>
#include<database/queries/provider/queryProvider.h>


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
    
        QAction		            *searchAction;
        KLineEdit 		        *searchLine;
        
        QDomDocument 		    doc;

        bool			        needUpdate;
        inline void             toolBarInit();
        inline void             plMenu(standardItem *item);
        inline void             smMenu(standardItem *item);

//         database::queryProvider	    *quer;
        views::tagItemHead	*smItem;

        QByteArray              plState;
        QByteArray              smpState;

        void                    readSettings();
	  
    public slots:
        void back();
        void forward();
        void search();
        void activationSlot(QModelIndex in);

        void addFolderSlot();
        void createSmpSlot();
        void editSmpSlot();
        void removeSlot();
        void renameFolderSlot();
        void writeSettings();
        void contextMenuSlot(QModelIndex index);
        void contextMenuForTracks(QModelIndex index, QModelIndexList list);
        standardItem* head(standardItem* item);
// //     bool quer();
// //     void quer();
};

#endif
