#include"playlistContent.h"
#include<QHBoxLayout>

#define XMLFILE QString("playlists.xml")

playlistContent::playlistContent(QWidget *parent)
        :abstractContent(parent),
        needUpdate(false)
{    
    stack=new QStackedWidget(this);
    treeV=new myTreeView(this);
    treeV->setFrameShape(QFrame::StyledPanel);
    treeV->setUniformRowHeights(false);
//     treeV->setIconSize(QSize ());
    
    treeV->setHeaderHidden(true);
    
    trackV=new songView(this,"playlistView");
    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);
    trackV->setNotHide(TITLE);
    trackV->setFrameShape(QFrame::StyledPanel);
    
    treeV->setRootIsDecorated(true);
    
    treeModel=new myStandardModel(this);
             
    QFile file(player::config.saveLocation()+XMLFILE);    
    QDomDocument doc;
    if(doc.setContent(&file,true) )
    {
	QDomNode n = doc.firstChild();
	if(n.isElement() && n.toElement().tagName()==QString("folder") )
	{
	    smHead=new folderItem(n.toElement() );
	}
	else
	{
	    smHead=new folderItem(tr("Smart playlist") );
	}	  
    }
    else
    {
	smHead=new folderItem(tr("Smart playlist") );
    }            
    plHead=new playlistFolder("Playlist");
    plHead->setSizeHint(QSize(40,30) );
    smHead->setSizeHint(QSize(40,30) );
    treeModel->appendRow(plHead);
    treeModel->appendRow(smHead);
    
    
    plModel=new playlistModel(this);
    smpModel=new songModel(this);
    
    proxyM=new QSortFilterProxyModel(this);
    proxyM->setSourceModel(treeModel);    
    treeV->setModel(proxyM);
    
    proxyM->sort(0);
    
    stack->addWidget(treeV);
    stack->addWidget(trackV);

    toolBarInit();
    
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(toolBar);
    layout->addWidget(stack);

    setLayout(layout);
    
    connect(treeV,SIGNAL(showContextMenu(QModelIndex) ),SLOT(contextMenuSlot(QModelIndex)) );
    connect(treeV, SIGNAL(activated(QModelIndex)), this, SLOT(activationSlot(QModelIndex) )) ;
    
    
    addFolderAction=new QAction(KIcon("folder") ,"create folder",this);
    createSmpAction=new QAction(KIcon("list-add"),"create smart playlist",this);
    removeAction=new QAction(KIcon("list-remove"),"remove",this);
    editSmpAction=new QAction(KIcon("document-edit"),"edit",this);
    
    connect(addFolderAction,SIGNAL(triggered(bool)),this,SLOT(addFolderSlot()));
    connect(createSmpAction,SIGNAL(triggered(bool)),this,SLOT(createSmpSlot()));
    connect(editSmpAction,SIGNAL(triggered(bool)),this,SLOT(editSmpSlot()));
    connect(removeAction,SIGNAL(triggered(bool)),this,SLOT(removeSlot()));
    
    connect(&db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(updateQueries() ) );
    connect(&db,SIGNAL(changed()),this,SLOT(updateQueries() ) );
    
    connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(save() ) );
}

void playlistContent::updateQueries()
{
    if(trackV->model()==smpModel)
    {
	smpModel->refresh();
	needUpdate=false;
    }
    else
    {      
	needUpdate=true;
    }
}

void playlistContent::removeSlot()
{
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex());
//     treeModel->removeRow(index.row(),index.parent());  
    QStandardItem *i=treeModel->itemFromIndex(index);
//     i=i->parent();	

    myStandardItem *item=static_cast<myStandardItem*>(i->parent());
    item->removeR(i->row());    
}


playlistContent::~playlistContent()
{   
}

void playlistContent::update(const int n)
{
/*    if(n==0 && current==1)
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
    }*/
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

void playlistContent::addFolderSlot()
{
    folderItem *f=new folderItem(tr("folder") );
    
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex());
    QStandardItem *i=treeModel->itemFromIndex(index);
    if(i->type()!=FOLDER_ITEM)
    {
	i=i->parent();	
    }
    
    myStandardItem *item=static_cast<myStandardItem*>(i);
    
    item->addRow(f);
    treeV->expand( proxyM->mapFromSource(treeModel->indexFromItem(i) ) );
    treeV->edit( proxyM->mapFromSource( treeModel->indexFromItem(f) ) );
}

void playlistContent::createSmpSlot()
{
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex() );
    
    myStandardItem *headItem=treeModel->head(index);
    
    if(headItem!=smHead)
    {
	return ;
    }
    
    smartPlaylistCreator *c=new smartPlaylistCreator(this);    
    c->exec();

    if(c->result()!= QDialog::Accepted)
    {
	return ;
    }

    smplaylistItem *item=c->item();
    
    if(item==0)
    {
	return;
    }
    
    qDebug()<<index;
    QStandardItem *i=treeModel->itemFromIndex(index);
    qDebug()<<"type "<<i->type();
    if(i->type()!=FOLDER_ITEM)
    {
	i=i->parent();	
    }
    qDebug()<<"type "<<i;
    
    myStandardItem *smItem=static_cast<myStandardItem*>(i);
    
    smItem->addRow(item);
    
    delete c;
}

void playlistContent::editSmpSlot()
{
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex());
    QStandardItem *item=treeModel->itemFromIndex(index);
    if(item==0 || item->type() != SMARTPL_ITEM)
    {
	return ;	
    }
    
    smplaylistItem *i=static_cast<smplaylistItem*>(item);
    
    smartPlaylistCreator *c=new smartPlaylistCreator(i,this);
    
    c->exec();
    if(c->result()!= QDialog::Accepted)
    {
	return ;
    }
    
    smplaylistItem *newItem=c->item();

    if(newItem==0)
    {
	return;
    }
    item=i->parent();
    myStandardItem *p=static_cast<myStandardItem*>(item);
    
    p->removeR(i->row());
    p->addRow(newItem);

    delete c;
}


void playlistContent::activationSlot(QModelIndex in)
{
    //if the activation was by right click we do not show the playlist but we show a context menu.
    //this menu would be shown by contextmenuevent function
  
    QModelIndex index=proxyM->mapToSource(in);
    QStandardItem *item=treeModel->itemFromIndex(index);
    
    if(item->type()==SMARTPL_ITEM)
    {
	trackV->setModel(smpModel);
	if(needUpdate)
	{
	    smpModel->refresh();
	}
	  
	smpModel->setFilter(item->data(ITEM_ROLE).toString());
	stack->setCurrentIndex(1);
    }
    else if(item->type()==PLAYLIST_ITEM)
    {
	trackV->setModel(plModel);
	plModel->setPlPath(item->data(ITEM_ROLE).toString() );
	stack->setCurrentIndex(1);
    }
    else if(item->type()==FOLDER_ITEM || item->type()==PLAYLIST_FOLDER)
    {
	if(treeV->isExpanded(in) )
	{
	    treeV->collapse(in);
	}
	else
	{
	    treeV->expand(in);
	}
    }
        
}

void playlistContent::contextMenuSlot(QModelIndex in)
{          
    if(!in.isValid() )
    {
	return ;
    }
    
    QModelIndex index=proxyM->mapToSource(in);
    
    QMenu *menu=new QMenu(this); 	
    
    QStandardItem *item=treeModel->itemFromIndex(index);
    
    //if we are on smart Playlist tree add the create smart playlist action
    if(treeModel->head(index)==smHead)
    {
	menu->addAction(addFolderAction);	
	menu->addSeparator();
	
	if(item->type()==SMARTPL_ITEM)
	{
	    menu->addAction(editSmpAction);
	}
	menu->addAction(createSmpAction);
	if(index.parent().isValid() )//if it's not a top level item
	{	
	    menu->addAction(removeAction);
	}
    }
    
    if(treeModel->head(index)==plHead)
    {
	if(index.parent().isValid() )//if it's not a top level item
	{	
	    menu->addAction(removeAction);
	}	
    }     
	
    menu->popup( QCursor::pos() );
}

void playlistContent::save()
{
    qDebug()<<"saving";
    QDomDocument doc;
    QDomElement root=doc.createElement("smartPlaylist");
//     root.appendChild(smHead->xml() );
    doc.appendChild(smHead->xml());

    
    QFile file(player::config.saveLocation()+XMLFILE);
    file.copy(player::config.saveLocation()+XMLFILE+QString(".bak") );
    if ( file.open( QIODevice::WriteOnly ) ) 
    {
	QTextStream ts(&file);
	ts << doc.toString();	
// 	qDebug()<<doc.toString();
	file.close();
    }
    else
    {
	player::statusBar.showMessage(tr("Unable to save the playlist"));
    }
    
    
}




