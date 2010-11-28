#ifndef PLAYLIST_CONTENT_H
#define PLAYLIST_CONTENT_H

#include<player.h>
#include<KToolBar>
#include<KIcon>
#include<QStackedWidget>

// #include"smartPlaylist.h"
#include"smartPlaylistModel.h"
#include"smartPlaylistCreator.h"
#include<songView.h>
// #include"smartPlaylist.h"

class  smartPlaylist;
class  filePlaylist;
class playlistContent :public abstractContent
{
      Q_OBJECT
      public:
	  playlistContent(QWidget *parent=0);
	  QString name() const;
	  void update(const int n);
	  
	  
      private:
	  smartPlaylist 	*smPl;
	  filePlaylist		*filePl;
	  KToolBar 		*toolBar;
	  QAction 		*backAction;      
	  QStackedWidget 	*stack;

	  myTreeView 		*treeV;
	  songView 		*trackV;
	  
	  short			current;
	  void toolBarInit();
	  
      public slots:
	  void back();
	 
    friend class smartPlaylist;
    friend class filePlaylist;
};

#endif
