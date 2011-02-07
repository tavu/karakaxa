#include<mainwindow.h>
#include<QSplitter>
#include"nplaylistModel.h"
#include"nplaylistDelegate.h"
#include<QGroupBox>

#include "../content/library/library.h"
#include "../content/folder/folder.h"
#include "../content/playlist/playlistContent.h"
#include "../content/configure/configureContent.h"
// #include "../content/visualization/visualization.h"
// #include<contentAdder.h>
#include<QToolButton>
#include"volumeBar.h"

#include<KConfig>
#include<KConfigGroup>

#define ICONZISE QSize(40,40)

using namespace player;

#include<QHeaderView>

mainWindow::mainWindow()
        :QMainWindow()
{
  
//    qApp->setStyleSheet("QAbstractItemView {background-color: transparent; }");
  
  
  
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));

    pal=palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
//     pal.setColor(QPalette::Link,QColor(0,0,255) );
//      pal.setColor(QPalette::Window,QColor(175,194,237) );

//     QColor c(180,189,213);
    QColor c(180,189,213);
    
    pal.setColor(QPalette::AlternateBase,c );
    pal.setColor(QPalette::Window,c );

    player::pal=pal;
    player::pal.setColor(QPalette::Base,pal.color(QPalette::Window) );

    infoInit();
    conTreeInit();
    conViewInit();


    init();

    nplViewInit();

    toolBarInit();
    
     QDockWidget *w=new QDockWidget(this);
     w->setWidget(toolBar);



     addDockWidget ( Qt::LeftDockWidgetArea, infoDock,Qt::Horizontal);
     addDockWidget ( Qt::LeftDockWidgetArea, conTreeDock,Qt::Vertical);
     addDockWidget ( Qt::LeftDockWidgetArea, w, Qt::Horizontal );
//      addDockWidget ( Qt::LeftDockWidgetArea, conViewDock, Qt::Horizontal );
     
      addDockWidget ( Qt::LeftDockWidgetArea, conViewDock, Qt::Vertical );
     addDockWidget ( Qt::LeftDockWidgetArea, nplViewDock, Qt::Horizontal );

     
     
    setStatusBar(player::statusBar.statusBar() );

//     addToolBar ( Qt::TopToolBarArea,toolBar);

//     lockDock();

    //signals


    connect( &engine ,SIGNAL(stateChanged ( Phonon::State) ),this, SLOT( stateChanged ( Phonon::State) ) );
//
//      connect(playButton, SIGNAL(clicked()), soundEngine, SLOT(playPause() ) );
//
//      connect(forwardButton, SIGNAL(clicked()), soundEngine, SLOT(next() ) );
//
//      connect(rewindButton, SIGNAL(clicked()), soundEngine, SLOT(prev() ) );

//      connect(nowPl,SIGNAL(changeSong(QString)),soundEngine,SLOT(play(QString) ) );


    readSettings();
    defaultContent();

//      writeSettings();
}
mainWindow::~mainWindow()
{
//      writeSettings();
    delete viewport;

}

inline void mainWindow::init()
{
    player::statusBar.init();
    db.init();
    player::engine.init();
//      player::nowPl=new nowPlaylist();


//      player::config=new PlayerConfigure();

    

    player::contentHandlr=new contentHandler(conTree,conView);

}

inline void mainWindow::infoInit()
{
    info=new playingInfo(this);
    info->setFixedSize(200,150);
    QWidget *w=new QWidget(this);
    QHBoxLayout *hLayout=new QHBoxLayout();
//     QVBoxLayout *VLayout=new QVBoxLayout();
    hLayout->addWidget(info);
    hLayout->addStretch();
    w->setLayout(hLayout);
    
    
    infoDock=new QDockWidget(this);
    infoDock->setWidget(w);

    infoDock->setPalette(player::pal);

    infoDock->setWindowTitle("playing track info");
    infoDock->setObjectName("playingTrackInfodf");
//     infoDockT=new QWidget(this);

}

void mainWindow::conViewInit()
{
    conView=new QStackedWidget(this);    
    conViewDock=new QDockWidget(this);
    conViewDock->setWindowTitle("content Dock");
    conViewDock->setObjectName("contentDock");
    conViewDock->setWidget(conView);



    conViewDock->setPalette(pal);

    conViewDockT=new QWidget(this);
}

void mainWindow::conTreeInit()
{
    conTree=new contentTree(this);
    conTree->setFrameStyle(QFrame::Raised);
    conTree->setHeaderHidden(true);
//     conTree->setHeaderLabel("Content");

    conTreeDock =new QDockWidget(this);
    conTreeDock->setWindowTitle("select content");
    conTreeDock->setObjectName("contentTree");

//     QWidget *w=new QWidget(this);
//     QFrame *f=new QFrame(this);
//     f->setFrameStyle(QFrame::HLine);
//     QVBoxLayout *l=new QVBoxLayout();
// 
//     
//     w->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//     
//     QLabel *label=new QLabel("Content",this);
//     
//     l->addWidget(info);
//     l->addWidget(f);
//     l->addWidget(label);
//     l->addWidget(conTree);
// //     l->addWidget(f);
//     
    
//     w->setLayout(l);
    
    conTreeDock->setWidget(conTree);

    conTreeDock->setPalette(player::pal);
    

}

void mainWindow::nplViewInit()
{
    QFrame *w=new QFrame(this);
    nplViewDockT=new QWidget(this);
    
    nplView =new nplaylistView(w);
    nplModel *m=new nplModel(this);
    qDebug()<<"column "<<m->columnCount();
    nplView->setModel(m);
    nplView->setDragDropMode(QAbstractItemView::DragDrop);
    nplView->setAcceptDrops(true);   

    nplDelegate *delegate=new nplDelegate(this);
    nplView->setItemDelegate(delegate);

    QPalette p=QApplication::palette();
    p.setColor(QPalette::Base,p.color(QPalette::Window) );

    nplView->setFrameShadow(QFrame::Raised);
    nplView->header()->setStretchLastSection(true);
    nplView->header()->setDefaultSectionSize(35);
    nplView->header()->setResizeMode(QHeaderView::Fixed);
    

    viewport = nplView->viewport();

    connect( &engine ,SIGNAL(trackChanged ( QString) ),viewport, SLOT(update() ) );


    KToolBar *t=new KToolBar(this);
    nplView->setAutoFillBackground(false);

    t->setToolButtonStyle( Qt::ToolButtonIconOnly );
    t->setIconSize(QSize(25,25) );    

    QAction *clearAction = new QAction( KIcon("edit-clear-list"),"clear", this );
    t->addAction( clearAction );
    connect(clearAction,SIGNAL(triggered( bool)),&npList,SLOT(clear() ) );

    QAction *suffleAction = new QAction( KIcon("roll"),"clear", this );
    t->addAction( suffleAction );
    connect(suffleAction,SIGNAL(triggered( bool)),&npList,SLOT(suffle() ) );

    QVBoxLayout *l=new QVBoxLayout(w);
    l->addWidget(nplView);
    l->addWidget(t);

    l->setContentsMargins(2,10,2,0);

//     w->setPalette(QApplication::palette);
    
//     w->setFrameShadow(QFrame::Raised);

    nplViewDock=new QDockWidget(this);
    nplViewDock->setWindowTitle("Playlist");
    nplViewDock->setObjectName("Playlist");
    nplViewDock->setWidget(w);
    
    nplViewDock->setPalette(player::pal);
//      nplViewDock->setPalette(player::pal);
//      nplViewDockT=new QWidget(this);


}

void mainWindow::toolBarInit()
{ 
    toolBar=new KToolBar(this);

    QPalette p=QApplication::palette();

    toolBar->setPalette(p);
    toolBar->setAutoFillBackground(true);

    toolBar->setObjectName("buttonsToolBar");
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );
    toolBar->setIconSize(ICONZISE );
    toolBar->setMovable(true);

    previousAction = new QAction(  decor.previous() ,"play previous", this );
    toolBar->addAction( previousAction );
    connect(previousAction,SIGNAL(triggered( bool)),&engine,SLOT(previous() ) );

    playAction = new QAction(  decor.play(),"play-pause", this );
    toolBar->addAction( playAction );
    connect(playAction,SIGNAL(triggered( bool)),&engine,SLOT(playPause() ) );

    nextAction = new QAction(  decor.next(),"play next", this );
    toolBar->addAction( nextAction );
    connect(nextAction,SIGNAL(triggered( bool)),&engine,SLOT(next() ) );
    
    slider = new Phonon::SeekSlider(this);
    slider->setMediaObject(engine.getMediaObject() );
    slider->setIconVisible(false);
    toolBar->addWidget(slider);
    
    volumeBar *v=new volumeBar(this);
    v->setFixedWidth(150);
    toolBar->addWidget(v);

}


void mainWindow::lockDock()
{
    const QFlags<QDockWidget::DockWidgetFeature> features = QDockWidget::NoDockWidgetFeatures;

    conTreeDock->setFeatures(features);
//      conTreeDock->setTitleBarWidget(0);

    conViewDock->setFeatures(features);
    conViewDock->setTitleBarWidget(conViewDockT);



    nplViewDock->setFeatures(features);
    nplViewDock->setTitleBarWidget(nplViewDockT);

    infoDock->setFeatures(features);
//     infoDock->setMinimumWidth(210);
//    infoDock->setTitleBarWidget(infoDockT);
    
}

void mainWindow::stateChanged(Phonon::State state)
{
    if (state==Phonon::ErrorState|| state==Phonon::PausedState )
        playAction->setIcon(decor.play() );
    else
        playAction->setIcon(decor.pause() );
}

void mainWindow::defaultContent()
{
    library *l=new library();
    configureContent *c=new configureContent();
    folderContent *f=new folderContent();
//       visualization *v=new visualization();
    playlistContent *pl=new playlistContent();

    contentHandlr->addContent(l);
    contentHandlr->addContent(f);
    contentHandlr->addContent(c);
    contentHandlr->addContent(pl);
//       contentHandlr->addContent(v);
}

void mainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}

void mainWindow::writeSettings()
{
    KSharedConfigPtr config=player::config.configFile();
    KConfigGroup group( config, "MainWindow" );
    group.writeEntry("geometry", QVariant(saveGeometry() ) );
    group.writeEntry( "state", QVariant(saveState() ));
//     group.writeEntry( "infoDockHeight", QVariant(infoDock->height()) );
    group.config()->sync();  

  
}

void mainWindow::readSettings()
{
  
    KSharedConfigPtr config=player::config.configFile();
    KConfigGroup group( config, "MainWindow" );
    restoreGeometry(group.readEntry("geometry",QByteArray() ) );    
    restoreState(group.readEntry("state",QByteArray()) );
  
//     infoDock->resize(infoDock->width(), group.readEntry("infoDockHeight",30) );
}


