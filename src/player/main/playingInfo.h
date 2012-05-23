#ifndef PLAYINGINFO_H
#define PLAYINGINFO_H
#include<views.h>
#include<nowPlayList/nplaylist.h>
#include<QLabel>
#include"scrolText.h"
// using namespace player;
class playingInfo :public QFrame
{
    Q_OBJECT
    public:
        playingInfo(QWidget *parent=0);
        ~playingInfo();
        virtual QSize sizeHint() const;

        private:
        QPoint startPos;
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void performDrag();
        views::coverWidget *cover;
        views::ratingWidget *stars;
        // 	  QLabel *titleL;
        // 	  QLabel *artistL;
        // 	  QLabel *albumL;
        // 	  QLabel *commentL;

        scrolText *titleT;
        scrolText *albumT;
        scrolText *artistT;
        scrolText *commentT;
        scrolText *genreT;

        QLabel 	  *titleIcon;
        QLabel 	  *albumIcon;
        QLabel 	  *artistIcon;
        QLabel 	  *commentIcon;
        QLabel 	  *genreIcon;

        core::nplPointer track;

    public slots:
        void update();
        void getInfo();
        void setRating(int);
};
#endif
