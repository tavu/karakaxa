#include"engine.h"
#include"../status/playerStatus.h"
#include"../nowPlayList/nplaylist.h"
// #include"../core.cpp"
using namespace Phonon;
using namespace core;
#include<QDebug>
#define MAX_ERR	10
core::soundEngine::soundEngine(QObject *parent)
        :QObject(parent),
        errors(0),
        mediaObject(0),
        audioOutput(0)
{
    mediaObject = new Phonon::MediaObject();
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);

    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject,SIGNAL( aboutToFinish () ),this ,SLOT ( getNext() ) );
    connect(mediaObject,SIGNAL( currentSourceChanged( const Phonon::MediaSource  ) ),this ,SLOT ( newSource( const Phonon::MediaSource  ) ) );
    connect(mediaObject,SIGNAL( stateChanged ( Phonon::State , Phonon::State ) ),this ,SLOT ( mediaStateChanged ( Phonon::State , Phonon::State ) ));
  
}

core::soundEngine::~soundEngine()
{
        delete mediaObject;
        delete audioOutput;
}

void core::soundEngine::init()
{

}

bool core::soundEngine::play(int n)
{
    mutex.lock();
    QString s=npList->playUrl(n);

    if (s.isNull() || s.isEmpty() )
    {
        mutex.unlock();
        return false;
    }
//     qDebug()<<"file "<<s;

    mediaObject->setCurrentSource(s);
    mediaObject->play();
    mutex.unlock();

    return true;
}

bool core::soundEngine::next()
{
    mutex.lock();
    QString s=npList->next();

    if (s.isEmpty() )
    {
        mutex.unlock();
        mediaObject->stop();
        return false;
    }

    mediaObject->setCurrentSource(s);

    mediaObject->play();

    mutex.unlock();

//      emit(trackChanged(s) );

    return true;
}

bool core::soundEngine::previous()
{
    mutex.lock();
    QString s=npList->previous();

    if (s.isEmpty() )
    {
        mediaObject->stop();
        mutex.unlock();
        return false;
    }
    mediaObject->setCurrentSource( s );
    mediaObject->play();
    mutex.unlock();

//      emit(trackChanged(s) );
    return true;
}

void core::soundEngine::getNext()
{
    mutex.lock();
    QString s=npList->next();

    if (s.isEmpty() )
    {
        mutex.unlock();
        return ;
    }
    mediaObject->enqueue( s );
//      mediaObject->play();
    mutex.unlock();

    return ;
}

MediaObject* core::soundEngine::getMediaObject()
{
    return mediaObject;
}

void core::soundEngine::mediaStateChanged ( Phonon::State newstate, Phonon::State oldstate )
{
    qDebug()<<oldstate<<"  "<<newstate<<"	"<<mediaObject->state();
    emit(stateChanged (newstate) );
    
    if (newstate==Phonon::ErrorState )
    {
        if (mediaObject->errorType()==Phonon::FatalError)
        {
	  qDebug()<<"fatal";
        }
        qDebug()<<"state";
        qDebug()<<"engine error "<<mediaObject->errorString();
        errors++;
	
	if(errors<MAX_ERR)
	{
// 	    next();
	}
	status->addError("playing error");
    }
    if(newstate==Phonon::PlayingState)
    {
	errors=0;
    }


}

void core::soundEngine::playPause()
{

    if (mediaObject->state() ==Phonon::PausedState||mediaObject->state() ==Phonon::ErrorState)
    {
        play();
    }
    else
    {
        mediaObject->pause();
    }
}

bool core::soundEngine::play()
{
    //check that there is a loaded file and plays it.
    //if there isn't load the first file
    mutex.lock();

    if (mediaObject->currentSource().url().isEmpty() )
    {

        //this is the same as play(int n)
        //we write it agane because the mutex is alrede locked
        QString s=npList->playUrl(0);

        if (s.isEmpty() )
        {
            mutex.unlock();
// 	       errors<<"can't play this";
            return false;
        }
        mediaObject->setCurrentSource( s );
        mediaObject->play();
        mutex.unlock();

        return true;
    }
    else
    {
        mediaObject->play();
    }
    mutex.unlock();
    return true;
}

Phonon::AudioOutput* core::soundEngine::getAudio()
{
    return audioOutput;
}

void core::soundEngine::newSource( const Phonon::MediaSource  s)
{
    QUrl u=s.url();
    if (s.type()==Phonon::MediaSource::LocalFile)
    {
        emit(trackChanged(u.toLocalFile()) );
    }
    else if (s.type()==Phonon::MediaSource::Stream)
    {
        emit(trackChanged(u.path() ) );
    }
    else
    {
        emit(trackChanged(QString() ) );
    }

}

void core::soundEngine::setMute(bool f)
{
    //due to a bug we don't use setMute from audioOutput but we set the volume to zero
    static qreal v=audioOutput->volume();    
    if(f)
    {
	v=audioOutput->volume();    
	audioOutput->setVolume(0);
    }
    else if(v==0)
    {
	audioOutput->setVolume(0.5);
    }
    else
    {
	audioOutput->setVolume(v);
    }
}

void core::soundEngine::muteToggle()
{
    setMute(!isMuted());
}

bool core::soundEngine::isMuted()
{
    return audioOutput->volume()==0;
}

namespace core
{
    soundEngine *engine;
}