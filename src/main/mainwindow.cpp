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
#define ICONZISE QSize(40,40)

#define CONF_PATH() ( QString ini_path(getenv("HOME")); \
				ini_path += "/.aman/"; )
using namespace player;

#define test qDebug()<<"test";

mainWindow::mainWindow()
        :QMainWindow()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
//      qDebug()<<"AAAAAAA";
//      QPalette p=palette();
    pal=palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
//      pal.setColor(QPalette::Window,QColor(175,194,237) );

    pal.setColor(QPalette::AlternateBase,QColor(171,193,219) );
    pal.setColor(QPalette::Window,QColor(171,193,219) );

    player::pal=pal;
    player::pal.setColor(QPalette::Base,pal.color(QPalette::Window) );

    conTreeInit();
    conViewInit();


    init();

    nplViewInit();

    toolBarInit();
    infoInit();



    addDockWidget ( Qt::LeftDockWidgetArea, infoDock,Qt::Vertical);
    addDockWidget ( Qt::LeftDockWidgetArea, conTreeDock,Qt::Vertical);
    addDockWidget ( Qt::LeftDockWidgetArea, conViewDock, Qt::Horizontal );
    addDockWidget ( Qt::LeftDockWidgetArea, nplViewDock, Qt::Horizontal );

    setStatusBar(player::statusBar.statusBar() );

    addToolBar ( Qt::TopToolBarArea,toolBar);
    test

    lockDock();
    test

    //signals


    connect( &engine ,SIGNAL(stateChanged ( Phonon::State) ),this, SLOT( stateChanged ( Phonon::State) ) );
//
//      connect(playButton, SIGNAL(clicked()), soundEngine, SLOT(playPause() ) );
//
//      connect(forwardButton, SIGNAL(clicked()), soundEngine, SLOT(next() ) );
//
//      connect(rewindButton, SIGNAL(clicked()), soundEngine, SLOT(prev() ) );

//      connect(nowPl,SIGNAL(changeSong(QString)),soundEngine,SLOT(play(QString) ) );



    defaultContent();

    readSettings();
//      writeSettings();
}
mainWindow::~mainWindow()
{
//      writeSettings();
    delete viewport;

}

inline void mainWindow::init()
{
    player::engine.init();
//      player::nowPl=new nowPlaylist();


//      player::config=new PlayerConfigure();

    player::statusBar.init();

    player::contentHandlr=new contentHandler(conTree,conView);

}

inline void mainWindow::infoInit()
{
    infoDockT=new playingInfo(this);
    infoDock=new QDockWidget(this);
    infoDock->setWidget(infoDockT);

    infoDock->setPalette(player::pal);

    infoDock->setWindowTitle("playing track info");
    infoDock->setObjectName("playingTrackInfo");

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

//       pal=palette();

//      conTree->setPalette(p);

    conTreeDock =new QDockWidget(this);
    conTreeDock->setWindowTitle("select content");
    conTreeDock->setObjectName("contentTree");
    conTreeDock->setWidget(conTree);

//      QPalette p;
//      p.setColor(QPalette::Base,p.color(QPalette::Window) );
    conTreeDock->setPalette(player::pal);
//      conTreeDockT=new QWidget(this);
}

void mainWindow::nplViewInit()
{
    QWidget *w=new QWidget(this);

    nplView =new nplaylistView(w);
    nplModel *m=new nplModel(this);
    nplView->setModel(m);
    nplView->setDragDropMode(QAbstractItemView::DragDrop);
    nplView->setAcceptDrops(true);



    nplView->setFrameStyle(QFrame::NoFrame);


    nplDelegate *delegate=new nplDelegate(this);
    nplView->setItemDelegate(delegate);

    QPalette p=QApplication::palette();
    p.setColor(QPalette::Base,p.color(QPalette::Window) );
    nplView->setPalette(p);



    viewport = nplView->viewport();

    connect( &engine ,SIGNAL(trackChanged ( QString) ),viewport, SLOT(update() ) );


    KToolBar *t=new KToolBar(this);
    nplView->setAutoFillBackground(false);

    t->setToolButtonStyle( Qt::ToolButtonIconOnly );
    t->setIconSize(QSize(25,25) );
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::HLine);

    QAction *clearAction = new QAction( KIcon("edit-clear-list"),"clear", this );
    t->addAction( clearAction );
    connect(clearAction,SIGNAL(triggered( bool)),&npList,SLOT(clear() ) );


    QVBoxLayout *l=new QVBoxLayout(w);
    l->addWidget(nplView);
    l->addWidget(f);
    l->addWidget(t);

    l->setContentsMargins(0,0,0,0);



    nplViewDock=new QDockWidget(this);
    nplViewDock->setWindowTitle("Playlist");
    nplViewDock->setObjectName("Playlist");
    nplViewDock->setWidget(w);
//      nplViewDock->setPalette(player::pal);
//      nplViewDockT=new QWidget(this);


}

void mainWindow::toolBarInit()
{
//      KToolBar *toolBarS=new KToolBar(this);
    toolBar=new KToolBar(this);

    QPalette p=QApplication::palette();

//      p.setColor(QPalette::Base,p.color(QPalette::Window) );

    toolBar->setPalette(p);
    toolBar->setAutoFillBackground(true);
//      toolBar->setPalette(QApplication::palette());


    toolBar->setObjectName("buttonsToolBar");
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );
    toolBar->setIconSize(ICONZISE );
//      toolBar->setMovable(true);
//       toolBar->setIconSize(QSize(30,30) );

    previousAction = new QAction(  decor.previous() ,"play previous", this );
    toolBar->addAction( previousAction );
    connect(previousAction,SIGNAL(triggered( bool)),&engine,SLOT(previous() ) );

    playAction = new QAction(  decor.play(),"play-pause", this );
    toolBar->addAction( playAction );
    connect(playAction,SIGNAL(triggered( bool)),&engine,SLOT(playPause() ) );

    nextAction = new QAction(  decor.next(),"play next", this );
    toolBar->addAction( nextAction );
    connect(nextAction,SIGNAL(triggered( bool)),&engine,SLOT(next() ) );


    volume = new Phonon::VolumeSlider(engine.getAudio(),this );
    volume->setFixedWidth(150);
    volume->setMuteVisible(false);
    slider = new Phonon::SeekSlider(this);

    slider->setMediaObject(engine.getMediaObject() );
    slider->setIconVisible(false);

//      QVBoxLayout *vLayout = new QVBoxLayout();
//      QHBoxLayout *hLayout = new QHBoxLayout();

//       vLayout->setContentsMargins(0,0,5,0);
//       hLayout->addWidget(toolBar);
//       hLayout->addStretch();
//       hLayout->addWidget(volume);
//      hLayout->addSpacing(5);
//      vLayout->addWidget(slider);
//      vLayout->addLayout(hLayout);

//      vLayout->addSpacing(5);

//      QWidget *w=new QWidget(this);
//      w->setLayout(vLayout);
    toolBar->addWidget(slider);
    toolBar->addWidget(volume);
//      toolBarS->addWidget(slider);
//      addToolBar ( Qt::BottomToolBarArea,toolBarS);
//      slider = new Phonon::SeekSlider(this);
//
//      timeLabel = new QLabel(this);
//      progressLabel = new QLabel(this);
//
//      volume = new Phonon::VolumeSlider(soundEngine->getAdio() );
//      volume->setFixedWidth(120);
//
}

void mainWindow::lockDock()
{
    const QFlags<QDockWidget::DockWidgetFeature> features = QDockWidget::NoDockWidgetFeatures;

    conTreeDock->setFeatures(features);
//      conTreeDock->setTitleBarWidget(0);

    conViewDock->setFeatures(features);
    conViewDock->setTitleBarWidget(conViewDockT);



    nplViewDock->setFeatures(features);
//      nplViewDock->setTitleBarWidget(nplViewDockT);

    infoDock->setFeatures(features);
    infoDock->setTitleBarWidget(infoDockT);

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
//       playlistContent *pl=new playlistContent();

    contentHandlr->addContent(l);
    contentHandlr->addContent(f);
    contentHandlr->addContent(c);
//       contentHandlr->addContent(v);
}

void mainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}

void mainWindow::writeSettings()
{
// 	  QString ini_path(getenv("HOME"));
// 	  ini_path += "/.aman/";
//       QSettings::setPath(QSettings::IniFormat,QSettings::SystemScope,ini_path );
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,"player.org","player");

    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();

    QStringList l=npList.getList();
    settings.setValue("playlist",QVariant(l));
//      settings.setValue("geometry", saveGeometry());

}

void mainWindow::readSettings()
{
//      QString ini_path(getenv("HOME"));
//      ini_path += "/.aman/";

//      QSettings::setPath(QSettings::IniFormat,QSettings::SystemScope,ini_path);
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,"player.org","player");
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();

//      qDebug()<<"edo";
    QStringList l=settings.value("playlist",QStringList() ).toStringList();
//      qDebug()<<l;
//      npList.addMediaList(l,0);
//      qDebug()<<"edo";
}


