#include"library.h"
#include<QLabel>
#include<QHBoxLayout>
#include <QSpacerItem>
// #include<libraryWidget.h>



library::library(QWidget *parent)
        :abstractContent(parent),
        needUpdate(-1)
{

    addChild(QString(tr("Artist")));
    stack=new QStackedWidget(this);


    artistV=new artistWidget(this);

    albumTrV=new albumTrack(this);


    stack->addWidget(artistV);
    stack->addWidget(albumTrV);

    toolBarInit();
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(toolBar);
    layout->addWidget(stack);

    setLayout(layout);

    scan=new QAction(tr("Scan"),this);
    config=new QAction(tr("Configure"),this);
    menu.addAction(scan);
    menu.addAction(config);

    searchTagL<<ARTIST<<ALBUM<<TITLE<<LEAD_ARTIST;
    
    
    connect(scan,SIGNAL(triggered()),this,SLOT(libraryScan() ) );

    connect(artistV,SIGNAL(toArtist(QString , QString) ) ,this,SLOT(toAlbum(const QString &,const QString &) ) );
    
    connect(&db,SIGNAL(updated(int)),this,SLOT(updateQueriesSlot(int) ) );
    

}

void library::updateQueriesSlot(int t)
{
    if(!abstractContent::isActive())
    {
	needUpdate=t;
    }
    else
    {
	updateQueries(t);
    }
}

void library::updateQueries(int n)
{
    qDebug()<<"library update";
    if(n==database::DBCHANGED)
    {
	artistV->update();
	albumTrV->update();
	albumTrV->updateTrack();
    }
    else
    {
	tagsEnum t=(tagsEnum)n;
	if(t==ARTIST||t==LEAD_ARTIST||t==ALBUM)
	{	
	    artistV->update();
	    albumTrV->update();	
	}   
    }
    albumTrV->updateTrack();    
    needUpdate=-1;
}



void library::update(const int n)
{
    if (n==0)
    {
        stack->setCurrentWidget(artistV);
    }

    if(needUpdate!=-1)
    {
	updateQueries((tagsEnum)needUpdate);
    }
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

void library::libraryScan()
{
//      libraryWidget *w=new libraryWidget();
//      player::contentHandlr->addWidget(w);
}

void library::toolBarInit()
{
    toolBar=new KToolBar(this);
    searchLine =new KLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage("Search");
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

    connect(searchLine,SIGNAL(editingFinished () ),this,SLOT(search() ) );
    connect(searchLine,SIGNAL(clearButtonClicked() ),this,SLOT(search() ) );
}

void library::search()
{
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
	search=queryGrt::connectOr(searchTagsL);
	qDebug()<<search;
    }
    albumTrV->setSearch(search);
    artistV->setSearch(search);
}

void library::toAlbum(const QString &s1,const QString &s2)
{
    albumTrV->setArtist(s1,s2);
    stack->setCurrentWidget(albumTrV);
}

void library::goToArtist()
{
    stack->setCurrentWidget(artistV);
}

void library::goToAlbum()
{
    stack->setCurrentWidget(albumTrV);
}
