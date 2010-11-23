#include"smartPlaylist.h"
#include<KIcon>
smartPlaylist::smartPlaylist(QTreeView *treeV,QTreeView *trackV,KToolBar *tb)
{
    this->treeV=treeV;
    this->trackV=trackV;
    this->tb=tb;

    toolBar=new QToolBar("smart playlist toolbar");

    QAction *addAction=new QAction(KIcon("list-add"),tr("&Add"),this);
    QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);
    toolBar->addAction(addAction);
    toolBar->addAction(removeAction);

    model=new QStandardItemModel(this);

    connect(addAction, SIGNAL(triggered()), this, SLOT(addPl() )) ;
//      connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));
}

smartPlaylist::~smartPlaylist()
{
    delete toolBar;
}

void smartPlaylist::addPl()
{
//      t-currentIndex ()
    smartPlaylistCreator *c=new smartPlaylistCreator();
    c->show();
    connect(c,SIGNAL(closed(QString,QString)),this,SLOT(newPl(QString,QString) ) );
}

void smartPlaylist::newPl(QString query,QString name)
{
    if (query.isEmpty() )	return ;

    QStandardItem *item = new QStandardItem(name);

    model->setItem(0,0,item);

    item = new QStandardItem(query);

    model->setItem(0,1,item);
}

void smartPlaylist::start()
{
    treeV->setModel(model);
    tb->addWidget(toolBar);
//      trackV->setModel(trackM);
}
