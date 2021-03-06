#include"engine.h"
#include<Basic/status.h>
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
        audioOutput(0),
        _newSource(true)
{
    mediaObject = new Phonon::MediaObject(this);
//     mediaObject->setTickInterval( 100 );
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);

    audioDataOutput = new Phonon::AudioDataOutput( this );

    Phonon::createPath( mediaObject, audioDataOutput );
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);

//     controller = new Phonon::MediaController( mediaObject);


    connect(mediaObject,SIGNAL( aboutToFinish () ),this ,SLOT ( getNext() ) );
    connect(mediaObject,SIGNAL( currentSourceChanged( const Phonon::MediaSource  ) ),this ,SLOT ( newSource( const Phonon::MediaSource  ) ) );
    connect(mediaObject,SIGNAL( stateChanged ( Phonon::State , Phonon::State ) ),this ,SLOT ( mediaStateChanged ( Phonon::State , Phonon::State ) ));
    connect(mediaObject,SIGNAL( totalTimeChanged(qint64)),this,SLOT(totalTimeSlot(qint64)) );
}

core::soundEngine::~soundEngine()
{
        delete mediaObject;
        delete audioOutput;
}

bool core::soundEngine::play(int n)
{
    //mutex.lock();
    QString s=npList()->playUrl(n);

    if (s.isNull() || s.isEmpty() )
    {
        //mutex.unlock();
        return false;
    }
    _newSource=true;
    mediaObject->setCurrentSource(s);
    mediaObject->clearQueue();
    mediaObject->play();
    //mutex.unlock();

    return true;
}

bool core::soundEngine::isPlaying()
{
    return mediaObject->state() != Phonon::PausedState && mediaObject->state() != Phonon::ErrorState;
}


bool core::soundEngine::next()
{
    //mutex.lock();
    QString s=npList()->next();

    if (s.isEmpty() )
    {
        //mutex.unlock();
        mediaObject->stop();
        return false;
    }
    _newSource=true;
    mediaObject->setCurrentSource(s);
    mediaObject->clearQueue();
    mediaObject->play();

    //mutex.unlock();

//      emit(trackChanged(s) );

    return true;
}

bool core::soundEngine::previous()
{
    //mutex.lock();
    QString s=npList()->previous();

    if (s.isEmpty() )
    {
        mediaObject->stop();
        //mutex.unlock();
        return false;
    }
    _newSource=true;
    mediaObject->setCurrentSource( s );
    mediaObject->clearQueue();
    mediaObject->play();
    //mutex.unlock();

//      emit(trackChanged(s) );
    return true;
}

void core::soundEngine::getNext()
{
    //mutex.lock();
    QString s=npList()->next();

    if (s.isEmpty() )
    {
        //mutex.unlock();
        return ;
    }
    _newSource=true;
    mediaObject->enqueue( s );
    
    //mutex.unlock();

    return ;
}

MediaObject* core::soundEngine::getMediaObject()
{
    return mediaObject;
}

void core::soundEngine::mediaStateChanged ( Phonon::State newstate, Phonon::State oldstate )
{
//    qDebug()<<oldstate<<"  "<<newstate<<"	"<<mediaObject->state();
    emit(stateChanged (newstate) );

    if (newstate==Phonon::ErrorState )
    {
        if (mediaObject->errorType()==Phonon::FatalError)
        {
		  qDebug()<<"fatal";
        }
        qDebug()<<"engine error "<<mediaObject->errorString();
        errors++;

        if(errors<MAX_ERR)
        {
    // 	    next();
        }
        Basic::msg()->error(tr("playing error") );
    }
    if(newstate==Phonon::PlayingState)
    {
        errors=0;
    }

}

void core::soundEngine::playPause()
{

    if (!isPlaying() )
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
    //mutex.lock();

    if (mediaObject->currentSource().url().isEmpty() )
    {

        //this is the same as play(int n)
        //we write it agane because the mutex is alrede locked
        QString s=npList()->playUrl(0);

        if (s.isEmpty() )
        {
            //mutex.unlock();
            return false;
        }
        
        _newSource=true;
        mediaObject->setCurrentSource( s );
        
        mediaObject->play();
        //mutex.unlock();

        return true;
    }
    else
    {
        mediaObject->play();
    }
    //mutex.unlock();
    return true;
}

Phonon::AudioOutput* core::soundEngine::getAudio()
{
    return audioOutput;
}

void core::soundEngine::newSource( const Phonon::MediaSource  s)
{
    /*
     * Some times due to a bug the mediaObject emits the newSource signal multiple times.
     * We prevent emiting the trackChanged signal more than one times by checking the _newSource variable
     */
    if(!_newSource)
    {
        return ;
    }
    _newSource=false;

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

    mediaObject->clearQueue();

    if(_totalTime )
    {
        emit (totalTimeChanged(mediaObject->totalTime() ) );
    }

}

void soundEngine::totalTimeSlot(qint64 time)
{
    if(_newSource )
    {
        _totalTime=true;
    }
    else
    {
        emit (totalTimeChanged(time) );
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

core::soundEngine* core::soundEngine::engine=0;