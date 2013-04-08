#include"volumeBar.h"
#include"../views.h"
#include"../../core/core.h"
#include<actionMenu.h>

// #define ICONZISE QSize(25,25)
using namespace core;


views::volumeBar::volumeBar(QWidget *parent)
     :KToolBar("volumeBar",parent)
{
    setToolButtonStyle( Qt::ToolButtonIconOnly );
    addAction( menus()->volume() );        
    volume = new Phonon::VolumeSlider(engine()->getAudio(),this );
    volume->setMuteVisible(false);    
    addWidget( volume );
}