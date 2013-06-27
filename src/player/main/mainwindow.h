#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QPushButton>
#include <Phonon/SeekSlider>
#include <Phonon/VideoWidget>
#include <Phonon/VolumeSlider>
#include<QLabel>
#include<QVBoxLayout>
#include<QSystemTrayIcon>

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

#include"nplaylistModel.h"
class mainWindow :public KMainWindow
{
    Q_OBJECT
    public:
	mainWindow();
	~mainWindow();
	
        static const QString nplStyle;
    private:
	
        QSystemTrayIcon	*trayIcon;
        QToolBar 	*toolBar;
        nplaylistView 	*nplView;
        contentTree 	*conTree;
        QStackedWidget 	*conView;


        QDockWidget 	*conTreeDock;
        QDockWidget 	*conViewDock;
        QDockWidget 	*nplViewDock;
        QDockWidget      *infoDock;

        nplModel *nowPlayListM;

        //for the menu bar
      /*  QMenu *playerMenu;
        QMenu *settingsMenu;
        QMenu *helpMenu;
        QMenu *viewMenu;
*/
        QAction *lockLayout;


        //fuctions
        inline void toolBarInit();
        inline void nplViewInit();
        inline void conTreeInit();
        inline void conViewInit();
        inline void defaultContent();
        inline void createTrayIcon();
        inline void createMenus();


        void writeSettings();
        void lockDock();
        void unlockDock();

        void readSettings();

        void closeEvent(QCloseEvent *event);
    // 	void keyPressEvent ( QKeyEvent * event );

    public slots:
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
