#include"library.h"
#include<QLabel>
#include<QHBoxLayout>
#include <QSpacerItem>
#include"artistDelegate.h"
#include<views.h>

using namespace core;

library::library(QWidget *parent)
        :abstractContent(parent)
{
    addSubmenu(QString(tr("Artist")),views::decor->tagIcon(ARTIST) );
    stack=new QStackedWidget(this);

    artistV=new QListView(this);
    artistM=new artistModel(this);    
    artistV->setModel(artistM);
    artistM->updateQueries();
    artistV->setItemDelegate(new artistDelegate() );
    
    albumTrV=new albumTrack(this);    

    stack->addWidget(artistV);
    stack->addWidget(albumTrV);

    searchQ=new queryGrt::matchQuery(queryGrt::OR);
    artistM->setSearch(searchQ);
    albumTrV->setSearch(searchQ);
    
    toolBarInit();
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(toolBar);
    layout->addWidget(stack);

    setLayout(layout);

    searchTagL<<ARTIST<<ALBUM<<TITLE<<LEAD_ARTIST;           
    
    connect(artistV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( artistActivated(const QModelIndex&) ) );

    connect(db,SIGNAL(changed() ),this,SLOT(dbChanged() ) );
    
    connect(db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(checkNeedUpdates(audioFiles::audioFile)) );       
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
    else if(stack->currentWidget()== artistV )    
    {	
	 artistM->updateQueries();	
    }	
    else if(stack->currentWidget()== albumTrV )
    {		
	 albumTrV->updateQueries();	
    }    
}

QString library::name() const
{
    return QString(tr("Library") );
}

void library::toolBarInit()
{
    toolBar=new KToolBar(this);
    searchLine =new KLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage("Search");
    searchLine->setPalette(palette() );
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );

    backAction = new QAction( KIcon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );

    connect( backAction, SIGNAL( triggered( bool) ), this, SLOT( goToArtist() ) );


    forwardAction = new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );

    connect( forwardAction, SIGNAL( triggered( bool) ), this, SLOT( goToAlbum() ) );

    toolBar->addWidget(searchLine);

//     connect(searchLine,SIGNAL(editingFinished () ),this,SLOT(search() ) );
//     connect(searchLine,SIGNAL(clearButtonClicked() ),this,SLOT(search() ) );textChanged ( const QString & text ) 
    connect(searchLine,SIGNAL(textChanged ( const QString & ) ),this,SLOT(search(const QString &) ) );
}

void library::search(const QString & text)
{    
    searchQ->clear();   
    if(!text.isEmpty() )
    {
	   QLinkedList<tagsEnum>::iterator i=searchTagL.begin();
		    
	   for(i=searchTagL.begin();i!=searchTagL.end();i++)
	   {
		  queryGrt::tagQuery *t=new queryGrt::tagQuery(*i,queryGrt::CONTAINS,text);
		  searchQ->append(t);
	   }
    }
    albumTrV->setAlbumNeedUpdate(true);
    albumTrV->setTrackNeedUpdate(true);
    artistM->setNeedUpdate(true);
    
    if(stack->currentWidget()==artistV )
    {
	 artistM->updateQueries();
    }
    else      
    {
	 albumTrV->updateQueries();
    }
}

void library::goToArtist()
{
    stack->setCurrentWidget(artistV);
    artistM->updateQueries();
}

void library::goToAlbum()
{
    stack->setCurrentWidget(albumTrV);
    albumTrV->updateQueries();    
}

void library::artistActivated(const QModelIndex &index )
{
    QString s=index.data(Qt::UserRole).toString();
    albumTrV->goToArtist(s);
    goToAlbum();
}

void library::dbChanged()
{
    artistM->setNeedUpdate(true);
    albumTrV->setAlbumNeedUpdate(true);
    albumTrV->setTrackNeedUpdate(true);
    
    	
    if(artistV->isVisible() )	
    {
      artistM->updateQueries();
    }	
    else if(albumTrV->isVisible() )	
    {    
      albumTrV->updateQueries();
    }
}

void library::checkNeedUpdates(audioFile f)
{     
    foreach(audioFiles::changes c ,f.tagChanged() )
    {
	   if(c.tag==ALBUM ||c.tag==ARTIST || c.tag==LEAD_ARTIST )
	   {
		  albumTrV->setAlbumNeedUpdate(true);
		  artistM->setNeedUpdate(true);
		  break ;
	   }
	   else if(searchQ->isValid() && searchTagL.contains((tagsEnum)c.tag) )
	   {
		    albumTrV->setAlbumNeedUpdate(true);
		    artistM->setNeedUpdate(true);
		    break ;
	   }
    }
    
    albumTrV->setTrackNeedUpdate(true);      
    
    if(artistV->isVisible() )	
    {
	   artistM->updateQueries();
    }	
    else if(albumTrV->isVisible() )	
    {    
	   albumTrV->updateQueries();
    }
}

