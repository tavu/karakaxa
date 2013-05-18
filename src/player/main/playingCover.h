#ifndef PLAYING_COVER_H
#define PLAYING_COVER_H
#include<coverWidget/coverWidget.h>

class playingCover :public views::coverWidget
{
    public: 
        playingCover(QWidget *parent=0);
         void paintEvent ( QPaintEvent * );
    protected:
         void   mouseReleaseEvent ( QMouseEvent * event );
};
#endif