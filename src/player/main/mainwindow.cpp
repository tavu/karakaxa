#include<mainwindow.h>
#include<QSplitter>
#include"nplaylistModel.h"
#include"nplaylistDelegate.h"
#include<QGroupBox>
#include<QString>
#include <QTextCodec>
#include<QApplication>
// #include "../content/library/library.h"
// #include "../content/folder/folder.h"
// #include "../content/playlist/playlistContent.h"
// #include "../content/configure/configureContent.h"
#include<QToolButton>
#include<core.h>
#include<KConfig>
#include<KConfigGroup>
#include<views.h>

#include"content/library/library.h"
#include"content/folder/folder.h"
#include"content/playlist/playlistContent.h"
#include"content/configure/configureContent.h"
#include"content/edit/editTrackContent.h"

#define ICONZISE QSize(35,35)

using namespace views;
using namespace core;

#include<QHeaderView>

mainWindow::mainWindow()
        :QMainWindow()
{    
    core::init();
    views::init();

    setIconSize(ICONZISE);
    setWindowIcon(decor->logo() );
    
    
    pal=palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    QColor c(180,189,213);
    pal.setColor(QPalette::Window,c );
//     pal.setColor(QPalette::Link,QColor(0,0,255) );
//     pal.setColor(QPalette::Window,QColor(175,194,237) );

//     QColor c(180,189,213);
     
//     c.setNamedColor("playerBlue");
    
//      pal.setColor(QPalette::AlternateBase,c );
     
//      pal.setColor(QPalette::Base,c );

//      qApp->setPalette(pal);
//     core::pal=pal;
//     core::pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    

    setMenuBar(0);
    infoInit();
    conTreeInit();
    conViewInit();    
    nplViewInit();    
    toolBarInit();                    
    createTrayIcon();

    setStatusBar(new views::statusBar(this) );    
     
    lockDock();

    connect( core::engine ,SIGNAL(stateChanged ( Phonon::State) ),this, SLOT( stateChanged ( Phonon::State) ) );
    
    connect(qApp,SIGNAL(aboutToQuit()) ,this,SLOT(QuitSlot() ) );
             
    readSettings();
    defaultContent();
    
//      core::contentHdl->init(conTree,conView);
//      core::contentHdl.loadDefault();


    //signals


    
//
//      connect(playButton, SIGNAL(clicked()), soundEngine, SLOT(playPause() ) );
//
//      connect(forwardButton, SIGNAL(clicked()), soundEngine, SLOT(next() ) );
//
//      connect(rewindButton, SIGNAL(clicked()), soundEngine, SLOT(prev() ) );

//      connect(nowPl,SIGNAL(changeSong(QString)),soundEngine,SLOT(play(QString) ) );




//      writeSettings();
}
mainWindow::~mainWindow()
{
//      writeSettings();
//     delete viewport;

}

// inline void mainWindow::init()
// {
//     core::statusBar.init();
//     db.init();
//     core::engine.init();
// //      core::nowPl=new nowPlaylist();
// 
// 
// //      core::config=new PlayerConfigure();
// 
//     
// 
//     core::contentHandlr=new contentHandler(conTree,conView);
// 
// }

inline void mainWindow::infoInit()
{
    info=new playingInfo(this);
    info->setFixedHeight(165);
    info->setMinimumWidth(150);
//     info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    
    infoDock=new QDockWidget(this);
    infoDock->setWidget(info);

    infoDock->setPalette(views::decor->palette() );

    info->setPalette(views::decor->palette());
    
    infoDock->setWindowTitle(tr("playing track info") );
    infoDock->setObjectName("playingTrackInfodf");    

    addDockWidget ( Qt::LeftDockWidgetArea, infoDock,Qt::Horizontal);
    
    infoDock->setPalette(decor->palette());
}

void mainWindow::conViewInit()
{
    QFrame *conView=contentHdl->contentView();
    conView->setFrameStyle(QFrame::StyledPanel);
    conView->setFrameShadow(QFrame::Raised);
//     conViewDock=new QDockWidget(this);
//      conViewDock->setWindowTitle("content Dock");
//     conViewDock->setObjectName("contentDock");
//     conViewDock->setWidget(conView);

    conView->setPalette(decor->palette());
    conView->setAutoFillBackground(true);
    setCentralWidget(conView); 
    
    
    
//     conViewDock->setPalette(pal);

    
}

void mainWindow::conTreeInit()
{
    conTree=new contentTree(this);
    conTree->setFrameStyle(QFrame::Raised);
    conTree->setHeaderHidden(true);
    conTree->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
//     conTree->setHeaderLabel("Content");

    conTreeDock =new QDockWidget(this);
    conTreeDock->setWindowTitle("select content");
    conTreeDock->setObjectName("contentTree");

    conTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding );
    QPalette pal= decor->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    conTree->setPalette(pal);
    conTreeDock->setPalette(pal); 
    
    core::contentHdl->setView(conTree);
    
    conTreeDock->setWidget(conTree);
    addDockWidget ( Qt::LeftDockWidgetArea, conTreeDock,Qt::Vertical);

    

}

void mainWindow::nplViewInit()
{
    QFrame *w=new QFrame(this);
//     nplViewDockT=new QWidget(this);
    
    nplView =new nplaylistView(w);
    nplModel *m=new nplModel(this);
    nplView->setModel(m);
    nplView->setDragDropMode(QAbstractItemView::DragDrop);
    nplView->setAcceptDrops(true);   

    nplDelegate *delegate=new nplDelegate(this);
    nplView->setItemDelegate(delegate);
    
//     p.setColor(QPalette::Base,p.color(QPalette::Window) );

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
    viewport = nplView->viewport();

    connect( engine ,SIGNAL(trackChanged ( QString) ),viewport, SLOT(update() ) );

    KToolBar *t=new KToolBar(this);

    t->setToolButtonStyle( Qt::ToolButtonIconOnly );
    t->setIconSize(QSize(25,25) );    

    QAction *clearAction = new QAction( KIcon("edit-clear-list"),"clear", this );
    t->addAction( clearAction );
    connect(clearAction,SIGNAL(triggered( bool)),npList,SLOT(clear() ) );

    QAction *suffleAction = new QAction( KIcon("roll"),"clear", this );
    t->addAction( suffleAction );
    connect(suffleAction,SIGNAL(triggered( bool)),npList,SLOT(suffle() ) );

    QVBoxLayout *l=new QVBoxLayout(w);
    l->addWidget(nplView);
    l->addWidget(t);

    l->setContentsMargins(2,10,2,0);

    nplViewDock=new QDockWidget(this);
    nplViewDock->setWindowTitle("Playlist");
    nplViewDock->setObjectName("Playlist");
    nplViewDock->setWidget(w);
    
    nplViewDock->setPalette(pal);
    nplView->header()->setPalette(pal);
    addDockWidget ( Qt::RightDockWidgetArea, nplViewDock, Qt::Vertical );

}

void mainWindow::toolBarInit()
{ 
    toolBar=new QToolBar(this);

//     QPalette p=QApplication::palette();

    toolBar->setObjectName("buttonsToolBar");
//     toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );
//     toolBar->setIconSize(ICONZISE );
//     toolBar->setMovable(true);

    previousAction = new QAction(  views::decor->previous() ,"play previous", this );
    toolBar->addAction( previousAction );
    connect(previousAction,SIGNAL(triggered( bool)),engine,SLOT(previous() ) );

    playAction = new QAction(  views::decor->play(),"play-pause", this );
    toolBar->addAction( playAction );
    connect(playAction,SIGNAL(triggered( bool)),engine,SLOT(playPause() ) );

    nextAction = new QAction(  views::decor->next(),"play next", this );
    toolBar->addAction( nextAction );
    connect(nextAction,SIGNAL(triggered( bool)),engine,SLOT(next() ) );
    
    slider = new Phonon::SeekSlider(this);
    slider->setMediaObject(core::engine->getMediaObject() );
    slider->setIconVisible(false);
    toolBar->addWidget(slider);
    
    volumeB=new views::volumeBar(this);
    volumeB->setFixedWidth(150);
    toolBar->addWidget(volumeB);
    
    toolBar->setAutoFillBackground(false);
   
    addToolBar ( Qt::TopToolBarArea,toolBar);

}


void mainWindow::lockDock()
{
    const QFlags<QDockWidget::DockWidgetFeature> features = QDockWidget::NoDockWidgetFeatures;

    conTreeDock->setFeatures(features);
    conTreeDock->setTitleBarWidget(0);

    nplViewDock->setFeatures(features);
    nplViewDock->setTitleBarWidget(new QWidget(nplViewDock));

    infoDock->setFeatures(features);
    infoDock->setTitleBarWidget(new QWidget(infoDock));

    toolBar->setMovable(false);
    
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

      contentHdl->addContent(l);
      contentHdl->addContent(f);
      contentHdl->addContent(pl);
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
    hide();
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "MainWindow" );
    group.writeEntry("geometry", QVariant(saveGeometry() ) );
    group.writeEntry("fullscreen", QVariant(isFullScreen() ) );
    group.writeEntry( "state", QVariant(saveState() ) );
    group.writeEntry( "infoDockHeight", QVariant(info->height()) );
    group.config()->sync();

  
}

void mainWindow::readSettings()
{  
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "MainWindow" );
    restoreGeometry(group.readEntry("geometry",QByteArray() ) );
//     _fullScreen=group.readEntry("fullscreen",false );
    int infoHeight=group.readEntry( "infoDockHeight",0 );
    
    restoreState(group.readEntry("state",QByteArray()) );
//     qDebug()<<"MM "<<infoHeight;
    
//     infoDock->resize( QSize(infoDock->width(),500) );
    
//     if(infoHeight!=0)
//     {
//  	info->resize( QSize(infoDock->width(),infoHeight) );
//     }
//      qDebug()<<"MMM "<<infoDock->height();
//      infoDock->resize(infoDock->width(), group.readEntry("infoDockHeight",30) );
}

void mainWindow::createTrayIcon()
{
     trayIcon=new QSystemTrayIcon(decor->logo(),this);
     QMenu *trayIconMenu = new QMenu(this);
     QAction *quitAction = new QAction(KIcon("application-exit"), tr("&Quit"), this);
     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
//      trayIconMenu->addAction(minimizeAction);
//      trayIconMenu->addAction(maximizeAction);
//      trayIconMenu->addAction(restoreAction);     
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
    }  
}
