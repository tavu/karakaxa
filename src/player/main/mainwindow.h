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
#include <KMainWindow>
#include<QTreeWidget>
#include<QStackedWidget>
#include"contentTree.h"
#include<QListView>
#include<QDockWidget>
#include <KToolBar>
#include<KIcon>
#include"nplaylistView.h"
#include"playingInfo.h"
#include"nplaylistModel.h"
class mainWindow :public KMainWindow
{
    Q_OBJECT
    public:
	mainWindow();
	~mainWindow();
	
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

        nplModel *nowPlayListM;

        //for the toolBar
        QAction *playAction;
        QAction *nextAction;
        QAction *previousAction;
        views::volumeBar *volumeB;
        Phonon::SeekSlider *slider;

        QLabel *timeLabel;
        QLabel *progressLabel;

        //for the menu bar
        QMenu *playerMenu;
        QMenu *settingsMenu;
        QMenu *helpMenu;
        QMenu *viewMenu;

        QAction *lockLayout;
        QAction *quitAction;


        //fuctions
        inline void toolBarInit();
        inline void nplViewInit();
        inline void conTreeInit();
        inline void conViewInit();
        inline void defaultContent();
        inline void infoInit();
        inline void createTrayIcon();
        inline void createMenus();


        void writeSettings();
        void lockDock();
        void unlockDock();

        void readSettings();

        void closeEvent(QCloseEvent *event);
    // 	void keyPressEvent ( QKeyEvent * event );

        
    public slots:
        void stateChanged(Phonon::State state);
        void iconActivated(QSystemTrayIcon::ActivationReason reason);
        void QuitSlot()
        {
            hide();
            writeSettings();
        }

        void changeLockLayout(bool b)
        {
            if(b)
            {
                    lockDock();
            }
            else
            {
                unlockDock();
            }
        }
};


#endif
