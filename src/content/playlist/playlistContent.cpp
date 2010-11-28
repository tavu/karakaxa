#include"playlistContent.h"
#include<QHBoxLayout>
#include"smartPlaylist.h"
#include"filePlaylist.h"
// #include <KCategorizedView>
playlistContent::playlistContent(QWidget *parent)
        :abstractContent(parent),
        current(0)
{    
    stack=new QStackedWidget(this);
    treeV=new myTreeView(this);
    trackV=new songView(this);
    
    stack->addWidget(treeV);
    stack->addWidget(trackV);

    toolBarInit();
    
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(toolBar);
    layout->addWidget(stack);

    setLayout(layout);
    
    addChild(QString(tr("Playlist")) );
    addChild(QString(tr("Smart Playlist")) );

    smPl=new smartPlaylist(this);
    filePl=new filePlaylist(this);
    
    filePl->activate();
}

void playlistContent::update(const int n)
{
    if(n==0 && current==1)
    {
	qDebug()<<"DEACTIVATING smpl";
	smPl->deActivate();
	filePl->activate();
	current=n;
    }
    if(n==1 && current==0)
    {
	qDebug()<<"DEACTIVATING filepl";
	filePl->deActivate();
	smPl->activate();
	current=n;
    }
}

QString playlistContent::name() const
{
    return QString(tr("Playlist") );
}

void playlistContent::toolBarInit()
{
    toolBar=new KToolBar(this);
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );

    backAction = new QAction( KIcon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );
    connect( backAction, SIGNAL( triggered( bool) ),this, SLOT( back() ) );
}

void playlistContent::back()
{
    stack->setCurrentIndex(0);
}


