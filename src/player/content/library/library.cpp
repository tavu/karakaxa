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
#include"albumDelegate.h"
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
    artistV->setItemDelegate(new artistDelegate(artistV) );    
    artistM=new standardModel(this);
    artistH=new views::tagItemHead(this);
    artistH->addTag(Basic::ALBUM_ARTIST);    
    artistH->fetchMore();
    artistM->setHeadItem(artistH);
    artistV->setModel(artistM);
    stack->addWidget(artistV);    
    
    view=new views::treeView(this);
    view->setHeaderHidden(true);
    view->setItemDelegate(new albumDelegate(this) );

//     view->setFrameShadow(QFrame::Plain);
//     view->setStyleSheet("QAbstractItemView {background-color: transparent; }");
    
    view->setUniformRowHeights(false);
    albumTrackM=new standardModel(this);
    albumTrackM->setProperty(SPAN_PROP,true);
    view->setModel(albumTrackM);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
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
//     artistL->setPixmap(views::decor->tagIcon(Basic::ARTIST).pixmap(QIcon::Normal) );
    
    layout->addWidget(artistL);
    
    layout->addWidget(stack);
    setLayout(layout);

    searchTagL<<Basic::ARTIST<<Basic::ALBUM<<Basic::TITLE<<Basic::LEAD_ARTIST;   
    
    connect(artistV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( artistActivated(const QModelIndex&) ) );
    
    connect(albumH,SIGNAL(updateNeeded() ),this,SLOT(albumUpdate() ) );
    connect(artistH,SIGNAL(updateNeeded() ),this,SLOT(artistUpdate()) );
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
    database::abstractQuery *q=static_cast<const views::tagItem*>(i)->selector()->filter();
    
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
    if(text.isEmpty() )
    {
        artistH->setCustomFilter(0);
    }
    else
    {
        database::matchQuery searchQ(database::OR);
        foreach(int i,searchTagL)
        {
            database::tagQuery *t=new database::tagQuery(i,database::CONTAINS,text);
            searchQ.append(t);
        }
        artistH->setCustomFilter(&searchQ);
    }
    
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
    artistL->setText(tr("Artist") );
    stack->setCurrentWidget(artistV);
    artistH->updateIfDirty();
}

void library::goToAlbum()
{
    artistL->setText(artistName);
    stack->setCurrentWidget(view);    
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
