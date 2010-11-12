#include"playingInfo.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<KToolBar>
#include<KIcon>
#include <QGridLayout>
#define ICONZISE QSize(35,35)
playingInfo::playingInfo(QWidget *parent)
        :QWidget(parent)
{
    cover=new player::coverWidget(this);
    cover->setSize(90,110);
    stars=new starWidget(this);
    stars->setFixedHeight(20);
    
    QHBoxLayout *hLayout=new QHBoxLayout();
    QVBoxLayout *vLayout=new QVBoxLayout();
    QVBoxLayout *layout=new QVBoxLayout();

    titleT=new scrolText(this);
    titleT->setBold(true);
    albumT= new scrolText(this);
    artistT= new scrolText(this);
    commentT= new scrolText(this);

    hLayout->addWidget(cover);
    vLayout->addWidget(stars);
    vLayout->addWidget(commentT);
    hLayout->addLayout(vLayout);
    
    layout->addLayout(hLayout);
    layout->addWidget(titleT);
    layout->addWidget(albumT);
    layout->addWidget(artistT);
    layout->addStretch();
    
    
//      hLayout->addWidget(cover);
//      hLayout->addLayout(vLayout);
     
     
    setLayout(layout);
//      setFixedHeight(50);    
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
    if (track.isNull())
    {
        qDebug()<<"playingInfo: can't get informarion file is null";
        return;
    }

    titleT->setText(track->tag(TITLE).toString() );
    albumT->setText(track->tag(ALBUM).toString() );
    artistT->setText(track->tag(LEAD_ARTIST).toString() );
    commentT->setText(track->tag(COMMENT).toString() );

    cover->setCover(track->cover() );
    stars->setRating(track->tag(RATING).toInt());
//      l->setPixmap(file->cover() );

}
