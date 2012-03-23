#include"playlistContent.h"
#include<QHBoxLayout>
#include"items.h"
#include"sortProxyModel.h"
#include<QFile>
#include<queries/fileQueryGrt.h>
#define XMLFILE QString("playlists.xml")

using namespace core;
playlistContent::playlistContent(QWidget *parent)
        :abstractContent(parent),
        needUpdate(false),
        trackProxy(0)
{    
    quer=new database::filesQueryGrt(this);
    smItem=new views::trackModelItem();
    smItem->setQueryG(quer);
    
    stack=new QStackedWidget(this);
    
    treeV=new views::treeView(this);
    treeV->setFrameShape(QFrame::StyledPanel);
    treeV->setUniformRowHeights(false);    
    treeV->setHeaderHidden(true);
    treeV->setSelectionMode(QAbstractItemView::SingleSelection);
    treeV->setRootIsDecorated(true);
    treeV->setAnimated(true);
    
    
    trackV=new views::treeView(this);
    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);
    trackV->setNotHide(TITLE);
    trackV->setFrameShape(QFrame::StyledPanel);
    trackV->setAcceptDrops(true);
    trackV->setDragDropMode(QAbstractItemView::DragDrop);
    
    treeModel=new standardModel(this);    
                   
    
    plModel=new views::filePlaylistModel(this);
    smpModel=new standardModel(this);
    
    smpModel->setHeadItem(smItem);
    
    proxyM=new sortProxyModel(this);
    proxyM->setSourceModel(treeModel);
    proxyM->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyM->setSortRole(Qt::DisplayRole);    

    
    treeV->setModel(proxyM);        
    
    stack->addWidget(treeV);
    stack->addWidget(trackV);
       
    
    iconL.setPixmap(views::decor->tagIcon(-1).pixmap(20,20) );
    textL.setText(tr("Playlists") );
    QFont font;
    font.setPointSize(13);
    font.setBold(true);
    textL.setFont(font);
    
    toolBarInit();
    
    
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addWidget(&iconL);
    hLayout->addWidget(&textL);
    hLayout->addStretch();
    
    layout->addLayout(hLayout);
    layout->addWidget(stack);

    setLayout(layout);
    
    connect(treeV,SIGNAL(showContextMenu(QModelIndex,QModelIndexList) ),this,SLOT(contextMenuSlot(QModelIndex)) );
    connect(trackV,SIGNAL(showContextMenu(QModelIndex,QModelIndexList) ),this,SLOT(contextMenuForTracks(QModelIndex,QModelIndexList)) );
    connect(treeV, SIGNAL(activated(QModelIndex)), this, SLOT(activationSlot(QModelIndex) )) ;
    
    
    addFolderAction=new QAction(KIcon("folder") ,"create folder",this);
    createSmpAction=new QAction(KIcon("list-add"),"create smart playlist",this);
    removeAction=new QAction(KIcon("list-remove"),"remove",this);
    editSmpAction=new QAction(KIcon("document-edit"),"edit",this);
    
    connect(addFolderAction,SIGNAL(triggered(bool)),this,SLOT(addFolderSlot()));
    connect(createSmpAction,SIGNAL(triggered(bool)),this,SLOT(createSmpSlot()));
    connect(editSmpAction,SIGNAL(triggered(bool)),this,SLOT(editSmpSlot()));
    connect(removeAction,SIGNAL(triggered(bool)),this,SLOT(removeSlot()));
        
//     connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(save() ) );
    
    stack->setCurrentWidget(treeV);

    readSettings();
    smHead->setSizeHint(QSize(40,30) );
    treeModel->appendRow(smHead);

    plHead=new playlistFolder("Playlist");
    plHead->setSizeHint(QSize(40,30) );
    treeModel->appendRow(plHead);


    
    proxyM->sort(0,Qt::AscendingOrder);
}

void playlistContent::readSettings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "playlistContent");
    smpState=group.readEntry( "smartPLState", QByteArray() ) ;
    plState=group.readEntry( "playlistState", QByteArray() );

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
}

void playlistContent::updateQueries()
{
    if(trackV->model()==smpModel)
    {
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
    treeModel->removeRow(index.row(),index.parent());
}


playlistContent::~playlistContent()
{
    writeSettings();
}

void playlistContent::activated(const int n)
{

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
    searchLine->setClickMessage(tr("Search") );
    searchLine->setFixedWidth(300);
    searchLine->setVisible(false);
    searchAction=toolBar->addWidget(searchLine);
        
    connect(searchLine,SIGNAL(textChanged (const QString&)),this,SLOT(search() ) );
    connect(searchLine,SIGNAL(clearButtonClicked() ),this,SLOT(search() ) );
}

void playlistContent::back()
{
    stack->setCurrentIndex(0);
    searchAction->setVisible(false);
    textL.setText(tr("Playlists") );
}

void playlistContent::forward()
{
    if(trackProxy==0)
    {
        return ;
    }
    stack->setCurrentIndex(1);
    
    if(trackProxy->sourceModel()==smpModel)
    {
        if(quer->needUpdate() )
        {
            quer->select();
        }
        trackV->header()->restoreState(smpState);
    }
    else
    {
        trackV->header()->restoreState(plState);
    }
    trackV->setModel(trackProxy);
    textL.setText(textS);
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
    
//     proxyM->sort(0,Qt::AscendingOrder);
    treeV->expand( proxyM->mapFromSource(treeModel->indexFromItem(i,0) ) );    
    treeV->edit( proxyM->mapFromSource( treeModel->indexFromItem(f,0) ) );
    proxyM->sort(0,Qt::AscendingOrder);
    
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
    proxyM->sort(0,Qt::AscendingOrder);
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
    
    proxyM->sort(0,Qt::AscendingOrder);
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
        if(trackProxy!=0)
        {
            plState=trackV->header()->saveState();
            delete trackProxy;
        }
        smplaylistItem  *i= static_cast<smplaylistItem*>(item);
        trackProxy=new QSortFilterProxyModel(this);
        trackProxy->setSourceModel(smpModel);
        trackProxy->setDynamicSortFilter(false);
        trackProxy->setFilterKeyColumn(-1);
        trackProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        trackProxy->setSourceModel(smpModel);

        
        database::abstractQuery *q=i->query();
        quer->setQuery(q->clone() );
        quer->select();
        textS=item->data(0,Qt::DisplayRole).toString();
        trackV->setSortingEnabled(true);
        forward();
    }
    else if(item->type()==PLAYLIST_ITEM)
    {
        if(trackProxy!=0)
        {
            smpState=trackV->header()->saveState();
            delete trackProxy;
        }
        
        trackProxy=new QSortFilterProxyModel(this);
        trackProxy->setDynamicSortFilter(false);
        trackProxy->setFilterKeyColumn(-1);
        trackProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        trackProxy->setSourceModel(smpModel);
        trackProxy->setSourceModel(plModel);

        trackV->setSortingEnabled(false);
        plModel->setPlPath(item->data(0,ITEM_ROLE).toString() );
        textS=item->data(0,Qt::DisplayRole).toString();
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

void playlistContent::writeSettings()
{    
    QFile file(core::config->saveLocation()+XMLFILE);
    file.copy(core::config->saveLocation()+XMLFILE+QString(".bak") );
    if ( file.open( QIODevice::WriteOnly ) ) 
    {
	   QTextStream ts(&file);
	   ts << doc.toString();
	   file.close();
    }
    else
    {
        core::status->addError(tr("Unable to save the playlist"));
        core::status->addErrorP(tr("Unable to save the playlist"));
    }

    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "playlistContent" );    
    group.writeEntry( "smartPLState", QVariant(smpState));
    group.writeEntry( "playlistState", QVariant(plState));
    group.config()->sync();
    
    
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
    trackProxy->setFilterFixedString(s);
}

void playlistContent::contextMenuForTracks(QModelIndex index, QModelIndexList list)
{
    if(!index.isValid() )
    {
        return ;
    }
    
    QUrl u=index.data(URL_ROLE).toUrl();    
    QMenu *menu=new QMenu(this);
    
    QAction *act=new QAction(KIcon("document-edit"),tr("edit"),menu );
    connect(act,SIGNAL(triggered(bool)),trackV,SLOT(editCurrent()) );
    menu->addAction(act);
    
    QList<QUrl> urls=views::treeView::getUrls(list);
    
    core::contentHdl->contextMenu(menu,KUrl(u),urls );
    if(!menu->isEmpty() )
    {
        menu->exec( QCursor::pos() );
    }
    menu->deleteLater();    
}