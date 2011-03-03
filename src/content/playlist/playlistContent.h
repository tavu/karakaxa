#ifndef PLAYLIST_CONTENT_H
#define PLAYLIST_CONTENT_H

#include<player.h>
#include<KToolBar>
#include<KIcon>
#include<QStackedWidget>
#include<QAction>
// #include"smartPlaylist.h"
#include"smartPlaylistCreator.h"
#include<songView.h>
#include<songModel.h>
#include<playlistModel.h>

#include"myStandardModel.h"
#include"playlistItem.h"
#include"folderItem.h"
#include"items.h"
#include"smplaylistItem.h"


class playlistContent :public abstractContent
{
      Q_OBJECT
      public:
	  playlistContent(QWidget *parent=0);
	  ~playlistContent();
	  QString name() const;
	  void update(const int n);
	  
	  
      private:
	  KToolBar 		*toolBar;
	  QAction 		*backAction;
	  QStackedWidget 	*stack;

	  QTreeView		*treeV;
	  songView 		*trackV;
	  playlistModel  	*plModel;
	  songModel		*smpModel;
	  
	  myStandardModel	*treeModel;
	  myStandardItem	*plHead;
	  myStandardItem	*smHead;

	  QAction 		*removeAction;
	  QAction		*addFolderAction;
	  QAction		*createSmpAction;
	  QAction		*editSmpAction;
	  QAction 		*renameAction;

	  QSortFilterProxyModel	*proxyM;
	  
	  bool			needUpdate;
	  
	  void toolBarInit();
	  
      public slots:
	  void back();
	  void activationSlot(QModelIndex in);
	  
	  void addFolderSlot();
	  void createSmpSlot();
	  void editSmpSlot();
	  void removeSlot();
	  void save();
	  void contextMenuSlot(QModelIndex index);
	  void updateQueries();
};

#endif
