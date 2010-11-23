#include"volumeBar.h"
#include<player.h>

#define ICONZISE QSize(25,25)

volumeBar::volumeBar(QWidget *parent)
     :KToolBar("volumeBar",parent)
{
    setIconSize(ICONZISE );
    setToolButtonStyle( Qt::ToolButtonIconOnly );
    
    volumeAction = new QAction(  decor.volumeMedium(),"volume", this );
    addAction( volumeAction );
    connect(volumeAction,SIGNAL(triggered( bool)),&engine,SLOT(muteToggle() ) );
    connect(engine.getAudio(),SIGNAL(volumeChanged(qreal)),this,SLOT(volumeC(qreal)));
            
    volume = new Phonon::VolumeSlider(engine.getAudio(),this );
//     volume->setFixedWidth(150);
    volume->setMuteVisible(false);
//     volume->setFixedWidth(150);
    
    volumeC(engine.getAudio()->volume() );
    addWidget( volume );
}

void volumeBar::volumeC(qreal v)
{
    if(v==0)
    {
	volumeAction->setIcon(decor.muted() );
    }
    else if(v<0.33)
    {	
	volumeAction->setIcon(decor.volumeLow() );	  
    }
    else if(v<0.67)
    {
	volumeAction->setIcon(decor.volumeMedium() );	
    }
    else
    {
	volumeAction->setIcon(decor.volumeHigh() );
    }
}