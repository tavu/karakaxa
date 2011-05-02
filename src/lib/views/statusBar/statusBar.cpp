#include"statusBar.h"
#include<QDebug>
#include"../../core/status/playerStatus.h"
#include"../../core/nowPlayList/nplaylist.h"
#include"../viewsFunc.h"
using namespace core;
views::statusBar::statusBar(QWidget *parent)
        :QStatusBar(parent),
        timeOut(7000)
{
    label=new QLabel(this);
    setSizeGripEnabled(false);
    setFixedHeight(25);
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::VLine);

    addPermanentWidget(f);
    addPermanentWidget(label);

    connect(status,SIGNAL(errorMessage(const QString &) ),this,SLOT(showMessage(const QString &) ), Qt::QueuedConnection );
    connect(status,SIGNAL(infoMessage(const QString &) ),this,SLOT(showMessage(const QString &) ), Qt::QueuedConnection );
    connect(npList,SIGNAL(inserted(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    connect(npList,SIGNAL(removed(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    connect(npList,SIGNAL(cleared() ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
}

void views::statusBar::showMessage(const QString &s,int time)
{
     if (time==-1)
     {
         time=timeOut;
    }
    QStatusBar::showMessage(s,time);
}

/*
void views::statusBar::addPermanentWidget(QWidget *w)
{
    w->setFixedHeight(bar->height()-5);
    bar->insertPermanentWidget(0,w);
}
*/


void views::statusBar::init()
{
//     bar=new QStatusBar();


}

void views::statusBar::setTrackTime()
{
    int l=core::npList->getLength();
    int n=npList->size();
    label->setText(QString::number(n)+" tracks "+views::prettyLength(l) );
}


views::statusBar::~statusBar()
{
//       delete label;
//       delete f;
//       delete bar;

}
