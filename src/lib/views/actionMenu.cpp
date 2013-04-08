#include"actionMenu.h"
#include<nowPlayList/nplaylist.h>
#include<QApplication>
views::actionMenu::actionMenu()
{
    repeatPlaylistA=0;
    clearPlaylistA = new QAction( KIcon("edit-clear-list"),tr("clear"), this );
    connect(clearPlaylistA,SIGNAL(triggered( bool)),core::npList(),SLOT(clear() ) );

    sufflePlaylistA = new QAction( KIcon("roll"),tr("suffle"), this );    
    connect(sufflePlaylistA,SIGNAL(triggered( bool)),core::npList(),SLOT(suffle() ) );    
    
    nextA = new QAction(  views::decor->next(),"play next", this );
    connect(nextA,SIGNAL(triggered( bool)),core::engine(),SLOT(next() ) );
    
    previousA = new QAction(  views::decor->previous() ,"play previous", this );    
    connect(previousA,SIGNAL(triggered( bool)),core::engine(),SLOT(previous() ) );

    playPauseA = new QAction(  views::decor->play(),"play-pause", this );
    connect(playPauseA,SIGNAL(triggered( bool)),core::engine(),SLOT(playPause() ) );
    
    volumeAction = new QAction(  decor->volumeMedium(),tr("mute"), this );    
    connect(volumeAction,SIGNAL(triggered( bool)),core::engine(),SLOT(muteToggle() ) );
    connect(core::engine()->getAudio(),SIGNAL(volumeChanged(qreal)),this,SLOT(volumeC(qreal)));
    volumeC(core::engine()->getAudio()->volume() );
    
    quitAction = new QAction(KIcon("application-exit"), tr("&Quit"), this);    
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

QAction* views::actionMenu::repeatPlaylist()
{
    if(repeatPlaylistA==0 )
    {
        repeatPlaylistA = new QAction( tr("playlist-repeat"), this );
        connect(repeatPlaylistA,SIGNAL(triggered(bool)),core::npList(),SLOT(repeatToggle()) );
        connect(core::npList(),SIGNAL(repeatChanged(bool)),this,SLOT(repeatPlaylistSlot(bool)) );
        repeatPlaylistSlot(core::npList()->repeat() );
    }
    return repeatPlaylistA;    
}



void views::actionMenu::repeatPlaylistSlot(bool repeat)
{
    if(repeat)
    {
        repeatPlaylistA->setToolTip(tr("repeat playlist") );
        repeatPlaylistA->setIcon(decor->icon("repeat-playlist") );
    }
    else
    {
        repeatPlaylistA->setToolTip(tr("stop at last track") );             
        repeatPlaylistA->setIcon(decor->icon("not-repeat-playlist") );
    }
}

void views::actionMenu::stateChanged(Phonon::State state)
{
    if (state==Phonon::ErrorState|| state==Phonon::PausedState )
        playPauseA->setIcon(decor->play() );
    else
        playPauseA->setIcon(decor->pause() ); 
}

void views::actionMenu::volumeC(qreal v)
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

views::actionMenu* views::actionMenu::instance()
{
    if ( _instance==0 ) {
        _instance=new actionMenu;
    }
    return _instance;
}


views::actionMenu* views::actionMenu::_instance=0;