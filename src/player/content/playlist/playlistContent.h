#ifndef PLAYLIST_CONTENT_H
#define PLAYLIST_CONTENT_H

#include<core.h>
#include<views.h>

#include<KIcon>
#include<QStackedWidget>
#include<QAction>

#include"playlistModel.h"
#include"smartPlaylistCreator/smartPlaylistCreator.h"

// #include"myStandardModel.h"
#include"playlistItem.h"
#include"folderItem.h"
#include"items.h"
#include"smplaylistItem.h"
#include<KLineEdit>
#include<core.h>
#include<QSortFilterProxyModel>


class playlistContent :public core::abstractContent
{
      Q_OBJECT
      public:
	  playlistContent(QWidget *parent=0);
	  ~playlistContent();
	  QString name() const;
	  void activated(const int n);
	  
	  
      private:	
	  QAction 		*backAction;
	  QAction 		*forwardAction;	  
	  QStackedWidget 	*stack;
	  
	  QTreeView		*treeV;
	  views::treeView	*trackV;
	  playlistModel  	*plModel;
	  standardModel		*smpModel;
	  
	  standardModel		*treeModel;
	  playlistFolder	*plHead;
	  folderItem		*smHead;

	  QSortFilterProxyModel	*proxyM;
 	  QSortFilterProxyModel	*trackProxy;
	  
	  //actions
	  QAction 		*removeAction;
	  QAction		*addFolderAction;
	  QAction		*createSmpAction;
	  QAction		*editSmpAction;
	  QAction 		*renameAction;
	  
	  QAction		*searchAction;

	  KLineEdit 		*searchLine;	  
	  
	  QDomDocument 		doc;
	  
	  bool			needUpdate;
	  
	  void 			toolBarInit();	 
	  
	  core::queryGrt	*quer;
	  views::trackModelItem	*smItem;
	  
      public slots:
	  void back();
	  void forward();
	  void search();
	  void activationSlot(QModelIndex in);
	  
	  void addFolderSlot();
	  void createSmpSlot();
	  void editSmpSlot();
	  void removeSlot();
	  void save();
	  void contextMenuSlot(QModelIndex index);
	  void updateQueries();
	  standardItem* head(standardItem* item);
};

#endif
