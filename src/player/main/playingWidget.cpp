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
#include<QApplication>
#include<QDrag>
#include<QMouseEvent>

playingWidget::playingWidget(QWidget* parent) :QWidget(parent)
{
    using namespace views;
    using namespace core;
    
    cover=new coverWidget(this);
    cover->setHeight(65);
    
    slider=new views::sliderWidget(true,this);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    rating=new views::ratingWidget(this);
    rating->setBlack(true);
    
    rating->setFixedHeight(25);
    rating->setFixedWidth(100);
    rating->hide();
    
    titleL=new scrolText(this);
    titleL->setBold(true);
    titleL->setTextSize(12);
    
    infoL=new scrolText(this);
    infoL->setTextSize(12);
    
    volumeB=new views::volumeBar(this); 
    
    volumeB->setIconSize(QSize(32,32) );
    volumeB->setFixedWidth(150);
            
    QToolButton *play=new QToolButton(this);
    play->setDefaultAction(views::menus()->playPause() );
    play->setToolButtonStyle(Qt::ToolButtonIconOnly);
    play->setIconSize(QSize(35,35) );
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
//     QWidget *smallSpace=new QWidget(this);
    
//     smallSpace->setFixedSize(QSize(1,10));
    
    infoW=new QWidget(this);
    QHBoxLayout *hl=new QHBoxLayout(infoW);
    hl->setContentsMargins(0,0,0,0);

//     hl->addWidget(play);
    hl->addStretch();    
    hl->addWidget(titleL);
    hl->addWidget(infoL);
    hl->addWidget(rating);
    hl->addStretch();
    hl->addWidget(volumeB);
    
    mainLayout->setSpacing(5);
    
    mainLayout->setContentsMargins(10,0,10,5);
//     mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(cover,0,0,2,1);
    mainLayout->addWidget(prev,0,1,Qt::AlignHCenter);
    mainLayout->addWidget(slider,0,2);
//     mainLayout->addWidget(smallSpace,0,3);
    mainLayout->addWidget(next,0,4);
    mainLayout->addWidget(play,1,1,Qt::AlignHCenter);
    mainLayout->addWidget(infoW,1,2,1,4);    
    
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
    
    QString title =track->tag(Basic::TITLE).toString().simplified();
    QString album=track->tag(Basic::ALBUM).toString().simplified();
    QString artist=track->tag(Basic::ARTIST).toString().simplified();
    QString info;
    if(album.isEmpty() )
    {
        if(!artist.isEmpty() )
        {
            info=artist;
        }
    }
    else
    {
        info=album;
        if(!artist.isEmpty() )
        {
            info=info.append(" - ").append(artist);
        }
    }
     
    if(!info.isEmpty() && !title.isEmpty())
    {
        info.prepend(" - ");
    }
    
    titleL->setText(title);
    infoL->setText(info);
    cover->setCover(track->cover() );    
    QVariant ratingValue=track->tag(Basic::RATING);
    if(ratingValue.isNull())
    {
        rating->hide();
    }
    else
    {
        rating->setRating(track->tag(Basic::RATING).toInt());
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
    if(f->setTag(Basic::RATING,n) )
    {
        rating->setRating(n);
    }    
}

void playingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton )
    {
        startPos = event->pos();
    }

    QWidget::mousePressEvent(event);
}


void playingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()  && infoW->underMouse() )
        {
            
//             QWidget::mouseMoveEvent(event);
            performDrag();
        }
        else
        {
            QWidget::mouseMoveEvent(event);
        }
    }
    else
    {
        QWidget::mouseMoveEvent(event);
    }
}

void playingWidget::performDrag()
{
    if(track.isNull() || !track->isValid() )
    {
           return ;
    }
        
    QList<QUrl> l;
    l<<track->path();
    QMimeData *mimeData = new QMimeData;
    mimeData->setUrls(l);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(views::decor->tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction);
}

