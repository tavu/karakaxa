#include"statusBar.h"
#include<QDebug>
#include"../../core/status/playerStatus.h"
#include"../../core/nowPlayList/nplaylist.h"
#include"../viewsFunc.h"
#include"../../core/database/scanTread.h"

using namespace core;
views::statusBar::statusBar(QWidget *parent)
        :QStatusBar(parent),
        timeOut(7000),
        scanW(0)
{
    label=new QLabel(this);
//     label->setText(prettyLength(0));
    setSizeGripEnabled(false);
    setFixedHeight(35);
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::VLine);

    addPermanentWidget(f);
    addPermanentWidget(label);

    connect(status,SIGNAL(errorMessage(const QString &) ),this,SLOT(showMessage(const QString &) ), Qt::QueuedConnection );
    connect(status,SIGNAL(infoMessage(const QString &) ),this,SLOT(showMessage(const QString &) ), Qt::QueuedConnection );
    connect(npList,SIGNAL(inserted(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    connect(npList,SIGNAL(removed(int) ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    connect(npList,SIGNAL(cleared() ),this,SLOT(setTrackTime() ), Qt::QueuedConnection );
    
    connect(db,SIGNAL(scanStart(core::scanThread*)),this,SLOT(addScan(core::scanThread*)),Qt::QueuedConnection );
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

void views::statusBar::addScan(core::scanThread* sc)
{   
    if(scanW!=0)
    {
	 removeWidget(scanW);
	 delete scanW;
    }
    scanW=sc->widget();
    scanW->setFixedWidth(230);
    insertPermanentWidget(0,scanW);
    
    QTimer *t=new QTimer(scanW);
    t->setInterval(5000);
    connect(t,SIGNAL(timeout()),this,SLOT(scanDone()));
    connect(sc,SIGNAL(finished()),t,SLOT(start()) );
//     connect(sc,SIGNAL(finished()),this,SLOT(scanDone()));
}

void views::statusBar::scanDone()
{
    removeWidget(scanW);
    delete scanW;
    scanW=0;
}
