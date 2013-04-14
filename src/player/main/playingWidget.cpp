#include"playingWidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include<engine/engine.h>
#include<decoration/decoration.h>
#include<nowPlayList/nplaylist.h>
#include"playingCover.h"
#include<actionMenu.h>
#include<QToolButton>

playingWidget::playingWidget(QWidget* parent) :QWidget(parent)
{
    using namespace views;
    using namespace core;
    
    cover=new coverWidget(this);
    cover->setHeight(65);
    
    slider=new views::sliderWidget(true,this);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    rating=new views::ratingWidget(this);
    rating->setFixedHeight(17);
    rating->setFixedWidth(125);
    rating->hide();
    
    titleL=new scrolText(this);
    titleL->setBold(true);
    titleL->setTextSize(12);
    
    infoL=new scrolText(this);
    infoL->setTextSize(12);
    
    volumeB=new views::volumeBar(this);    
    volumeB->setFixedWidth(150);
            
    QToolButton *play=new QToolButton(this);
    play->setDefaultAction(views::menus()->playPause() );
    play->setToolButtonStyle(Qt::ToolButtonIconOnly);
    play->setIconSize(QSize(25,25) );
    play->setAutoRaise(true);
   
    QToolButton *next=new QToolButton(this);
    next->setDefaultAction(views::menus()->next());
    next->setAutoRaise(true);
    next->setToolButtonStyle(Qt::ToolButtonIconOnly);
    next->setIconSize(QSize(25,25));
    
    QToolButton *prev=new QToolButton(this);
    prev->setDefaultAction(views::menus()->previous());
    prev->setToolButtonStyle(Qt::ToolButtonIconOnly);
    prev->setAutoRaise(true);
    prev->setIconSize(QSize(25,25));
    
    QGridLayout *mainLayout=new QGridLayout(this);    
    QHBoxLayout *hl=new QHBoxLayout();        

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    hl->setContentsMargins(0,0,0,0);
    hl->addWidget(titleL);
    hl->addWidget(rating);
    hl->addWidget(infoL);
    hl->addWidget(spacer);
    hl->addWidget(volumeB);
    
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(cover,0,0,2,1);
    mainLayout->addWidget(prev,0,1,Qt::AlignHCenter);
    mainLayout->addWidget(slider,0,2);
    mainLayout->addWidget(next,0,3);
    mainLayout->addWidget(play,1,1,Qt::AlignHCenter);
    mainLayout->addLayout(hl,1,2,1,3);    
    
    connect(engine(),SIGNAL(trackChanged(QString) ),this,SLOT(updateInfo()) );
    connect(rating,SIGNAL(ratingChanged(int) ),SLOT(setRating(int) ) );
}

void playingWidget::updateInfo()
{

    if(!track.isNull() )
    {
        disconnect(track.data(), 0, this, 0);
    }
    track=core::npList()->getPlayingTrack();
    connect(track.data(),SIGNAL(changed()),this,SLOT(getInfo()) );
    getInfo();
}

void playingWidget::getInfo()
{   
    if (track.isNull())
    {
        titleL->setText(" ");
        infoL->setText(" ");
        rating->hide();
        return;
    }
    
    QString title =track->tag(TITLE).toString()+"   - ";
    titleL->setText(title);
    
    QString info=track->tag(ALBUM).toString() +" - "+track->tag(ARTIST).toString();
    if(info.isEmpty() )
    {
        infoL->setText(" ");
    }
    else
    {
        infoL->setText(info);
    }
    
    cover->setCover(track->cover() );    
    QVariant ratingValue=track->tag(RATING);
    if(ratingValue.isNull())
    {
        rating->hide();
    }
    else
    {
        rating->setRating(track->tag(RATING).toInt());
        rating->show();
    }
}

void playingWidget::setRating(int n)
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
        rating->setRating(n);
    }    
}

