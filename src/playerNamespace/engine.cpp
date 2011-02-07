#include"engine.h"
#include<player.h>
using namespace Phonon;
using namespace player;
#include<QDebug>
#define MAX_ERR	10
player::soundEngine::soundEngine(QObject *parent)
        :QObject(parent),
        errors(0),
        mediaObject(0),
        audioOutput(0)
{

}

player::soundEngine::~soundEngine()
{
//        delete mediaObject;
//        delete audioOutput;
}

void player::soundEngine::init()
{
    mediaObject = new Phonon::MediaObject();
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);

    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);

    connect(mediaObject,SIGNAL( aboutToFinish () ),this ,SLOT ( getNext() ) );
    connect(mediaObject,SIGNAL( currentSourceChanged( const Phonon::MediaSource  ) ),this ,SLOT ( newSource( const Phonon::MediaSource  ) ) );
    connect(mediaObject,SIGNAL( stateChanged ( Phonon::State , Phonon::State ) ),this ,SLOT ( mediaStateChanged ( Phonon::State , Phonon::State ) ));
}

bool player::soundEngine::play(int n)
{
    mutex.lock();
    QString s=npList.playUrl(n);

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

bool player::soundEngine::next()
{
    mutex.lock();
    QString s=npList.next();

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

bool player::soundEngine::previous()
{
    mutex.lock();
    QString s=npList.previous();

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

void player::soundEngine::getNext()
{
    mutex.lock();
    QString s=npList.next();

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

MediaObject* player::soundEngine::getMediaObject()
{
    return mediaObject;
}

void player::soundEngine::mediaStateChanged ( Phonon::State newstate, Phonon::State oldstate )
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
        player::statusBar.showMessage("playing error");
    }
    if(newstate==Phonon::PlayingState)
    {
	errors=0;
    }


}

void player::soundEngine::playPause()
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

bool player::soundEngine::play()
{
    //check that there is a loaded file and plays it.
    //if there isn't load the first file
    mutex.lock();

    if (mediaObject->currentSource().url().isEmpty() )
    {

        //this is the same as play(int n)
        //we write it agane because the mutex is alrede locked
        QString s=npList.playUrl(0);

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

Phonon::AudioOutput* player::soundEngine::getAudio()
{
    return audioOutput;
}

void player::soundEngine::newSource( const Phonon::MediaSource  s)
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

void player::soundEngine::setMute(bool f)
{
    //due to a bug we don't use setMute from audioOutput but we set the volume to zero
    static qreal v;
    if(f)
    {
	v=audioOutput->volume();    
	audioOutput->setVolume(0);
    }
    else
    {
	audioOutput->setVolume(v);
    }
    _isMuted=f;
}

void player::soundEngine::muteToggle()
{
    setMute(!_isMuted);
}

bool player::soundEngine::isMuted()
{
    return _isMuted;
}
