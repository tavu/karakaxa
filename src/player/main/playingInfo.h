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

	QLabel 	  *titleIcon;
	QLabel 	  *albumIcon;
	QLabel 	  *artistIcon;
	QLabel 	  *commentIcon;
	
	core::nplPointer track;

    public slots:
	void update();
	void getInfo();
	void setRating(int);
};
#endif
