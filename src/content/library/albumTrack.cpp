#include"albumTrack.h"
#include<player.h>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSplitter>
#include<QDebug>
#include"../treeViewHeader.h"
#include"albumWidget.h"
#include"songView.h"
#include"albumDelegate.h"

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
    
    splitter->setMidLineWidth(5);
    QList<int> l;
    l<<100<<200;
    splitter->setSizes(l);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(splitter);
    setLayout(vLayout);
    
    connect(albumV,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( albumActivated(const QModelIndex&) ) );
    
    
//     connect(trackM,SIGNAL(newQuery()),trackV ,SLOT(updateStarWidget() ) );

//       trackV->setStyleSheet(    qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #616161, stop: 0.5 #505050,stop: 0.6 #434343, stop:1 #656565);		
//       QString m_styleSet;
//       m_styleSet=QString("QHeaderView::section {background-color: %1; padding-left: 4px; border: 1px solid; }");
//       QString lineGrad=QString("qlineargradient(x1:0.5, y2:0.25, x2:0.5, y2:0.45, colorAt: 0.0 #%1,colorAt: 0.5 #%2)");
//       lineGrad=lineGrad.arg("QColor::Blue","palette().highlight().color()");
//       m_styleSet=m_styleSet.arg(lineGrad);
//       trackV->setStyleSheet(m_styleSet);
      
}

void albumTrack::trackVInit()
{
    trackV=new songView(this,"TRACKVIEW");
    trackM=new songModel(this);

    trackV->setRatingColumn(RATING);
    trackV->setEditTriggers(QAbstractItemView::SelectedClicked);

    trackV->setModel(trackM);
    trackV->setNotHide(TITLE);
    
//     trackV->setPalette(player::pal);
//     trackV->setStyleSheet("QAbstractItemView {background-color: transparent; }");
    
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

    albumDelegate *del=new albumDelegate(this);
    albumV->setItemDelegate(del);
    
    albumV->setModel(albumM);

    albumV->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    albumV->setPalette(player::pal);

    albumV->setFrameStyle(QFrame::NoFrame);
    albumV->setViewMode(QListView::IconMode);
    albumV->setUniformItemSizes (true);
    albumV->setResizeMode(QListView::Adjust);
    albumV->setFlow(QListView::LeftToRight);

    albumV->setWrapping(false);
    albumV->setWordWrap(true);
    albumV->setMinimumHeight(80);
    albumV->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    QSizePolicy p;
    p.setHorizontalPolicy(QSizePolicy::Ignored);
/*
    leftB=new QPushButton(this);
    leftB->setFixedWidth(20);
    leftB->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    leftB->setFlat(true);
    leftB->setIcon(KIcon("go-previous-view") );
    leftB->setAutoRepeat (true);

    rightB=new QPushButton(this);
    rightB->setAutoFillBackground(true);
    rightB->setFixedWidth(20);
    rightB->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    rightB->setFlat(true);
    rightB->setIcon(KIcon("go-next-view") );
    rightB->setAutoRepeat (true);
    */
//     rightB->setStyleSheet("QPushButton { background-color: green }");

//       QPalette pal=player::pal;
//       pal.setColor(QPalette::Button,pal.color(QPalette::Window) );
//       leftB->setPalette(pal);

    albumW=new QWidget(this);
    albumW->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
/*
    QPalette pal=albumV->palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    albumV->setPalette(pal);*/

    albumV->setStyleSheet("QAbstractItemView {background-color: transparent; }");

    QHBoxLayout *hLayout = new QHBoxLayout(albumW);

//      QGridLayout *hLayout = new QGridLayout;

    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
//     hLayout->addWidget(leftB);
    hLayout->addWidget(albumV);
//     hLayout->addWidget(rightB);

//     connect(rightB,SIGNAL(pressed() ),albumV,SLOT(scrollR() ) );
//     connect(leftB,SIGNAL(pressed() ),albumV,SLOT(scrollL() ) );
}

void albumTrack::setArtist(const QString &artist,const QString &labelS)
{
    sLabel->setText(labelS);
    this->artist=artist;
    update();
    albumActivated(albumM->index(0,0) );
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
	return false;
    }
    return true;
}

void albumTrack::setSearch(const QString &s)
{
    search=s;        
    update();
    albumActivated(albumM->index(0,0) );
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

void albumTrack::updateQueries()
{

//   qDebug()<<"trackView update";
  
    QSqlQuery q=albumM->query();
//   albumM->setQuery(q);
    QSqlQuery nq(q.executedQuery(),db.getDatabase() );
    nq.exec();
    albumM->setQuery(nq);
    
    trackM->refresh();
}