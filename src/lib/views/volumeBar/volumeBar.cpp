#include"volumeBar.h"
#include"../views.h"
#include"../../core/core.h"

#define ICONZISE QSize(25,25)
using namespace core;


views::volumeBar::volumeBar(QWidget *parent)
     :KToolBar("volumeBar",parent)
{
    setIconSize(ICONZISE );
    setToolButtonStyle( Qt::ToolButtonIconOnly );
    
    volumeAction = new QAction(  decor->volumeMedium(),tr("mute"), this );
    addAction( volumeAction );
    connect(volumeAction,SIGNAL(triggered( bool)),engine,SLOT(muteToggle() ) );
    connect(engine->getAudio(),SIGNAL(volumeChanged(qreal)),this,SLOT(volumeC(qreal)));
            
    volume = new Phonon::VolumeSlider(engine->getAudio(),this );
    volume->setMuteVisible(false);
    
    volumeC(engine->getAudio()->volume() );
    addWidget( volume );
}

void views::volumeBar::volumeC(qreal v)
{
    if(v==0)
    {
        volumeAction->setIcon(decor->muted() );
        volumeAction->setText(tr("Unmute") );
    }
    else if(v<0.33)
    {	
        volumeAction->setIcon(decor->volumeLow() );
        volumeAction->setText(tr("Mute") );
    }
    else if(v<0.67)
    {
        volumeAction->setIcon(decor->volumeMedium() );
        volumeAction->setText(tr("Mute") );
    }
    else
    {
        volumeAction->setIcon(decor->volumeHigh() );
        volumeAction->setText(tr("Mute") );
    }
}