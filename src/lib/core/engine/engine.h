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
void cleanUp();

class soundEngine :public QObject
{
    Q_OBJECT
    public:
        friend void core::cleanUp();
                
        Phonon::AudioOutput* getAudio();
        ~soundEngine();        
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


        static void init()
        {
            if(engine==0)
            {
                engine=new  soundEngine();
            }
        }
        static soundEngine *instance()
        {
            return engine;
        }
    private:
        soundEngine(QObject *parent=0);
        
        Phonon::MediaObject* mediaObject;
        Phonon::AudioOutput *audioOutput;
        Phonon::AudioDataOutput *audioDataOutput;
//         Phonon::MediaController   *controller;

        bool _newSource;
        bool _totalTime;
        int errors;
        QMutex mutex;

        static soundEngine *engine;

        static void cleanUp()
        {
            delete engine;
        }

    private slots:
        void getNext();
        void mediaStateChanged (Phonon::State, Phonon::State);
        void newSource( const Phonon::MediaSource  );
        void totalTimeSlot(qint64 time);


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
        void totalTimeChanged(qint64 );
};

inline soundEngine* engine()
{
    return soundEngine::instance();
}

}
#endif
