#ifndef PSTATUSBAR_H
#define PSTATUSBAR_H

#include"playerNamespace.h"
#include<QLabel>
#include<QStatusBar>

#include"nowPlayList/nplaylist.h"

namespace player
{
class pStatusBar :public QObject
{
    Q_OBJECT
public:
    pStatusBar(QWidget *parent=0);
    QStatusBar* statusBar();
    void addPermanentWidget(QWidget *w);
    void removeWidget(QWidget *w);
    ~pStatusBar();
    void init();
private:
    QStatusBar *bar;
    int timeOut;

    QFrame *f;
    QLabel *label;

public slots:
    void showMessage(const QString &s,int time=-1);

// 	  void setTrackTime(int l);

private slots:
    void setTrackTime();

signals:
    void message(const QString &s,int time);


};//class
};//namespace

#endif
