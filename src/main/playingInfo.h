#ifndef PLAYINGINFO_H
#define PLAYINGINFO_H
#include<player.h>
#include<QLabel>
#include"scrolText.h"
using namespace player;
class playingInfo :public QWidget
{
    Q_OBJECT
    public:
	playingInfo(QWidget *parent=0);
	~playingInfo();
	
    private:
	player::coverWidget *cover;
	player::starWidget *stars;
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
	
	nplPointer track;

    public slots:
	void update(QString path);
	void getInfo();
	void setRating(int);
};
#endif
