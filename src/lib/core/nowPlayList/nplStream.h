#ifndef NPLSTREAM_H
#define NPLSTREAM_H

#include"nplTrack.h"
// #include"../playerNamespace.h"
#include<kurl.h>
#include<QObject>
#include <Phonon/MediaObject>

namespace core
{
class nplStream :public nplTrack
{
    Q_OBJECT
    public:
        nplStream(QString s);
        QString 	path();
        QString	 	title();
        int 		type();

        QVariant 	tag(int t);
        void 		play();
        void 		finish();
        nplTrack*	clone();
    protected:
        KUrl 	url;
        QString albumS;
        QString titleS;
        QString artistS;
        QString commentS;
        QString genreS;

        Phonon::MediaObject *mediaObject;
    protected slots:
        void stateCh(Phonon::State newstate, Phonon::State oldstate);

        void getMetaData();

};
};
#endif
