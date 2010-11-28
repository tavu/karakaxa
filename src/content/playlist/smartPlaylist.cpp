#include"smartPlaylist.h"
#include<KIcon>

smartPlaylist::smartPlaylist(playlistContent *pl)
    :QObject(pl),
    current(0)
{
    plContent=pl;
    trackM=new songModel(plContent->treeV);

    QToolBar *toolBar=new QToolBar("smart playlist toolbar",plContent);

    QAction *addAction=new QAction(KIcon("list-add"),tr("&Add"),this);
    QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);
    toolBar->addAction(addAction);
    toolBar->addAction(removeAction);
    widgetAction = plContent->toolBar->addWidget(toolBar);

    smModel=new smartPlaylistModel(this);            
    connect(addAction, SIGNAL(triggered()), this, SLOT(addPl() )) ;
    
//      connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

    widgetAction->setVisible(false);
}

void smartPlaylist::goToPlaylist(QModelIndex i) 
{
//      trackV->setNotHide(TITLE);     
     trackM->setFilter(i.data(Qt::UserRole).toString());
     plContent->trackV->setModel(trackM);
     plContent->stack->setCurrentIndex(1);
}

smartPlaylist::~smartPlaylist()
{
//     delete toolBar;
}

void smartPlaylist::addPl()
{
    smartPlaylistCreator *c=new smartPlaylistCreator();
    c->exec();
    QString q=c->query();
    if (q.isEmpty() )	return ;

    smartPlaylistModelItem *item=new smartPlaylistModelItem(c->name(),q);
    smModel->append(item);    
    
    delete c;
}


void smartPlaylist::activate()
{
    plContent->treeV->setModel(smModel);    
    plContent->trackV->setModel(trackM);
    widgetAction->setVisible(true);
    plContent->stack->setCurrentIndex(current);
    connect(plContent->treeV, SIGNAL(activated(QModelIndex)), this, SLOT(goToPlaylist(QModelIndex) )) ;
}

void smartPlaylist::deActivate()
{
    widgetAction->setVisible(false);
    plContent->treeV->disconnect();
    current=plContent->stack->currentIndex();
}

