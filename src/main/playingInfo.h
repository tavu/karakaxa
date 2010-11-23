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

	nplPointer track;

	QLabel *l;

    public slots:
	void update(QString path);
	void getInfo();
};
#endif
