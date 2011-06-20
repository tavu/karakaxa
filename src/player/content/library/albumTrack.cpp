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
        _needUpdate(false)
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
    
    connect(db,SIGNAL(updated(audioFiles::audioFile ) ),this,SLOT(albumsNeedUpdate(audioFiles::audioFile ) ) );
    
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(writeSettings()) );
//     connect(db,SIGNAL(changed()),this,SLOT(setNeedUpdateTrue() ) );
      
}

void albumTrack::trackVInit()
{
    trackV=new views::treeView(this,"TRACKVIEW");
    trackM=new standardModel(this);
    
    trmItem=new views::trackModelItem();
//     trackM->appendRow(trmItem);

    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);

//     trackV->setModel(trackM);
    trackV->setNotHide(TITLE);
    
    queryGen=new queryGrt(this);    
    quer=new queryGrt::tagQuery();
    andQ=new queryGrt::matchQuery(queryGrt::AND);
    andQ->append(quer);
    queryGen->setQuery(andQ);
    
    trmItem->setQueryG(queryGen);

    trackV->setModel(trackM);
    trackM->setHeadItem(trmItem);

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
//     pix=views::decor.artist().toPixmap();    

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

//     albumV->setPalette(player::pal);

    albumV->setFrameStyle(QFrame::NoFrame);
    albumV->setViewMode(QListView::IconMode);
    albumV->setUniformItemSizes (true);
    albumV->setResizeMode(QListView::Adjust);
    albumV->setFlow(QListView::LeftToRight);

    albumV->setWrapping(false);
    albumV->setWordWrap(true);
    albumV->setMinimumHeight(80);
    albumV->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

//     QSizePolicy p;
//     p.setHorizontalPolicy(QSizePolicy::Ignored);

    albumW=new QWidget(this);
    albumW->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
   
    albumV->setStyleSheet("QAbstractItemView {background-color: transparent; }");

    QHBoxLayout *hLayout = new QHBoxLayout(albumW);

    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    hLayout->addWidget(albumV);
    
//     albumM->update();

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
/*
    QString s;
    if (search.isEmpty() )
    {
        s=queryGrt::tracks(albumId);
    }
    else
    {
        s=queryGrt::tracks(albumId,search);	
    }
    trackM->setFilter(s);
*/
   queryGrt::tagQuery *quer=new queryGrt::tagQuery();
   
   quer->init(ALBUM_ID,queryGrt::EQUAL,QVariant(albumId) );
   andQ->clear();
   andQ->append(quer);
   if(searchQ!=0 && searchQ->isValid() )
   {
      andQ->append(searchQ->clone());
   }
   queryGen->select();
//    trackM->refresh ();
   
   qDebug()<<queryGen->queryString();

}

void albumTrack::updateQueries()
{      
    albumM->update();
    QModelIndex in=albumM->index(0,0);
    albumActivated(in);
	
    _needUpdate=true;	

}

void albumTrack::albumsNeedUpdate(audioFile f)
{    
    foreach(audioFiles::changes c ,f.tagChanged() )
    {
	if(c.tag==ALBUM ||c.tag==ARTIST || c.tag==LEAD_ARTIST )
	{
	    if(isVisible() )
	    {
		updateQueries();
	    }
	    else
	    {
		_needUpdate=true;
	    }
	    break;
	}
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
//     l<<100<<200;
    l<<group.readEntry("albumSize",100 );
    l<<group.readEntry("trackVSize",200 );
    splitter->setSizes(l);
}
