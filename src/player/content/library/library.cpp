#include"library.h"
#include<QLabel>
#include<QHBoxLayout>
#include <QSpacerItem>
#include<views.h>
#include<database/queries/provider/queryProvider.h>
#include<core/standardModel/standardModel.h>
#include<views/models/libraryModel/tagItemHead.h>
#include"artistDelegate.h"
#include<views/models/urlRole.h>
#include<views/models/libraryModel/tagItem.h>
#include "albumView.h"
using namespace core;

library::library(QWidget *parent)
        :abstractContent(parent)
{
    addSubmenu(QString(tr("Artist")),views::decor->tagIcon(Basic::ARTIST) );
    stack=new QStackedWidget(this);

  
    searchQ=new database::matchQuery(database::OR);
    toolBarInit();
    QVBoxLayout *layout = new QVBoxLayout();


    artistV=new QListView(this);
    artistV->setViewMode(QListView::ListMode);
//     artistV->setFlow(QListView::LeftToRight);
    artistV->setResizeMode(QListView::Adjust);
    artistV->setWrapping(true);
    artistV->setUniformItemSizes(true);
    artistV->setWordWrap(true);
    artistV->setLayoutMode(QListView::Batched);
//     artistV->setBatchSize(5);
    artistV->setItemDelegate(new artistDelegate(artistV) );    
    artistM=new standardModel(this);
    artistH=new views::tagItemHead(this);
    artistH->addTag(Basic::ALBUM_ARTIST);    
    artistH->fetchMore();
    artistM->setHeadItem(artistH);
    artistV->setModel(artistM);
    stack->addWidget(artistV);    
    

    view= new albumView("albumViewLibrary",this);

    albumTrackM=new standardModel(this);
    albumTrackM->setProperty(SPAN_PROP,true);
    view->setModel(albumTrackM);
    albumH=new views::tagItemHead(this);
    albumTrackM->setHeadItem(albumH);
    albumH->addTag(Basic::ALBUM);
    albumH->addTag(Basic::FILES);
    stack->addWidget(view);
    artistL=new QLabel(this);
    artistL->setText(tr("Artist") );
    QFont f=artistL->font();
    f.setBold(true);
    artistL->setFont(f);
    
    layout->addWidget(artistL);
    
    layout->addWidget(stack);
    setLayout(layout);

    searchTagL<<Basic::ARTIST<<Basic::ALBUM<<Basic::TITLE<<Basic::LEAD_ARTIST;   
    
    connect(artistV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( artistActivated(const QModelIndex&) ) );
    
    connect(albumH,SIGNAL(updateNeeded() ),this,SLOT(albumUpdate() ) );
    connect(artistH,SIGNAL(updateNeeded() ),this,SLOT(artistUpdate()) );
    
    connect(view,SIGNAL(showContextMenu(QModelIndex,QModelIndexList)),this,SLOT(showContexMenuSlot(QModelIndex,QModelIndexList))); 
}

library::~library()
{
    delete searchQ;
}

void library::activated(const int n)
{    
    if (n==0)
    {
        goToArtist();
    }    
    else if(onArtist() )
    {
        artistH->updateIfDirty();
    }
    else if(onAlbum() )
    {
        albumH->updateIfDirty();
    }  
}

QString library::name() const
{
    return QString(tr("Library") );
}

void library::artistActivated(const QModelIndex &index )
{

    if(!index.isValid() )
    {
        return ;
    }
    artistName=index.data(Qt::DisplayRole).toString();
    artistL->setText(artistName);
    standardItem *i=artistM->itemFromIndex(index);
    database::abstractQuery *q=static_cast<const views::tagItem*>(i)->filter();
    
    albumH->setCustomFilter(q);
    stack->setCurrentWidget(view);
    albumH->update();
}



void library::toolBarInit()
{
    toolBar=new KToolBar(this);
    QWidget *spacer=new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    searchLine =new views::delayLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage("Search");
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );

    backAction = new QAction( views::decor->icon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );

    connect( backAction, SIGNAL( triggered( bool) ), this, SLOT( goToArtist() ) );


    forwardAction = new QAction( views::decor->icon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
    connect( forwardAction, SIGNAL( triggered( bool) ), this, SLOT( goToAlbum() ) );
    
    toolBar->addWidget(spacer);
    toolBar->addWidget(searchLine);
    connect(searchLine,SIGNAL(textChangedDelay ( const QString & ) ),this,SLOT(search(const QString &) ) );
}

void library::search(const QString & text)
{        
    database::abstractQuery *q=searchQuery();
    artistH->setCustomFilter(q);
    if(q!=0)
        delete q;
    
    if(onArtist())
    {
        artistH->update();
    }
    else
    {
        QModelIndex m=artistV->currentIndex();
        artistActivated(m);
    }
}

void library::goToArtist()
{    
    stack->setCurrentWidget(artistV);
    artistL->setText(tr("Artist") );
    artistH->updateIfDirty();
}

void library::goToAlbum()
{    
    stack->setCurrentWidget(view);    
    artistL->setText(artistName);
    albumH->updateIfDirty();
}

bool library::onAlbum()
{
    return stack->currentWidget()==view;
}

bool library::onArtist()
{
    return stack->currentWidget()==artistV;
}

void library::albumUpdate()
{
    if(view->isVisible())
    {
        albumH->update();
    }
}

void library::artistUpdate()
{
    if(artistV->isVisible())
    {
        artistH->update();
    }
}

database::abstractQuery* library::searchQuery()
{
    QString text=searchLine->text();
    if(text.isEmpty())
        return 0;
    
    database::matchQuery *searchQ=new database::matchQuery (database::OR);
    
    foreach(int i,searchTagL)
    {
        database::tagQuery *t=new database::tagQuery(i,database::CONTAINS,text);
        searchQ->append(t);
    }
    return searchQ;
}

void library::showContexMenuSlot(QModelIndex index, QModelIndexList list)
{
    if(!index.isValid() )
    {
         return ;
    }
    
//     qDebug()<<"LI "<<list.size();
    _editIndex=index;
    QUrl u=index.data(URL_ROLE).toUrl();    
    QMenu *menu=new QMenu(this);
    
    QAction *act=new QAction(KIcon("document-edit"),tr("edit"),menu );
    connect(act,SIGNAL(triggered(bool)),this,SLOT(editIndex())) ;
    menu->addAction(act);
    
    QList<QUrl>urls=view->getUrls(list);
    core::contentHdl->contextMenu(menu,KUrl(u),urls );
    if(!menu->isEmpty() )
    {
        menu->exec( QCursor::pos() );
    }
    menu->deleteLater();
}

void library::editIndex()
{
    view->edit(_editIndex);
    _editIndex=QModelIndex();
}
