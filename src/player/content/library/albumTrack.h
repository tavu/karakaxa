#ifndef ALBUMTRACK_H
#define ALBUMTRACK_H

#include<QWidget>
#include"albumModel.h"
#include"songView.h"
#include"albumWidget.h"
#include<QPushButton>
#include <QLinkedList>
#include<views.h>
 
class albumTrack :public QWidget
{
    Q_OBJECT

public:
    albumTrack(QWidget *parent=0);
//     void updateTrack();
    void updateQueries();
private:

    void labelInit();
    void albumVInit();
    void trackVInit();


    albumModel *albumM;
    views::trackModel *trackM;

    QString search;

    QString artist;

    albumWidget *albumV;
    views::treeView *trackV;
//     treeViewDelegate *trackD;


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
    bool update();

};

#endif