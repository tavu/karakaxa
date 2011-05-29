#include"playlistContent.h"
#include<QHBoxLayout>
#include"items.h"

#define XMLFILE QString("playlists.xml")

using namespace core;
playlistContent::playlistContent(QWidget *parent)
        :abstractContent(parent),
        needUpdate(false)
{    
    quer=new queryGrt(this);
    smItem=new views::trackModelItem();
    smItem->setQueryG(quer);
    
    stack=new QStackedWidget(this);
    
    treeV=new views::treeView(this);
    treeV->setFrameShape(QFrame::StyledPanel);
    treeV->setUniformRowHeights(false);    
    treeV->setHeaderHidden(true);
    treeV->setSelectionMode(QAbstractItemView::SingleSelection);
    treeV->setRootIsDecorated(true);
    
    trackV=new views::treeView(this,"playlistView");
    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);
    trackV->setNotHide(TITLE);
    trackV->setFrameShape(QFrame::StyledPanel);
        
    
    treeModel=new standardModel(this);    
             
    QFile file(core::config->saveLocation()+XMLFILE);        
    QDomElement el;
    if(doc.setContent(&file,true) )
    {
	el = doc.firstChildElement ("spartPlaylists");
    }
	
    if(el.isNull() )
    {
	el=doc.createElement("spartPlaylists");
	doc.appendChild(el);      
    }
    
    smHead=new smplalistHead(el);
    smHead->setSizeHint(QSize(40,30) );
    treeModel->appendRow(smHead);
    
    plHead=new playlistFolder("Playlist");
    plHead->setSizeHint(QSize(40,30) );
    
    
    treeModel->appendRow(plHead);    
    
    
    plModel=new playlistModel(this);
    smpModel=new standardModel(this);
    
    smpModel->setHeadItem(smItem);
    
    proxyM=new QSortFilterProxyModel(this);
    proxyM->setSourceModel(treeModel);
//     proxyM->setDynamicSortFilter(true);
    
    trackProxy=new QSortFilterProxyModel(this);
    trackProxy->setDynamicSortFilter(true);
    trackProxy->setFilterKeyColumn(-1);
    trackProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    
    trackV->setModel(trackProxy);
    
    treeV->setModel(proxyM);
    
//     proxyM->sort(0);
    
    stack->addWidget(treeV);
    stack->addWidget(trackV);

    toolBarInit();
    
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(stack);

    setLayout(layout);
    
    connect(treeV,SIGNAL(showContextMenu(QModelIndex) ),this,SLOT(contextMenuSlot(QModelIndex)) );
    connect(treeV, SIGNAL(activated(QModelIndex)), this, SLOT(activationSlot(QModelIndex) )) ;
    
    
    addFolderAction=new QAction(KIcon("folder") ,"create folder",this);
    createSmpAction=new QAction(KIcon("list-add"),"create smart playlist",this);
    removeAction=new QAction(KIcon("list-remove"),"remove",this);
    editSmpAction=new QAction(KIcon("document-edit"),"edit",this);
    
    connect(addFolderAction,SIGNAL(triggered(bool)),this,SLOT(addFolderSlot()));
    connect(createSmpAction,SIGNAL(triggered(bool)),this,SLOT(createSmpSlot()));
    connect(editSmpAction,SIGNAL(triggered(bool)),this,SLOT(editSmpSlot()));
    connect(removeAction,SIGNAL(triggered(bool)),this,SLOT(removeSlot()));
        
    connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(save() ) );
    
    stack->setCurrentWidget(treeV);    
        
//     test();
//     treeModel->modelReset();
}

void playlistContent::updateQueries()
{
    if(trackV->model()==smpModel)
    {
// 	smpModel->refresh();
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
    treeModel->removeRow(index.row(),index.parent());
//     standardItem *i=treeModel->itemFromIndex(index);
//     i=i->parent();	

//     standardItem *item=i->parent();
//     item->removeR(i->row());    
}


playlistContent::~playlistContent()
{   
}

void playlistContent::activated(const int n)
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
//     test();
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
    
    forwardAction =new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
    connect( forwardAction, SIGNAL( triggered( bool) ),this, SLOT( forward() ) );   
    
    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);
    
    searchLine =new KLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage("Search");
    searchLine->setFixedWidth(300);
    searchLine->setVisible(false);
    searchAction=toolBar->addWidget(searchLine);
        
    connect(searchLine,SIGNAL(editingFinished () ),this,SLOT(search() ) );
    connect(searchLine,SIGNAL(clearButtonClicked() ),this,SLOT(search() ) );
}

void playlistContent::back()
{
    stack->setCurrentIndex(0);
    searchAction->setVisible(false);
}

void playlistContent::forward()
{
    stack->setCurrentIndex(1);
    if(trackProxy->sourceModel()==smpModel && quer->needUpdate() )
    {
	quer->select();
    }
    searchAction->setVisible(true);
}

void playlistContent::addFolderSlot()
{
    folderItem *f=new folderItem(doc,tr("folder") );
    
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex() );
    standardItem *i=treeModel->itemFromIndex(index);
    if(i->type()!=FOLDER_ITEM)
    {
	i=i->parent();	
    }    
    
    i->appendRow(f);
    
    treeV->expand( proxyM->mapFromSource(treeModel->indexFromItem(i,0) ) );
    treeV->edit( proxyM->mapFromSource( treeModel->indexFromItem(f,0) ) );

    
}

void playlistContent::createSmpSlot()
{
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex() );
    
    standardItem *item=treeModel->itemFromIndex(index);
    
    if(head(item)!=smHead)
    {
	return;
    }
    
    smartPlaylistCreator *c=new smartPlaylistCreator(doc,this);    
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
    
    if(item->type()!=FOLDER_ITEM)
    {
	item=item->parent();	
    }    
    
    item->appendRow(newItem);
    
    delete c;        
}

void playlistContent::editSmpSlot()
{
    QModelIndex index=proxyM->mapToSource(treeV->currentIndex());
    standardItem *item=treeModel->itemFromIndex(index);
    if(item==0 || item->type() != SMARTPL_ITEM)
    {
	return ;
    }    
    
    smartPlaylistCreator *c=new smartPlaylistCreator(static_cast<smplaylistItem*>(item),this);
    
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
    standardItem *parent=item->parent();    
        
    parent->removeRow(item->row());
    parent->appendRow(newItem);

    delete c;
}


void playlistContent::activationSlot(QModelIndex in)
{
    //if the activation was by right click we do not show the playlist but we show a context menu.
    //this menu would be shown by contextMenuEvent function
  
    QModelIndex index=proxyM->mapToSource(in);
    standardItem *item=treeModel->itemFromIndex(index);
    
    if(item==0)
    {
	return;
    }
    
    if(item->type()==SMARTPL_ITEM)
    {
	smplaylistItem  *i= static_cast<smplaylistItem*>(item);
	trackProxy->setSourceModel(smpModel);
	queryGrt::abstractQuery *q=i->query();
	quer->setQuery(q->clone() );
	quer->select();
	forward();
    }
    else if(item->type()==PLAYLIST_ITEM)
    {
	trackProxy->setSourceModel(plModel);
	plModel->setPlPath(item->data(0,ITEM_ROLE).toString() );
	forward();
    }
    else if(item->type()==FOLDER_ITEM || item->type()==PLAYLIST_FOLDER )
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
    
    standardItem *item=treeModel->itemFromIndex(index);
    
    //if we are on smart Playlist tree add the create smart playlist action
    if(head(item)==smHead)
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
    
    if(head(item)==plHead)
    {
	if(index.parent().isValid() )//if it's not a top level item
	{	
	    menu->addAction(removeAction);
	}	
    }     
	
    if( !menu->isEmpty() )
    {
	menu->popup( QCursor::pos() );
    }
}

void playlistContent::save()
{
    qDebug()<<"saving";    
    
    QFile file(core::config->saveLocation()+XMLFILE);
    file.copy(core::config->saveLocation()+XMLFILE+QString(".bak") );
    if ( file.open( QIODevice::WriteOnly ) ) 
    {
	QTextStream ts(&file);
	ts << doc.toString();	
	qDebug()<<smHead->xml().hasChildNodes();
// 	qDebug()<<doc.toString();
	file.close();
    }
    else
    {
	core::status->addError(tr("Unable to save the playlist"));
	core::status->addErrorP(tr("Unable to save the playlist"));
    }
    
    
}

standardItem* playlistContent::head( standardItem *item)
{
    standardItem *parent=item;
    while(parent->parent()!=0)
    {
	parent=parent->parent();
    }
    return parent;
}

void playlistContent::search()
{
    QString s=searchLine->text();
    QString search;
    
    trackProxy->setFilterFixedString(s);
}