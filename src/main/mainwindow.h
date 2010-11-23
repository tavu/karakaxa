#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QPushButton>
#include <Phonon/SeekSlider>
#include <Phonon/VideoWidget>
#include <Phonon/VolumeSlider>
#include<QLabel>
#include<QVBoxLayout>

// #include"nowPlaylistWidget.h"
// #include"sound/sound.h"
// #include"../mainWidget.h"
#include <QDockWidget>
#include<player.h>
#include <QMainWindow>
#include<QTreeWidget>
#include<QStackedWidget>
#include"contentTree.h"
#include<QListView>
#include<QDockWidget>
#include <KToolBar>
#include<KIcon>
#include"nplaylistView.h"
#include"playingInfo.h"
class mainWindow :public QMainWindow
{
    Q_OBJECT
    public:
	mainWindow();
	~mainWindow();
    private:

	KToolBar *toolBar;
	nplaylistView *nplView;
	contentTree *conTree;
	QStackedWidget *conView;

	QDockWidget 	*conTreeDock;
	QDockWidget 	*conViewDock;
	QDockWidget 	*nplViewDock;
	QDockWidget      *infoDock;

	QWidget  *conTreeDockT;
	QWidget  *conViewDockT;
	QWidget  *nplViewDockT;
	QWidget  *infoDockT;
	//for the toolBar
	QAction *playAction;
	QAction *nextAction;
	QAction *previousAction;
	QAction *volumeAction;
	
	
	Phonon::SeekSlider *slider;
	QLabel *timeLabel;
	QLabel *progressLabel;    

    //  	  sound *sd;
	QWidget * viewport;

	QPalette pal;
	//fuctions
	inline void init();
	inline void toolBarInit();
	inline void nplViewInit();
	inline void conTreeInit();
	inline void conViewInit();
	inline void defaultContent();
	inline void infoInit();

	void lockDock();

	void writeSettings();
	void readSettings();

	void closeEvent(QCloseEvent *event);
    public slots:
	void stateChanged(Phonon::State state);


};


#endif
