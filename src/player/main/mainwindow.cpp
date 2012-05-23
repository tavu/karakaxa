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
#include<dbFunc.h>

#include"nplaylistModel.h"
#include"nplaylistDelegate.h"

#include"../content/library/library.h"
#include"../content/folder/folder.h"
#include"../content/playlist/playlistContent.h"
#include"../content/configure/configureContent.h"
#include"../content/edit/editTrackContent.h"
#include"../content/nowPlaylist/nowPlaylistContent.h"


#define ICONZISE QSize(35,35)

using namespace views;
using namespace core;

#include<iostream>

mainWindow::mainWindow()
        :KMainWindow()
{
    audioFiles::init();
    core::init();
    database::init();
    views::init();

    setIconSize(ICONZISE);
    setWindowIcon(decor->logo() );
           
    infoInit();
    conTreeInit();
    conViewInit();    
    nplViewInit();    
    toolBarInit();                    
    createMenus();
    createTrayIcon();
    
    
    setStatusBar(new views::statusBar(this) );    

    connect( core::engine() ,SIGNAL(stateChanged ( Phonon::State) ),this, SLOT( stateChanged ( Phonon::State) ) );
    
    defaultContent();
    readSettings();

    
    npList()->loadSavedPlaylist();
}

mainWindow::~mainWindow()
{
      writeSettings();
}

inline void mainWindow::infoInit()
{
    info=new playingInfo(this);
    info->setFixedHeight(100);
    
    infoDock=new QDockWidget(this);
    infoDock->setWidget(info);

    infoDock->setPalette(views::decor->palette() );

    info->setPalette(views::decor->palette());
    
    infoDock->setWindowTitle(tr("playing track information") );
    infoDock->setObjectName("playingTrackInfo");    
    infoDock->setAutoFillBackground(true);

    addDockWidget ( Qt::LeftDockWidgetArea, infoDock,Qt::Horizontal);    
}

void mainWindow::conViewInit()
{
    QFrame *f =new QFrame(this);
    QWidget *conView=contentHdl->view();
    conView->setPalette(views::decor->palette());
    f->setAutoFillBackground(true);
    f->setPalette(views::decor->palette());
    
    QVBoxLayout *l=new QVBoxLayout(f);
    l->addWidget(core::contentHdl->toolBar() );
    l->addWidget(conView);
    l->setContentsMargins(0,0,0,0);
    
    f->setFrameStyle(QFrame::StyledPanel);
    f->setFrameShadow(QFrame::Raised);
                   
    conView->setAutoFillBackground(true);
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
    QPalette pal= decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    conTree->setPalette(pal);
    conTreeDock->setPalette(pal); 
        
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
    nplView->setDragDropMode(QAbstractItemView::DragDrop);
    nplView->setAcceptDrops(true);
    nplView->setHeaderHidden(true);
    for(int i=1;i<FRAME_NUM;i++)
    {
         nplView->setColumnHidden(i,true);
    }
   
    nplView->setItemDelegate(new nplDelegate(this) );    

    nplView->setFrameShadow(QFrame::Raised);
    nplView->header()->setStretchLastSection(true);
    nplView->header()->setDefaultSectionSize(35);
    nplView->header()->setResizeMode(QHeaderView::Fixed);    
    
    QColor c=decor->palette().color(QPalette::Window);    
    QString s=("QHeaderView::section {background-color: rgb(%1,%2,%3); }");
    s=s.arg(QString::number(c.red() ),QString::number( c.green() ),QString::number( c.blue() ) );
    
    QPalette pal=decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    nplView->setPalette(pal);
        
    nplView->header()->setStyleSheet(s);



    KToolBar *t=new KToolBar(this);

    t->setToolButtonStyle( Qt::ToolButtonIconOnly );
    t->setIconSize(QSize(25,25) );    


    t->addAction( views::menus->clearPlaylist() );    
    t->addAction( views::menus->repeatPlaylist() );
    t->addAction( views::menus->sufflePlaylist() );
    t->addSeparator();
    t->addAction( nplView->goToCurrent() );

    QVBoxLayout *l=new QVBoxLayout(w);
    l->addWidget(nplView);
    l->addWidget(t);

    l->setContentsMargins(2,10,2,0);

    nplViewDock=new QDockWidget(this);
    nplViewDock->setWindowTitle("Playlist");
    nplViewDock->setObjectName("Playlist");
    nplViewDock->setWidget(w);
    
    nplViewDock->setPalette(pal);
    nplViewDock->setAutoFillBackground(true);
    nplView->header()->setPalette(pal);
    addDockWidget ( Qt::RightDockWidgetArea, nplViewDock, Qt::Vertical );

}

void mainWindow::toolBarInit()
{      
    toolBar=new QToolBar(this);
    
//     info->setFixedWidth(160);  
    toolBar->setIconSize(ICONZISE);
    
        
    
    previousAction = new QAction(  views::decor->previous() ,"play previous", this );
    toolBar ->addAction( previousAction );
    connect(previousAction,SIGNAL(triggered( bool)),engine(),SLOT(previous() ) );

    playAction = new QAction(  views::decor->play(),"play-pause", this );
    toolBar->addAction( playAction );
    connect(playAction,SIGNAL(triggered( bool)),engine(),SLOT(playPause() ) );

    nextAction = new QAction(  views::decor->next(),"play next", this );
    toolBar->addAction( nextAction );
    connect(nextAction,SIGNAL(triggered( bool)),engine(),SLOT(next() ) );
   
    views::sliderWidget *slider=new views::sliderWidget(this);
    
    toolBar->addWidget(slider);
    
                
    volumeB=new views::volumeBar(this);
    volumeB->setFixedWidth(150);
    toolBar->addWidget(volumeB);
           
   
    
    
    addToolBar ( Qt::TopToolBarArea,toolBar);

    toolBar->setAutoFillBackground(false);
            
//     toolBar->setFixedHeight(110);

    toolBar->setObjectName("buttonsToolBar");


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



void mainWindow::stateChanged(Phonon::State state)
{
    if (state==Phonon::ErrorState|| state==Phonon::PausedState )
        playAction->setIcon(decor->play() );
    else
        playAction->setIcon(decor->pause() );
}

void mainWindow::defaultContent()
{
      library *l=new library();      
      folderContent *f=new folderContent();
      playlistContent *pl=new playlistContent();
      configureContent *c=new configureContent();
      nowPlaylistContent *n=new nowPlaylistContent();
      
      n->setModel(nowPlayListM);
      
      contentHdl->addContent(l);
      contentHdl->addContent(f);
      contentHdl->addContent(pl);
      contentHdl->addContent(n);
      
      contentHdl->addContent(c);

      contentHdl->setCurrentContent(l);
      
      editTrackMenu *m=new editTrackMenu();
      contentHdl->addMenu(m);

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

    trayIconMenu->addAction(volumeB->action());
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(previousAction);    
    trayIconMenu->addAction(playAction);    
    trayIconMenu->addAction(nextAction);    
    trayIconMenu->addSeparator();    
    trayIconMenu->addAction(quitAction);
         
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
    playerMenu=menuBar()->addMenu(tr("&Karakaxa"));

    quitAction = new QAction(KIcon("application-exit"), tr("&Quit"), this);
    
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    

    playerMenu->addAction(previousAction);    
    playerMenu->addAction(playAction);    
    playerMenu->addAction(nextAction);    
    playerMenu->addAction(volumeB->action());
    playerMenu->addSeparator();    
    playerMenu->addAction(quitAction);
    
    
    viewMenu=menuBar()->addMenu(tr("&View"));    
    
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

// void mainWindow::keyPressEvent(QKeyEvent* event)
// {
//     if(event->key()==Qt::Key_Space)
//     {
// 	   engine->playPause();
//     }
//     QWidget::keyPressEvent(event);
// }
