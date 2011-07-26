#include"albumTrack.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QDebug>
#include"albumWidget.h"
#include"songView.h"
#include"albumDelegate.h"
#include<core.h>
#include<views.h>
#include<KConfigGroup>
using namespace core;

albumTrack::albumTrack(QWidget *parent)
        :QWidget(parent),
        searchQ(0),
        _albumNeedUpdate(false),
	   _trackNeedUpdate(false)
{
    labelInit();
    albumVInit();
    trackVInit();    
    
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addWidget(pLabel);
    hLayout->addWidget(sLabel);
    hLayout->addStretch();

    splitter= new QSplitter (Qt::Vertical,this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    splitter->addWidget(albumW);
        
    splitter->addWidget(trackV);
    
    splitter->setMidLineWidth(5);

    readSettings();

    vLayout->addLayout(hLayout);
    vLayout->addWidget(splitter);
    setLayout(vLayout);
    
    connect(albumV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( albumActivated(const QModelIndex&) ) );    
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(writeSettings()) );
}

void albumTrack::trackVInit()
{
    trackV=new views::treeView(this,"TRACKVIEW");
    trackM=new standardModel(this);
    proxyM=new QSortFilterProxyModel(this);        
    
    trmItem=new views::trackModelItem();
    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);

    trackV->setNotHide(TITLE);
    
    queryGen=new queryGrt(this);    
    quer=new queryGrt::tagQuery();
    andQ=new queryGrt::matchQuery(queryGrt::AND);
    andQ->append(quer);
    queryGen->setQuery(andQ);
    
    trmItem->setQueryG(queryGen);

    trackM->setHeadItem(trmItem);
    proxyM->setSourceModel(trackM);
    trackV->setModel(proxyM);
    
    trackV->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    

    connect(trackV,SIGNAL(showContextMenu(QModelIndex,QModelIndexList)),this,SLOT(showContexMenuSlot(QModelIndex,QModelIndexList))); 
//     trackV->setStyleSheet("QAbstractItemView {background-color: transparent; }");
    
}

void albumTrack::labelInit()
{
    sLabel =new QLabel(this);    
    QFont font;
    font.setPointSize(13);
    font.setBold(true);
    sLabel->setFont(font);

    pLabel=new QLabel(this);

    QPixmap pix=views::decor->tagIcon(ARTIST).pixmap(18,18);

    pLabel->setPixmap(pix);
}

void albumTrack::albumVInit()
{
    albumV=new albumWidget(this);
    albumM=new albumModel(this);

    albumDelegate *del=new albumDelegate(this);
    albumV->setItemDelegate(del);
    
    albumV->setModel(albumM);

    albumV->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    albumV->setFrameStyle(QFrame::NoFrame);
    albumV->setViewMode(QListView::IconMode);
    albumV->setUniformItemSizes (true);
    albumV->setResizeMode(QListView::Adjust);
    albumV->setFlow(QListView::LeftToRight);

    albumV->setWrapping(false);
    albumV->setWordWrap(true);
    albumV->setMinimumHeight(80);
    albumV->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    albumW=new QWidget(this);
    albumW->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
   
    albumV->setStyleSheet("QAbstractItemView {background-color: transparent; }");

    QHBoxLayout *hLayout = new QHBoxLayout(albumW);

    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    hLayout->addWidget(albumV);    
}

void albumTrack::goToArtist(QString& s)
{  
    sLabel->setText(views::pretyTag(s,ARTIST).toString() );      
    
    albumM->setArtist(s);
    albumM->update();
    QModelIndex in=albumM->index(0,0);
    albumActivated(in);
}

void albumTrack::albumActivated(const QModelIndex &n)
{    
    int albumId=albumM->albumId(n.row() );

   queryGrt::tagQuery *quer=new queryGrt::tagQuery();
   
   quer->init(ALBUM_ID,queryGrt::EQUAL,QVariant(albumId) );
   andQ->clear();
   andQ->append(quer);
   if(searchQ!=0 && searchQ->isValid() )
   {
      andQ->append(searchQ->clone());
   }
   queryGen->select();
}

void albumTrack::updateQueries()
{      
    if(_albumNeedUpdate)
    {
	   int currentAlbumId=albumM->albumId(albumV->currentIndex().row() );
	   albumM->update();
	   
	   QModelIndex in;
	   int i;
	   for(i=0;i<albumM->rowCount();i++)
	   {
		  if(albumM->albumId(i)==currentAlbumId )
		  {
			 in=albumM->index(i,0);
			 break ;
		  }
	   }
	   if(i==albumM->rowCount() )
	   {
		  in=albumM->index(0,0);
	   }
	   
	   albumActivated(in);
	   _albumNeedUpdate=false;
    }
    else if(_trackNeedUpdate)
    {
	   queryGen->select();
	   _trackNeedUpdate=false;
    }
}


void albumTrack::showContexMenuSlot(QModelIndex index, QModelIndexList list)
{
    QUrl u=index.data(URL_ROLE).toUrl();    
    QMenu *menu=new QMenu(this);
    core::contentHdl->contextMenu(menu,KUrl(u),!list.isEmpty() );
    if(!menu->isEmpty() )
    {
	menu->exec( QCursor::pos() );
    }
    menu->deleteLater();
}

void albumTrack::writeSettings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "albumTrack" );
    group.writeEntry("albumSize", QVariant(splitter->sizes().at(0)  ) );
    group.writeEntry("trackVSize", QVariant(splitter->sizes().at(1)  ) );
    group.config()->sync();  
}

void albumTrack::readSettings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "albumTrack" );
    QList<int> l;
    
    l<<group.readEntry("albumSize",50 );
    l<<group.readEntry("trackVSize",200 );
//     l<<50<<200;
    splitter->setSizes(l);
}
