#include"statusBar.h"
#include<QDebug>
#include"../../core/status/playerStatus.h"
#include"../../core/nowPlayList/nplaylist.h"
#include"../viewsFunc.h"
#include<scanTread.h>

using namespace core;
views::statusBar::statusBar(QWidget *parent)
        :QStatusBar(parent),
        timeOut(7000),
        timer(0)
{
    label=new QLabel(this);
//     label->setText(prettyLength(0));
    setSizeGripEnabled(false);
    setFixedHeight(35);
    QFrame *f=new QFrame(this);
    f->setFrameStyle(QFrame::VLine);

    addPermanentWidget(f);
    addPermanentWidget(label);

    connect(status,SIGNAL(errorMessage(const QString &) ),this,SLOT(showMessage(const QString &) ) );
    connect(status,SIGNAL(infoMessage(const QString &) ),this,SLOT(showMessage(const QString &) ) );
    connect(npList(),SIGNAL(tracksInserted(int,int)),this,SLOT(setTrackTime() ));
    connect(npList(),SIGNAL(tracksRemoved(int,int)),this,SLOT(setTrackTime() ) );
    connect(npList(),SIGNAL(cleared() ),this,SLOT(setTrackTime() ) );
    
    connect(database::db(),SIGNAL(stateCanged(dbState,dbState)),this,SLOT(addScanner()));
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

void views::statusBar::addScanner()
{
    using namespace database;
    if(db()->state()==NORMAL && !scanner.isNull())
    {        
        timer=new QTimer(this);
        timer->setInterval(5000);
        timer->start();
        connect(timer,SIGNAL(timeout()),this,SLOT(scanDone()));
    }
    else
    {
        if(timer!=0)
        {
            timer->stop();
            delete timer;
            timer=0;
        }
        
        if(!scanner.isNull() )
        {
            removeWidget(scanner->widget() );
        }

        scanner=db()->scanner();
        if(scanner->widget() !=0)
        {
            scanner->widget()->setFixedWidth(230);
            insertPermanentWidget(0,scanner->widget());
        }
    }    
}

void views::statusBar::scanDone()
{
    removeWidget(scanner->widget());
    scanner.clear();
    delete timer;
    timer=0;
}
