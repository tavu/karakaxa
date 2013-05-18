#ifndef PLAYING_WIDGET_H
#define PLAYING_WIDGET_H

#include<slider.h>
#include<coverWidget/coverWidget.h>
#include<ratingWidget/ratingWidget.h>
#include<QLabel>
#include <QToolBar>
#include<volumeBar/volumeBar.h>
#include<nowPlayList/nplTrack.h>
#include"scrolText.h"
#include <kratingwidget.h>
class playingWidget :public QWidget
{
    Q_OBJECT
    public:
        playingWidget(QWidget *parent);
        
    private:
        views::coverWidget  *cover;
        views::sliderWidget *slider;
        views::ratingWidget *rating;  
        QWidget *infoW;
        scrolText *titleL;
        scrolText *infoL;
        views::volumeBar *volumeB;
        
        core::nplPointer track;        
        QPoint startPos;
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void performDrag();
    private slots:
        void updateInfo();
        void setRating(int n);
        void getInfo();
        
};

#endif
