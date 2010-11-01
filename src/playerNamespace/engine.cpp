#include"engine.h"
#include<player.h>
using namespace Phonon;
using namespace player;
#include<QDebug>
#define test qDebug()<<"TETE";
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
    connect(mediaObject,SIGNAL( stateChanged ( Phonon::State , Phonon::State ) ),this ,SLOT ( mediaStateChanged ( Phonon::State , Phonon::State ) ),Qt::QueuedConnection  );
}

bool player::soundEngine::play(int n)
{
    mutex.lock();
    QString s=npList.playUrl(n);

    if (s.isEmpty() )
    {
        mutex.unlock();
// 	  errors<<"can't play this";
        return false;
    }
    mediaObject->setCurrentSource( s );
    mediaObject->play();
    mutex.unlock();

//      emit(trackChanged(s) );

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
//      qDebug()<<oldstate<<"  "<<newstate;
    emit(stateChanged (newstate) );



    if (newstate==Phonon::ErrorState )
    {
        if (mediaObject->errorType()==Phonon::FatalError)
        {
        }
        qDebug()<<"engine error "<<mediaObject->errorString();
        errors++;
//    	  next();
        player::statusBar.showMessage("playing error");

    }


}

void player::soundEngine::playPause()
{

    if (mediaObject->state() !=Phonon::PlayingState)
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

