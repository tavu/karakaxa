#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H
#include <KToolBar>
#include<QAction>
#include <Phonon/VolumeSlider>
class volumeBar :public KToolBar
{
    Q_OBJECT
    public:
	volumeBar(QWidget *parent=0);
    private:
	QAction *volumeAction;
	Phonon::VolumeSlider *volume;
	
    private slots:
	void volumeC(qreal v);
};
#endif