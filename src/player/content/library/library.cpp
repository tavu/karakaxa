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
//     quer=new queryGrt();
  
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

//     connect(db,SIGNAL(changed() ),this,SLOT(dbChanged() ) );

    

}

library::~library()
{
    delete searchQ;
}
/*
void library::updateQueriesSlot()
{   
    qDebug()<<"update queries";
    if(artistV->isVisible() )
    {
      qDebug()<<"artistV";
	artistV->updateQueries();
	needUpdate =0b10;
    }
    else if(albumTrV->isVisible() )
    {
      qDebug()<<"trackV";
	albumTrV->updateQueries();
	needUpdate =0b01;
    }
    else
    {
      needUpdate =0b11;
    }
}
*/
void library::updateQueries(int n)
{
//     qDebug()<<"library update";
//     if(n==database::DBCHANGED)
//     {
// 	artistV->update();
// 	albumTrV->update();
// 	albumTrV->updateTrack();
//     }
//     else
//     {
// 	tagsEnum t=(tagsEnum)n;
// 	if(t==ARTIST||t==LEAD_ARTIST||t==ALBUM)
// 	{	
// 	    artistV->update();
// 	    albumTrV->update();	
// 	}   
//     }
//     albumTrV->updateTrack();    
//     needUpdate=-1;
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
//     qDebug()<<"F "<<albumTrV->isVisible();
    
}

QString library::name() const
{
    return QString(tr("Library") );
}

void library::buttonInit()
{
    QSize buttonSize(34, 28);
    refresh=new QPushButton(this);
    playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
    refresh->setIcon(playIcon);

    refresh->setFlat(true);
    QHBoxLayout *hlayout = new QHBoxLayout();
    refresh->setMinimumSize(buttonSize);
    hlayout->addWidget(refresh);
    buttonWidget->setLayout(hlayout);

    buttonWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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

//     QSpacerItem s;
//     toolBar->addWidget(&s);
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
// 	    searchTagsL<<queryGrt::query(*i,queryGrt::CONTAINS,s);
	}
    }
    albumTrV->setNeedUpdate(true);
    artistM->setNeedUpdate(true);
    
    if(stack->currentWidget()==artistV )
    {
	artistM->updateQueries();
    }
    else      
    {
	albumTrV->updateQueries();
    }
//     artistV->setSearch(search);
  /*
    QString s=searchLine->text();
    QString search;
    if(!s.isEmpty() )
    {
    	QLinkedList<tagsEnum>::iterator i=searchTagL.begin();
	QStringList searchTagsL;
	    
	for(i=searchTagL.begin();i!=searchTagL.end();i++)
	{
	  searchTagsL<<queryGrt::query(*i,queryGrt::CONTAINS,s);
	}	
// 	search=queryGrt::connectOr(searchTagsL);
	qDebug()<<search;
    }
    albumTrV->setSearch(search);
    artistV->setSearch(search);
    */
}

void library::toAlbum(const QString &s1,const QString &s2)
{
//     albumTrV->setArtist(s1,s2);
//     stack->setCurrentWidget(albumTrV);
}

void library::goToArtist()
{
    stack->setCurrentWidget(artistV);
    if(artistM->needUpdate() )
    {
	artistM->updateQueries();
    }
}

void library::goToAlbum()
{
    stack->setCurrentWidget(albumTrV);
    if(albumTrV->needUpdate() )
    {
	albumTrV->updateQueries();
    }
}

void library::artistActivated(const QModelIndex &index )
{
    QString s=index.data(Qt::UserRole).toString();
    albumTrV->goToArtist(s);
    goToAlbum();
}


void library::artistNeedUpdate(audioFile f)
{
    foreach(audioFiles::changes c,f.tagChanged() )
    {
	if(c.tag==ARTIST || c.tag==LEAD_ARTIST )
	{
	    if(artistV->isVisible() )
	    {
		artistM->updateQueries();
	    }
	    else
	    {
		artistM->setNeedUpdate(true);
	    }
	    break;
	}
    }
}

void library::dbChanged()
{
    artistM->setNeedUpdate(true);
    albumTrV->setNeedUpdate(true);
    
	
    if(artistV->isVisible() )	
    {
      artistM->updateQueries();
    }	
    else if(albumTrV->isVisible() )	
    {
	    
      albumTrV->updateQueries();
    }
}
