#include"albumTrack.h"
#include<player.h>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSplitter>
#include<QDebug>
#include"../treeViewHeader.h"
#include"albumWidget.h"
#include"songView.h"

albumTrack::albumTrack(QWidget *parent)
        :QWidget(parent)
{
    labelInit();
    albumVInit();
    trackVInit();



    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addWidget(pLabel);
    hLayout->addWidget(sLabel);
    hLayout->addStretch();

    QSplitter *splitter= new QSplitter (Qt::Vertical,this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    splitter->addWidget(albumW);
    splitter->addWidget(trackV);
//      splitter->setStretchFactor(0,1);
//      splitter->setStretchFactor(1,0);
    QList<int> l;
    l<<100<<200;
    splitter->setSizes(l);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(splitter);
    setLayout(vLayout);


    
    connect(albumV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( albumActivated(const QModelIndex&) ) );
    
}

void albumTrack::trackVInit()
{
    trackV=new songView(this);
    trackM=new songModel(this);

    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);

    trackV->setModel(trackM);
    trackV->setNotHide(TITLE);
}

void albumTrack::labelInit()
{
    sLabel =new QLabel(this);
    QFont font;
    font.setPointSize(13);
    sLabel->setFont(font);

    pLabel=new QLabel(this);

    QPixmap pix;
    pix.load("/home/tavu/src/player/data/artist.png");
    pix=pix.scaled(18,18, Qt::KeepAspectRatio,Qt::SmoothTransformation);


    pLabel->setPixmap(pix);
}

void albumTrack::albumVInit()
{
    albumV=new albumWidget(this);
    albumM=new albumModel(this);

    albumV->setModel(albumM);

    albumV->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    albumV->setPalette(player::pal);

    albumV->setFrameStyle(QFrame::NoFrame);
//      albumV->setFrameStyle(QFrame::Box|QFrame::Plain);
//      albumV->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
    albumV->setViewMode(QListView::IconMode);
    albumV->setUniformItemSizes (true);
//      albumV->setIconSize(QSize(100,100));
    albumV->setResizeMode(QListView::Adjust);
    albumV->setFlow(QListView::LeftToRight);

    albumV->setWrapping(false);
    albumV->setWordWrap(true);
//      albumV->setTextElideMode(Qt::ElideNone);
    albumV->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    QSizePolicy p;
    p.setHorizontalPolicy(QSizePolicy::Ignored);
//      albumV->setSizePolicy(p);

    leftB=new QPushButton(this);
    leftB->setFixedWidth(20);
    leftB->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    leftB->setFlat(true);
    leftB->setIcon(KIcon("go-previous-view") );
    leftB->setAutoRepeat (true);

    rightB=new QPushButton(this);
    rightB->setFixedWidth(20);
    rightB->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    rightB->setFlat(true);
    rightB->setIcon(KIcon("go-next-view") );
    rightB->setAutoRepeat (true);

//       QPalette pal=player::pal;
//       pal.setColor(QPalette::Button,pal.color(QPalette::Window) );
//       leftB->setPalette(pal);

    albumW=new QWidget(this);
    albumW->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);



    QHBoxLayout *hLayout = new QHBoxLayout(albumW);

//      QGridLayout *hLayout = new QGridLayout;

    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    hLayout->addWidget(leftB);
    hLayout->addWidget(albumV);
    hLayout->addWidget(rightB);

    connect(rightB,SIGNAL(pressed() ),albumV,SLOT(scrollR() ) );
    connect(leftB,SIGNAL(pressed() ),albumV,SLOT(scrollL() ) );
}

void albumTrack::setArtist(const QString &artist,const QString &labelS)
{
    sLabel->setText(labelS);
    this->artist=artist;
    update();
}

void albumTrack::updateTrack()
{
    trackM->refresh();    
}

bool albumTrack::update()
{
    QString query;
    if (search.isNull())
    {
        query= queryGrt::albums(artist);
    }
    else
    {
        query=queryGrt::albums(artist,search);
    }

    albumM->setQuery( query,db.getDatabase() );

    if(albumM->rowCount()==0)
    {
      qDebug()<<"EEEEEEEEEEEE";
	return false;
    }
    else
    {
	albumActivated(albumM->index(0,0) );
    }
    return true;
}

void albumTrack::setSearch(const QString &s)
{
    search=s;        
    update();
}

void albumTrack::albumActivated(const QModelIndex &n)
{
    int albumId=albumM->albumId(n.row() );

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
//      trackM->setQuery(queryGrt::finish(s) );
}

