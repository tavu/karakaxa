#include"slider.h"
#include<QHBoxLayout>
#include"viewsFunc.h"
#include"../core/core.h"
#include <Phonon/MediaObject>
views::sliderWidget::sliderWidget(QWidget* parent): QWidget(parent)
{
    slider = new Phonon::SeekSlider(this);
    slider->setMediaObject(core::engine->getMediaObject() );
    slider->setIconVisible(false);

    left=new QLabel(this);
    right=new QLabel(this);

    left->setText("     ");
    right->setText("     ");
    
    timer.setSingleShot(false);
    timer.setInterval(1000);
//     connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(core::engine->getMediaObject(),SIGNAL(totalTimeChanged(qint64)),this,SLOT(updateTime()) );
    connect(core::engine->getMediaObject(),SIGNAL(tick(qint64)),this,SLOT(updateTime()) );
    
    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->addWidget(left);
    layout->addWidget(slider);
    layout->addWidget(right);

    timer.start();
}

void views::sliderWidget::updateTime()
{
    qint64 totalTime=core::engine->getMediaObject()->totalTime();
    qint64 currentTime=core::engine->getMediaObject()->currentTime();
    left->setText(views::prettyLength(currentTime));

    if(totalTime!=0)
    {
        totalTime -=currentTime;
    }

    QString s=views::prettyLength(totalTime);
    s.prepend('-');
    
    right->setText(s);
}




