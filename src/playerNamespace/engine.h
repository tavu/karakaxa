#ifndef ENGINE_H
#define ENGINE_H

#include <phonon>
#include <Phonon/AudioOutput>
// #include <Phonon/MediaObject>
#include<QString>
#include<KUrl>
#include<QMutex>
#include"playerNamespace.h"
namespace player
{
class soundEngine :public QObject
{
    Q_OBJECT
public:
    soundEngine(QObject *parent=0);
    Phonon::AudioOutput* getAudio();
    ~soundEngine();
    void init();

private:
    Phonon::MediaObject* mediaObject;
    Phonon::AudioOutput *audioOutput;

    int errors;
    QMutex mutex;
    bool flag;

private slots:
    void getNext();
    void mediaStateChanged (Phonon::State, Phonon::State);

public slots:
    bool next();
    bool previous();
    bool play(int n);
    bool play();
    Phonon::MediaObject* getMediaObject();
    void playPause();
    void newSource( const Phonon::MediaSource  );

signals:
    void stateChanged (Phonon::State state);
    void trackChanged (QString );
};

};
#endif
