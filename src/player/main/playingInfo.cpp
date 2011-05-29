#include"playingInfo.h"
#include<core.h>
#include<decoration/decoration.h>
// #include<views.h>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<KToolBar>
#include<KIcon>
#include <QFormLayout>
#include<QGraphicsView>
#include<QCommonStyle>
#define ICONZISE QSize(15,15)

using namespace core;
using namespace views;

playingInfo::playingInfo(QWidget *parent)
        :QFrame(parent)
{
 
    cover=new views::coverWidget(this);
    cover->setSize(90,110);
//     cover->setFixedSize(100,110);
//     cover->setFrameShape(QFrame::StyledPanel);
//     cover->setFrameShadow(QFrame::Sunken);
        
    stars=new views::ratingWidget(this);
    stars->setMaximumWidth(100);    

    titleT=new scrolText(tr("Empty"),this);
    titleT->setBold(true);
    albumT= new scrolText(tr("Empty"),this);
    artistT= new scrolText(tr("Empty"),this);
    commentT= new scrolText(tr("Empty"),this);
    
    titleIcon=new QLabel(this);
    albumIcon=new QLabel(this);
    commentIcon=new QLabel(this);
    artistIcon=new QLabel(this);
     
    titleIcon->setPixmap(decor->tagIcon(TITLE).pixmap(ICONZISE ));
    albumIcon->setPixmap(decor->tagIcon(ALBUM).pixmap(ICONZISE ));
    commentIcon->setPixmap(decor->tagIcon(COMMENT).pixmap(ICONZISE ));
    artistIcon ->setPixmap(decor->tagIcon(ARTIST).pixmap(ICONZISE ));
    
    QFormLayout *formLayout=new QFormLayout();    
    formLayout->addRow(stars);
    formLayout->addRow(commentIcon,commentT);
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(cover);
    hLayout->addLayout(formLayout);
    hLayout->addStretch();
    
     hLayout->setContentsMargins(0,0,0,0);
     QWidget *w =new QWidget(this);
     w->setLayout(hLayout);
     w->setFixedHeight(100);
//     
//      layout->addLayout(hLayout);
//      layout->addWidget(titleT);
//      layout->addWidget(albumT);
//      layout->addWidget(artistT);
//      layout->addStretch();
    
    QFormLayout *mainLayout=new QFormLayout();

//     l->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
     mainLayout->addRow(w);
    
//     l->addLayout(hLayout,0,0,2,2);
    
    
    
    mainLayout->addRow(titleIcon,titleT);
    mainLayout->addRow(albumIcon,albumT);
    mainLayout->addRow(artistIcon,artistT);

    
    
    
       mainLayout->setContentsMargins(0,0,0,0);
// /       setLayout(layout);
      
//        l->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
//        l->setSizeConstraint(QLayout::SetMaximumSize);d
    
//     QCommonStyle *style=new QCommonStyle ();
//     setStyle(style);
//     setSizePolicy( QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum) );
    setLayout(mainLayout);
      
      
//      setFixedHeight(50);    
    connect(engine,SIGNAL(trackChanged(QString) ),this,SLOT(update(QString)) );
    connect(stars,SIGNAL(ratingChanged(int) ),SLOT(setRating(int) ) );
    
//     setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

QSize playingInfo::sizeHint() const
{
    return QSize(100,185);
}



playingInfo::~playingInfo()
{
    delete stars;
}

void playingInfo::update(QString path)
{
     track=npList->getPlayingTrack();
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
    artistT->setText(track->tag(ARTIST).toString() );
    commentT->setText(track->tag(COMMENT).toString() );

//      cover->setCover(track->cover() );
//     lab->setPixmap(track->cover());
    stars->setRating(track->tag(RATING).toInt());
//      l->setPixmap(file->cover() );

}

void playingInfo::setRating(int n)
{
    if (track.isNull())
    {
	return ;
    }
  
    audioFile *f=new audioFile(track->path() );
    if(f==0)
    {
	return;
    }
    if(f->setTag(RATING,n) )
    {
	stars->setRating(n);
    }
    
}