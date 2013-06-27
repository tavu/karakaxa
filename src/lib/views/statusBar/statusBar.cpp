#include"statusBar.h"
#include<QDebug>
#include"core/nowPlayList/nplaylist.h"
#include"views/viewsFunc.h"
#include"Basic/status.h"

#define W_WIDTH 200
#define W_TIME  3000

using namespace core;
views::statusBar::statusBar(QWidget *parent)
        :QStatusBar(parent),
        timeOut(7000),
        timer(0)
{
    label=new QLabel(this);
    setSizeGripEnabled(false);
    setFixedHeight(35);
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::VLine);

    addPermanentWidget(f);
    addPermanentWidget(label);

    connect(Basic::msg(),SIGNAL(errorMessage(const QString &) ),this,SLOT(showMessage(const QString &) ) );
    connect(Basic::msg(),SIGNAL(infoMessage(const QString &) ),this,SLOT(showMessage(const QString &) ) );
    connect(npList(),SIGNAL(tracksInserted(int,int)),this,SLOT(setTrackTime() ));
    connect(npList(),SIGNAL(tracksRemoved(int,int)),this,SLOT(setTrackTime() ) );
    connect(npList(),SIGNAL(cleared() ),this,SLOT(setTrackTime() ) );

//     connect(database::db(),SIGNAL(stateCanged(dbState,dbState)),this,SLOT(addScanner()));
    connect(database::db(),SIGNAL(newJob(database::dbJobP) ),this,SLOT(addJob(database::dbJobP)) );
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
    int l=core::npList()->getLength();
    int n=npList()->size();
    label->setText(QString::number(n)+" tracks "+views::prettyLength(l) );
}


views::statusBar::~statusBar()
{
//       delete label;
//       delete f;
//       delete bar;

}

void views::statusBar::addJob(database::dbJobP job)
{
    if(job.isNull() )
    {
        return ;
    }

    QWidget *w=job->widget();
    if(w!=0)
    {
        timer=new QTimer(this);
        timer->setInterval(W_TIME);
        jobMap[timer]=job;
        w->setFixedWidth(W_WIDTH);
        insertPermanentWidget(0,w);
        connect(timer,SIGNAL(timeout() ),this,SLOT(jobDone() ) );
        connect(job.data(),SIGNAL(finished()),timer,SLOT(start()) );
    }
}

void views::statusBar::jobDone()
{
    QObject *sen=sender ();
    database::dbJobP job=jobMap.take(sen);

    if(!job.isNull() && job->widget()!=0)
    {
        removeWidget(job->widget());
    }
    delete sen;
}
