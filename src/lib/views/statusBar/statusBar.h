#ifndef PSTATUSBAR_H
#define PSTATUSBAR_H

// #include"playerNamespace.h"
// #include".h"
#include"nowPlayList/nplaylist.h"

#include<database.h>
#include<QLabel>
#include<QStatusBar>
#include<QMap>
#include<QTimer>

namespace views
{
class statusBar :public QStatusBar
{
    Q_OBJECT
    public:
        statusBar(QWidget *parent=0);
        ~statusBar();
        void init();

    protected:
        int timeOut;
        QLabel *label;
        QTimer *timer;
        database::dbJobP dbJob;
        QMap<QObject*,database::dbJobP> jobMap;

    public slots:
        void showMessage(const QString &s,int time=-1);

    // 	  void setTrackTime(int l);

    private slots:
        void setTrackTime();
        void addJob(database::dbJobP job);

        void jobDone();


};//class
};//namespace

#endif
