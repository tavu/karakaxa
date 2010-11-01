#ifndef LIBRARY_H
#define LIBRARY_H

#include<QPushButton>


#include<player.h>
#include<KToolBar>
#include<KLineEdit>
#include<KIcon>

#include"artistWidget.h"
#include"albumTrack.h"

class library :public abstractContent
{
    Q_OBJECT
public:
    library(QWidget *parent=0);
    QString name() const;
    void update(const int n);

private:

    QWidget *buttonWidget;

    artistWidget *artistV;
    albumTrack  *albumTrV;
    QStackedWidget *stack;

    QIcon playIcon;

    KToolBar *toolBar;
    QAction *backAction;
    QAction *forwardAction;
    KLineEdit *searchLine;

    QPushButton *refresh;

    QAction *scan;
    QAction *config;
    //functions
    void buttonInit();
    void inline toolBarInit();

public slots:
    void libraryScan();
    void toAlbum(const QString &s1,const QString &s2);
    void goToArtist();
    void goToAlbum();
//      private slots:
// 	  void search();
};

#endif
