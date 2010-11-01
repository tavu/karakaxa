#include"playlistContent.h"
#include<QHBoxLayout>

// #include <KCategorizedView>
playlistContent::playlistContent(QWidget *parent)
        :abstractContent(parent)
{
    toolBarInit();

    stack=new QStackedWidget(this);
    treeV=new QTreeView(this);
    trackV=new QTreeView(this);
    smartPl=new smartPlaylist(treeV,trackV,toolBar);
    smartPl->start();

//      smartPlaylistCreator *c=new smartPlaylistCreator(this);
//      c->show();
    stack->addWidget(treeV);
    stack->addWidget(trackV);


//      smartInit();

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(toolBar);
    layout->addWidget(stack);

    setLayout(layout);


}

void playlistContent::update(const int n)
{
//       if(n==0)
    smartPl->start();
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
//     connect( backAction, SIGNAL( triggered( bool) ), lc, SLOT( goToArtist() ) );


    forwardAction = new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
//     connect( forwardAction, SIGNAL( triggered( bool) ), lc, SLOT( goToAlbum() ) );

}

void playlistContent::smartInit()
{
//      toolBar1=new KToolBar(this);
//    /* */ QAction *add=new QAction(KIcon("list-add"),tr("&Add"),this);
//      QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);


}
