#ifndef ALBUMTRACK_H
#define ALBUMTRACK_H

#include<QWidget>
#include"albumModel.h"
#include"songModel.h"
#include"songView.h"
#include"albumWidget.h"
#include"../myTreeView.h"
#include"../treeViewDelegate.h"
#include<QPushButton>

class albumTrack :public QWidget
{
    Q_OBJECT

public:
    albumTrack(QWidget *parent=0);

private:

    void labelInit();
    void albumVInit();
    void trackVInit();


    albumModel *albumM;
    songModel *trackM;

    QString search;

    QString artist;

    albumWidget *albumV;
    myTreeView *trackV;
    treeViewDelegate *trackD;


    QLabel *sLabel;
    QLabel *pLabel;

    QPushButton *leftB;
    QPushButton *rightB;

    QWidget *albumW;

public slots:
    void setArtist(const QString &artist,const QString &labelS);
    void setSearch(const QString &s);

//      private slots:
    void albumActivated(const QModelIndex &n);
    void update();

private slots:
    void play(const QModelIndex);
};

#endif
