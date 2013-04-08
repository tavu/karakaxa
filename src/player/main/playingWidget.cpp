#include"playingWidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include<engine/engine.h>
#include<decoration/decoration.h>
#include<nowPlayList/nplaylist.h>
#include"playingCover.h"

playingWidget::playingWidget(QWidget* parent) :QWidget(parent)
{
    using namespace views;
    using namespace core;
    
    cover=new playingCover(this);
    slider=new views::sliderWidget(this);
    rating=new views::ratingWidget(this);
    titleL=new scrolText(this);
    titleL->setBold(true);
    infoL=new scrolText(this);
    toolBar=new QToolBar(this);
    volumeB=new views::volumeBar(this);    
        
    volumeB->setMaximumWidth(150);  
    
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cover->setHeight(60);
    
    QAction *previousAction = new QAction(  views::decor->previous() ,"play previous", this );
    toolBar ->addAction( previousAction );
    connect(previousAction,SIGNAL(triggered( bool)),engine(),SLOT(previous() ) );

    toolBar->addWidget(slider);
   
    QAction *nextAction = new QAction(  views::decor->next(),"play next", this );
    toolBar->addAction( nextAction );
    connect(nextAction,SIGNAL(triggered( bool)),engine(),SLOT(next() ) );
    
    rating->setFixedHeight(15);
//     rating->setFixedWidth(50);
    
    QGridLayout *mainLayout=new QGridLayout(this);
    QGridLayout *gridL=new QGridLayout();        

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    gridL->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    gridL->setContentsMargins(10,0,0,0);
    gridL->setSpacing(0);
    
    gridL->addWidget(titleL,0,0,Qt::AlignHCenter|Qt::AlignLeft);    
    gridL->addWidget(infoL,0,1,Qt::AlignHCenter|Qt::AlignLeft);
    gridL->addWidget(rating,0,2,Qt::AlignHCenter|Qt::AlignLeft);
    gridL->addWidget(spacer,0,3);
    gridL->addWidget(volumeB,0,4,Qt::AlignHCenter|Qt::AlignRight);    

    mainLayout->setContentsMargins(0,2,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(cover,0,0,2,1);
    mainLayout->addWidget(toolBar,0,1);
    mainLayout->addLayout(gridL,1,1);
    
    

   
    
//     toolBar->addWidget(slider);
    
                
  
        
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
//         core::status->addErrorP("playingInfo: can't get informarion file is null");
        return;
    }
    QString title =track->tag(TITLE).toString()+" - ";
    titleL->setText(title);
    QString info=track->tag(ALBUM).toString() +" - "+track->tag(ARTIST).toString();
    infoL->setText(info);
    
    cover->setCover(track->cover() );    
    rating->setRating(track->tag(RATING).toInt());
    
    
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

