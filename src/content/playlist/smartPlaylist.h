#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include <QStandardItemModel>
#include"smartPlaylistCreator.h"
#include<myTreeView.h>
#include"smartPlaylistModel.h"
#include<songModel.h>
#include"playlistContent.h"
class smartPlaylist :public QObject
{
    Q_OBJECT
    public:
	smartPlaylist(playlistContent *pl);
	~smartPlaylist();
    // 	  trackView();
    // 	  treeView();
    // 	  KToolBar* toolBar();

    private:     
	QAction			*widgetAction;
	playlistContent 	*plContent;
	smartPlaylistModel 	*smModel;

	songModel  		*trackM;
	short 			current;
	
    private slots:
	void addPl();
	void addFolder();

    public slots:
	void activate();
	void deActivate();
	void goToPlaylist(QModelIndex);
	
};

#endif
