#include"playingInfo.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<KToolBar>
#include<KIcon>
#define ICONZISE QSize(35,35)
#include<QGridLayout>
playingInfo::playingInfo(QWidget *parent)
        :QWidget(parent)
{
     cover=new player::coverWidget(this);
     cover->setSize(90,110);

//     QHBoxLayout *hLayout=new QHBoxLayout();
// //     QVBoxLayout *vLayout2=new QVBoxLayout();
//     QVBoxLayout *vLayout=new QVBoxLayout();

//     hLayout->addWidget(cover);
    
//     vLayout1->addLayout(hLayout);
    
    titleT=new scrolText("AAAAA",this);
    titleT->setBold(true);
    albumT= new scrolText(this);
    artistT= new scrolText(this);
    commentT= new scrolText(this);

//     vLayout->addWidget(cover);
//     vLayout->addWidget(commentT);
//     vLayout->addWidget(titleT);
//     vLayout->addWidget(albumT);
//     vLayout->addWidget(artistT);
    
//      vLayout->addWidget(toolBar);
    QGridLayout *layout=new QGridLayout(this);
    layout->setContentsMargins(20,20,50,20);
    qDebug()<<albumT->sizeHint();
//     layout->addWidget(commentT,0,0);
      layout->addWidget(cover,0,0,3,1);
      layout->addWidget(titleT,0,1);
//     layout->addWidget(cover,1,0);
     layout->addWidget(albumT,1,0,1,2);
     layout->addWidget(artistT,2,0,1,2);
//     layout->addWidget(artistT,3,0);


    
//     vLayout2->addLayout(hLayout);
//     vLayout2->addLayout(vLayout1);

//     setLayout(layout);
//      setFixedHeight(50);
//     setMinimumWidth(200);
//      update("/media/D/music/BLACK n WHITE - Escucha Lo/02 Escucha Lo.mp3");
     connect(&engine,SIGNAL(trackChanged(QString) ),this,SLOT(update(QString)) );
}

void playingInfo::update(QString path)
{

    track=npList.getPlayingTrack();
    getInfo();
}

void playingInfo::getInfo()
{
    if (track.isNull() )
    {
        qDebug()<<"playingInfo: can't get informarion file is null";
        return;
    }

    titleT->setText(track->tag(TITLE).toString() );
    albumT->setText(track->tag(ALBUM).toString() );
    artistT->setText(track->tag(LEAD_ARTIST).toString() );
    commentT->setText(track->tag(COMMENT).toString() );

//     cover->setCover(track->cover() );
    
//      l->setPixmap(file->cover() );

}
