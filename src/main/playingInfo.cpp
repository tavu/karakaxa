#include"playingInfo.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<KToolBar>
#include<KIcon>
#define ICONZISE QSize(35,35)
playingInfo::playingInfo(QWidget *parent)
        :QWidget(parent)
{

//      file=0;
//      setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    cover=new player::coverWidget(this);
    cover->setSize(90,110);

//      l=new QLabel(this);



    QHBoxLayout *hLayout=new QHBoxLayout();
    QVBoxLayout *vLayout=new QVBoxLayout();


    titleT=new scrolText(this);
    titleT->setBold(true);
    albumT= new scrolText(this);
    artistT= new scrolText(this);
    commentT= new scrolText(this);
//      titleL=new QLabel(this);
//      titleL->setWordWrap(true);
//      albumL=new QLabel(this);
//      artistL=new QLabel(this);
//      commentL=new QLabel(this);

    vLayout->addWidget(titleT);
    vLayout->addWidget(albumT);
    vLayout->addWidget(artistT);
    vLayout->addWidget(commentT);
//      vLayout->addWidget(toolBar);

    hLayout->addWidget(cover);
    hLayout->addLayout(vLayout);

    setLayout(hLayout);
//      setFixedHeight(50);
    setMinimumWidth(200);
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
//      l->setPixmap(file->cover() );

}
