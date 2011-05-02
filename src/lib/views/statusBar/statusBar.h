#ifndef PSTATUSBAR_H
#define PSTATUSBAR_H

// #include"playerNamespace.h"
// #include".h"
#include<QLabel>
#include<QStatusBar>

#include"nowPlayList/nplaylist.h"

namespace views
{
class statusBar :public QStatusBar
{
    Q_OBJECT
    public:
	statusBar(QWidget *parent=0);
    //     QStatusBar* statusBar();
    //     void addPermanentWidget(QWidget *w);
    //     void removeWidget(QWidget *w);
	~statusBar();
	void init();
  protected:    
	int timeOut;
	
	QLabel *label;

    public slots:
	void showMessage(const QString &s,int time=-1);

    // 	  void setTrackTime(int l);

    private slots:
	void setTrackTime();


};//class
};//namespace

#endif
