#ifndef ENGINE_H
#define ENGINE_H

// #include <phonon>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
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
	bool isMuted();
	
    private:
	Phonon::MediaObject* mediaObject;
	Phonon::AudioOutput *audioOutput;

	int errors;
	QMutex mutex;
	bool flag;
	bool _isMuted;

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
