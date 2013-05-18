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
#define ICONZISE QSize(17,17)

using namespace core;
using namespace views;
using namespace Basic;

playingInfo::playingInfo(QWidget *parent)
        :QFrame(parent)
{
 
    cover=new views::coverWidget(this);
    cover->setSize(100,90);
//     cover->setFrameStyle(QFrame::Panel | QFrame::Raised);
        
    stars=new views::ratingWidget(this);
//     stars->setMaximumWidth(100);    

    titleT=new scrolText(tr("Empty"),this);
    titleT->setBold(true);
    albumT= new scrolText(tr("Empty"),this);
    artistT= new scrolText(tr("Empty"),this);
//     commentT= new scrolText(tr("Empty"),this);
//     genreT=new scrolText(tr("Empty"),this);
    
    titleIcon=new QLabel(this);
    albumIcon=new QLabel(this);
//     commentIcon=new QLabel(this);
//     genreIcon=new QLabel(this);
    artistIcon=new QLabel(this);    
     
    titleIcon->setPixmap(decor->tagIcon(TITLE).pixmap(ICONZISE ));
    albumIcon->setPixmap(decor->tagIcon(ALBUM).pixmap(ICONZISE ));
//     commentIcon->setPixmap(decor->tagIcon(COMMENT).pixmap(ICONZISE ));
//     genreIcon->setPixmap(decor->tagIcon(GENRE).pixmap(ICONZISE ));
    artistIcon ->setPixmap(decor->tagIcon(ARTIST).pixmap(ICONZISE ));
    
    QFormLayout *formLayout=new QFormLayout();    
    formLayout->addRow(stars);
//     formLayout->addRow(commentIcon,commentT);
//     formLayout->addRow(genreIcon,genreT);
     formLayout->addRow(titleIcon,titleT);
	formLayout->addRow(artistIcon,artistT);
	formLayout->addRow(albumIcon,albumT);
    
    formLayout->setContentsMargins(0,0,0,0);
    
    
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(cover);
    hLayout->addLayout(formLayout);
    hLayout->addStretch();
    
    hLayout->setContentsMargins(0,8,0,0);
//      QWidget *w =new QWidget(this);
//      w->setLayout(hLayout);
//      w->setFixedHeight(100);
//     
//      layout->addLayout(hLayout);
//      layout->addWidget(titleT);
//      layout->addWidget(albumT);
//      layout->addWidget(artistT);
//      layout->addStretch();
    
    QFormLayout *mainLayout=new QFormLayout();

//     l->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
     mainLayout->addRow(hLayout);
    
//     l->addLayout(hLayout,0,0,2,2);
    
    
    
//     mainLayout->addRow(titleIcon,titleT);
//     mainLayout->addRow(albumIcon,albumT);
//     mainLayout->addRow(artistIcon,artistT);

    
    
    
//     l->setContentsMargins(2,10,2,0);  
    mainLayout->setContentsMargins(3,0,3,3);
// /       setLayout(layout);
      
//        l->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
//        l->setSizeConstraint(QLayout::SetMaximumSize);d
    
//     QCommonStyle *style=new QCommonStyle ();
//     setStyle(style);
//     setSizePolicy( QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum) );
    setLayout(mainLayout);
      
      
//      setFixedHeight(50);    
    connect(engine(),SIGNAL(trackChanged(QString) ),this,SLOT(update()) );
    connect(stars,SIGNAL(ratingChanged(int) ),SLOT(setRating(int) ) );
    
//     setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

QSize playingInfo::sizeHint() const
{
    return QSize(70,65);
}



playingInfo::~playingInfo()
{
    delete stars;
}

void playingInfo::update()
{
	if(!track.isNull() )
	{
	   disconnect(track.data(), 0, this, 0);
	}
     track=npList()->getPlayingTrack();
     connect(track.data(),SIGNAL(changed()),this,SLOT(getInfo()) );
     getInfo();
}

void playingInfo::getInfo()
{   
    if (track.isNull())
    {
        core::status->addErrorP("playingInfo: can't get informarion file is null");
        return;
    }

    titleT->setText(track->tag(TITLE).toString() );
    albumT->setText(track->tag(ALBUM).toString() );
    artistT->setText(track->tag(ARTIST).toString() );
//     commentT->setText(track->tag(COMMENT).toString() );
//     genreT->setText(track->tag(GENRE).toString() );
    
    cover->setCover(track->cover() );
    stars->setRating(track->tag(RATING).toInt());

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
    if(f->setTag(Basic::RATING,n) )
    {
	stars->setRating(n);
    }    
}

void playingInfo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPos = event->pos();
    }
    else
    {
	   QWidget::mousePressEvent(event);
    }
}


void playingInfo::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            performDrag();
            //after the drag we get no mouse released event due to a bug
            //we  create that event manualy
            QMouseEvent *e=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(-1,-1),Qt::NoButton,Qt::LeftButton,Qt::NoModifier);
            mouseReleaseEvent (e);
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

void playingInfo::performDrag()
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
    drag->setPixmap(QPixmap(decor->tagIcon(-1).pixmap(48,48)) );

    drag->exec(Qt::CopyAction);
}