#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H
#include <KToolBar>
#include<QAction>
#include <Phonon/VolumeSlider>
namespace views
{
  
class volumeBar :public KToolBar
{
    Q_OBJECT
    public:
        volumeBar(QWidget *parent=0);

    private:
        QAction *volumeAction;
        Phonon::VolumeSlider *volume;
};

};
#endif