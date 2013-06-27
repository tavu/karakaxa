#include"mainwindow.h"

#include<QSplitter>
#include<QGroupBox>
#include<QString>
#include <QTextCodec>
#include<QApplication>
#include<QMenuBar>
#include<QToolButton>
#include<KConfig>
#include<KConfigGroup>
#include<QHeaderView>
#include <kcmdlineargs.h>
#include<QVBoxLayout>
#include<KHelpMenu>
#include<KMenuBar>
#include<KMenu>

#include<core.h>
#include<views.h>
#include<database/dbFunc.h>
#include<Basic/func.h>

#include"nplaylistModel.h"
#include"nplaylistDelegate.h"
#include "playingWidget.h"

#include"../content/library/library.h"
#include"../content/folder/folder.h"
#include"../content/playlist/playlistContent.h"
#include"../content/configure/configureContent.h"
#include"../content/edit/editTrackContent.h"
#include"../content/nowPlaylist/nowPlaylistContent.h"

// #include<coverWidget/coverDownloaderWidget.h>
#include"../content/newLibrary/libraryContent.h"

#define ICONZISE QSize(35,35)

using namespace views;
using namespace core;

#include<iostream>

mainWindow::mainWindow()
        :KMainWindow()
{
    Basic::init();
    audioFiles::init();
    core::init();
    database::init();
    views::init();

    setWindowIcon(decor->logo() );
    conTreeInit();
    conViewInit();    
    nplViewInit();    
    toolBarInit();                    
    createMenus();
    createTrayIcon();
    
    
    setStatusBar(new views::statusBar(this) );
    
    config->setMainWindow(this);
    config->readSetings();
    
    defaultContent();
    readSettings();
    
    npList()->loadSavedPlaylist();

}

mainWindow::~mainWindow()
{
      writeSettings();
}

void mainWindow::conViewInit()
{
    QFrame *f =new QFrame(this);
    QWidget *conView=contentHdl->view();
    
    QVBoxLayout *l=new QVBoxLayout(f);
    l->addWidget(core::contentHdl->toolBar() );
    l->addWidget(conView);
    l->setContentsMargins(0,0,0,0);
    conView->setAutoFillBackground(false);
    f->setObjectName("mainFrame");
//     f->setFrameShape(QFrame::Panel);
//     f->setFrameShadow(QFrame::Plain);
//     f->setStyleSheet("#mainFrame { border:1px solid gray; border-radius: 4px; }");
//     f->setStyleSheet("#mainFrame { border-width: 1px;border-style: solid;border-color: gray; border-radius: 4px; }");
    setCentralWidget(f); 
}

void mainWindow::conTreeInit()
{
    conTree=new contentTree(this);
    conTree->setFrameStyle(QFrame::Raised);
    conTree->setHeaderHidden(true);
    conTree->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    conTree->setAutoFillBackground(true);

    conTreeDock =new QDockWidget(this);
    conTreeDock->setWindowTitle("contents");
    conTreeDock->setObjectName("contentTree");

    conTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding );
    conTree->setStyleSheet("QAbstractItemView {background-color: transparent;icon-size: 20px;} QTreeView::item{height: 30px;}");
//     QPalette pal= decor->palette();
//     pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
   // conTree->setPalette(pal);
    //conTreeDock->setPalette(pal); 
        
    core::contentHdl->setView(conTree);
        
    conTreeDock->setWidget(conTree);
    conTreeDock->setAutoFillBackground(true);
    addDockWidget ( Qt::LeftDockWidgetArea, conTreeDock,Qt::Vertical);

    

}

void mainWindow::nplViewInit()
{
    QFrame *w=new QFrame(this);
    nplView =new nplaylistView();
    nowPlayListM=new nplModel(this);
    nplView->setModel(nowPlayListM);
    nplView->initMinimalView();
    
    QColor c=nplView->palette().color(QPalette::Window);
    nplView->setStyleSheet(nplStyle.arg(c.darker().name() ) );
    nplView->setFrameStyle(QFrame::NoFrame);

    
    QPalette pal=decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
   // nplView->setPalette(pal);
        
//     nplView->header()->setStyleSheet(s);



    KToolBar *t=new KToolBar(this);

    t->setToolButtonStyle( Qt::ToolButtonIconOnly );
    t->setIconSize(QSize(25,25) );    


    t->addAction( views::menus()->clearPlaylist() );    
    t->addAction( views::menus()->repeatPlaylist() );
    t->addAction( views::menus()->sufflePlaylist() );
    t->addSeparator();
    t->addAction( nplView->goToCurrent() );

    QVBoxLayout *l=new QVBoxLayout(w);
    l->addWidget(nplView);
    l->addWidget(t);

//     l->setContentsMargins(2,10,2,0);

    nplViewDock=new QDockWidget(this);
    nplViewDock->setWindowTitle("Playlist");
    nplViewDock->setObjectName("Playlist");
    nplViewDock->setWidget(w);
    
    //nplViewDock->setPalette(pal);
    nplViewDock->setAutoFillBackground(false);
   // nplView->header()->setPalette(pal);
    addDockWidget ( Qt::RightDockWidgetArea, nplViewDock, Qt::Vertical );

}

void mainWindow::toolBarInit()
{      
    toolBar=new QToolBar(this);         

  
   playingWidget *plw=new playingWidget(this);
    
    toolBar->addWidget(plw);
//     addToolBar ( Qt::TopToolBarArea,toolBar);

    toolBar->setAutoFillBackground(true);
            
//     toolBar->setFixedHeight(110);

    toolBar->setObjectName("buttonsToolBar");
    
    QPalette pal=toolBar->palette();
    QColor c=pal.color(QPalette::Base);  
    c=c.darker(150);
    pal.setColor(QPalette::Base,c);
//     toolBar->setPalette(c); 

    infoDock=new QDockWidget(this);
    infoDock->setWindowTitle("info");
    infoDock->setObjectName("info");
    infoDock->setWidget(toolBar);
    addDockWidget ( Qt::RightDockWidgetArea, infoDock, Qt::Vertical );
}


void mainWindow::lockDock()
{
    const QFlags<QDockWidget::DockWidgetFeature> features = QDockWidget::NoDockWidgetFeatures;

    conTreeDock->setFeatures(features);

    nplViewDock->setFeatures(features);
//     nplViewDock->titleBarWidget()->hide();
    nplViewDock->setTitleBarWidget(new QWidget(nplViewDock));

    infoDock->setFeatures(features);
    infoDock->setTitleBarWidget(new QWidget(infoDock));

    toolBar->setMovable(false);    
}

void mainWindow::unlockDock()
{
    const QFlags<QDockWidget::DockWidgetFeature> features = QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable;

    conTreeDock->setFeatures(features);


    nplViewDock->setFeatures(features);        
    QWidget *w=nplViewDock->titleBarWidget();
    conTreeDock->setTitleBarWidget(0);
    delete w;
//     nplViewDock->setTitleBarWidget(new QWidget(nplViewDock));

  infoDock->setFeatures(features);
    w=infoDock->titleBarWidget();
    infoDock->setTitleBarWidget(0);
    delete w;
    
    toolBar->setMovable(true);    
}

void mainWindow::defaultContent()
{
      library *l=new library();      
      folderContent *f=new folderContent();
      playlistContent *pl=new playlistContent();
      configureContent *c=new configureContent();
      nowPlaylistContent *n=new nowPlaylistContent();
      
//     libraryContent *nl=new libraryContent();
	  
      n->setModel(nowPlayListM);
      
      contentHdl->addContent(l);
      contentHdl->addContent(f);
      contentHdl->addContent(pl);
      contentHdl->addContent(n);      
      contentHdl->addContent(c);
	  
//       contentHdl->addContent(nl);

      contentHdl->setCurrentContent(l);
      
      editTrackMenu *m=new editTrackMenu();
      contentHdl->addMenu(m);

// 	  coverDownloaderWidget *w=new coverDownloaderWidget(this);
// 	  contentHdl->addWidget(w);
}

void mainWindow::closeEvent(QCloseEvent *event)
{    
    hide();	
    event->ignore();
}

void mainWindow::writeSettings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "MainWindow" );
    group.writeEntry("geometry", QVariant(saveGeometry() ) );
    group.writeEntry("volume", QVariant(engine()->volume() ) );
    group.writeEntry( "state", QVariant(saveState() ) );
    group.writeEntry( "layoutLocked", QVariant(lockLayout->isChecked() ) );
    group.config()->sync();

  
}

void mainWindow::readSettings()
{  
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "MainWindow" );
    restoreGeometry(group.readEntry("geometry",QByteArray() ) );
    lockLayout->setChecked(group.readEntry("layoutLocked",false) );
    engine()->setVolume(group.readEntry("volume",0.5 ));        
    restoreState(group.readEntry("state",QByteArray()) );

    if(lockLayout->isChecked() )
    {
        lockDock();
    }
}

void mainWindow::createTrayIcon()
{
    trayIcon=new QSystemTrayIcon(decor->logo(),this);
    QMenu *trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(menus()->volume());
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(menus()->previous());    
    trayIconMenu->addAction(menus()->playPause());    
    trayIconMenu->addAction(menus()->next());    
    trayIconMenu->addSeparator();    
    trayIconMenu->addAction(menus()->quit());
         
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(decor->logo());
     
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason) ) );
    trayIcon->show();
}

void mainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger||reason==QSystemTrayIcon::DoubleClick)
    {
        setVisible(!isVisible());
        if(isVisible() )
        {
            activateWindow();
        }
    }  
}


void mainWindow::createMenus()
{
    QMenu* playerMenu=menuBar()->addMenu(tr("&Karakaxa"));

    playerMenu->addAction(menus()->previous());    
    playerMenu->addAction(menus()->playPause());    
    playerMenu->addAction(menus()->next() );    
    playerMenu->addAction(menus()->volume() );
    playerMenu->addSeparator();    
    playerMenu->addAction(menus()->quit());   
    
    QMenu* viewMenu=menuBar()->addMenu(tr("&View"));    
    
    lockLayout=new QAction(tr("&lock layout"),viewMenu);
    lockLayout->setCheckable(true);
    connect(lockLayout,SIGNAL(triggered(bool)),this,SLOT(changeLockLayout(bool)) );
    
    viewMenu->addAction(infoDock->toggleViewAction() );
    viewMenu->addAction(nplViewDock->toggleViewAction() );
    viewMenu->addAction(conTreeDock->toggleViewAction() );
    viewMenu->addAction(lockLayout );
    
    KHelpMenu *helpMenu=new KHelpMenu(this,KCmdLineArgs::aboutData(),false);
    KMenu *s_helpMenu=helpMenu->menu();
    helpMenu->action( KHelpMenu::menuHelpContents )->setVisible( false );    
    menuBar()->addMenu(s_helpMenu);
}

const QString mainWindow::nplStyle="\
QAbstractItemView { \
    background-color: transparent \
} \
QTreeView::item { \
    height: 20px;\
} \
QScrollBar {\
     border: 0px;\
     background: transparent;\
}\
QScrollBar:vertical {\
     width: 7px;\
     margin: 5px 0px 0px 0px;\
}\
QScrollBar::handle {\
     background: %1;\
}\
QScrollBar::add-line  {\
    width: 0px;\
}\
QScrollBar::sub-line  {\
    width: 0px;\
}";
