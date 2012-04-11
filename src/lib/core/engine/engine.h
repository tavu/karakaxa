#ifndef ENGINE_H
#define ENGINE_H

// #include <phonon>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <phonon/audiodataoutput.h>
#include <Phonon/MediaController>
#include<QString>
#include<kurl.h>
#include<QMutex>
// #include"../coreNamespace.h"
namespace core
{
class soundEngine :public QObject
{
    Q_OBJECT
    public:
        soundEngine(QObject *parent=0);
        Phonon::AudioOutput* getAudio();
        ~soundEngine();
        void init();
        Phonon::MediaObject* getMediaObject();
        inline bool isMuted();

        qreal volume()
        {
            return audioOutput->volume();
        }

        void setVolume(qreal n)
        {
            audioOutput->setVolume(n);
        }

    private:
        Phonon::MediaObject* mediaObject;
        Phonon::AudioOutput *audioOutput;
        Phonon::AudioDataOutput *audioDataOutput;
        Phonon::MediaController   *controller;

        int errors;
        QMutex mutex;
        bool flag;

    private slots:
        void getNext();
        void mediaStateChanged (Phonon::State, Phonon::State);
        void newSource( const Phonon::MediaSource  );


    public slots:
        bool next();
        bool previous();
        bool play(int n);
        bool play();
        void setMute(bool);
        void muteToggle();

        void playPause();


    signals:
        void stateChanged (Phonon::State state);
        void trackChanged (QString );
};

extern soundEngine *engine;
};
#endif
