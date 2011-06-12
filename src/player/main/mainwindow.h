#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QPushButton>
#include <Phonon/SeekSlider>
#include <Phonon/VideoWidget>
#include <Phonon/VolumeSlider>
#include<QLabel>
#include<QVBoxLayout>
#include<QSystemTrayIcon>

// #include"nowPlaylistWidget.h"
// #include"sound/sound.h"
// #include"../mainWidget.h"
#include <QDockWidget>
#include<core.h>
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
// 	bool fullScreen()
// 	{
// 	    return _fullScreen;
// 	}
	
    private:
	
	QSystemTrayIcon	*trayIcon;
	QToolBar 	*toolBar;
	nplaylistView 	*nplView;
	contentTree 	*conTree;
	QStackedWidget 	*conView;
	playingInfo	*info;

	QDockWidget 	*conTreeDock;
	QDockWidget 	*conViewDock;
	QDockWidget 	*nplViewDock;
	QDockWidget      *infoDock;

	QWidget  *conTreeDockT;
	QWidget  *nplViewDockT;
	QWidget  *infoDockT;
	//for the toolBar
	QAction *playAction;
	QAction *nextAction;
	QAction *previousAction;
	
	views::volumeBar *volumeB;
	
	
	Phonon::SeekSlider *slider;
	QLabel *timeLabel;
	QLabel *progressLabel;    

	QWidget * viewport;

	QPalette pal;
	//fuctions
	inline void toolBarInit();
	inline void nplViewInit();
	inline void conTreeInit();
	inline void conViewInit();
	inline void defaultContent();
	inline void infoInit();
	inline void createTrayIcon();
	

	void writeSettings();
// 	bool _fullScreen;
	void lockDock();
	
	void readSettings();

	void closeEvent(QCloseEvent *event);
    
    public slots:
	void stateChanged(Phonon::State state);
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void QuitSlot()
	{
	    hide();
	    writeSettings();
	}


};


#endif
