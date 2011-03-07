#include"pStatusBar.h"
#include<QDebug>
player::pStatusBar::pStatusBar(QWidget *parent)
        :QObject(parent),
        timeOut(7000)
{

}

void player::pStatusBar::showMessage(const QString &s,int time)
{
    if (time==-1)
    {
        time=timeOut;
    }
    emit message(s,time) ;
}

QStatusBar* player::pStatusBar::statusBar()
{
    return bar;


}
void player::pStatusBar::addPermanentWidget(QWidget *w)
{
    w->setFixedHeight(bar->height()-5);
    bar->insertPermanentWidget(0,w);
}

void player::pStatusBar::removeWidget(QWidget *w)
{
    bar->removeWidget(w);
}

void player::pStatusBar::init()
{
    bar=new QStatusBar();
    label=new QLabel();
    bar->setSizeGripEnabled(false);
    bar->setFixedHeight(25);
    f=new QFrame();
    f->setFrameStyle(QFrame::VLine);

    bar->addPermanentWidget(f);
    bar->addPermanentWidget(label);

    //that connection allow to send messages thread safe
    //thats why we create that class
    connect(this,SIGNAL(message(const QString &,int) ),bar,SLOT(showMessage(const QString &,int) ), Qt::QueuedConnection );
    connect(&player::npList,SIGNAL(inserted(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    connect(&player::npList,SIGNAL(removed(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );

}

void player::pStatusBar::setTrackTime()
{
    int l=npList.getLength();
    int n=npList.size();
    label->setText(QString::number(n)+" tracks "+player::prettyLength(l) );
}


player::pStatusBar::~pStatusBar()
{
//       delete label;
//       delete f;
//       delete bar;

}
