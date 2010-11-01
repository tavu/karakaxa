#include"playingInfo.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<KToolBar>
#include<KIcon>
#define ICONZISE QSize(35,35)
playingInfo::playingInfo(QWidget *parent)
        :QWidget(parent),
        file(0)
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
//      connect(&engine,SIGNAL(trackChanged(QString) ),this,SLOT(update(QString)) );
}

void playingInfo::update(QString path)
{
    if (file==0)
    {
        file=audioFile::getAudioFile(path);
    }
    else
    {
        audioFile::releaseAudioFile(file);
        file=audioFile::getAudioFile(path);
    }
    getInfo();
}

void playingInfo::getInfo()
{
    if (file==0)
    {
        qDebug()<<"playingInfo: can't get informarion file is null";
        return;
    }

    titleT->setText(file->tag(TITLE).toString() );
    albumT->setText(file->tag(ALBUM).toString() );
    artistT->setText(file->tag(LEAD_ARTIST).toString() );
    commentT->setText(file->tag(COMMENT).toString() );

    cover->setCover(file->cover() );
//      l->setPixmap(file->cover() );

}
