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
    toolBar->addAction(addAction);
    
    QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);
    toolBar->addAction(removeAction);    
    
    QAction *addFolderAction=new QAction(KIcon("folder-new"),tr("&new folder"),this);
    toolBar->addAction(addFolderAction);
    
    widgetAction = plContent->toolBar->addWidget(toolBar);

    smModel=new smartPlaylistModel(this);            
    connect(addAction, SIGNAL(triggered()), this, SLOT(addPl() ));
    connect(addFolderAction, SIGNAL(triggered()), this, SLOT(addFolder() ));
//      connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

    widgetAction->setVisible(false);
}

void smartPlaylist::goToPlaylist(QModelIndex i) 
{
     QStandardItem *f=smModel->itemFromIndex(i);
     if(f==0)
     {
	return ;
     }
     smartPlaylistModelItem *item=static_cast<smartPlaylistModelItem *>(f);
     if(item->isFolder())
     {
	return ;
     }
     
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

    if(c->result()==QDialog::Rejected)
    {
//  	return;
    }
    
    smartPlaylistModelItem *item=c->item();
    if(item==0)
    {
	return;
    }
    
    QModelIndex i=plContent->treeV->currentIndex();
    
    qDebug()<<"EDOODTDO";
    smModel->append(item,i);
    
    delete c;
}

void smartPlaylist::addFolder()
{
    smartPlaylistModelItem *item=new smartPlaylistModelItem("folder",true);        
    QModelIndex i=plContent->treeV->currentIndex();
    
    smModel->append(item,i);
    i=smModel->indexFromItem(item);
    QModelIndex parent=i.parent();
    plContent->treeV->expand(parent);
    plContent->treeV->edit(i);
}




void smartPlaylist::activate()
{
    plContent->treeV->setModel(smModel);
    plContent->treeV->setRootIsDecorated(true);
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

