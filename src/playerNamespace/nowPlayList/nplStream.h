#ifndef NPLSTREAM_H
#define NPLSTREAM_H

#include"nplTrack.h"
#include"../playerNamespace.h"
#include<KUrl>
#include<QObject>
#include <phonon>

namespace player
{
class nplStream :public QObject,public nplTrack
{
    Q_OBJECT
    public:
	nplStream(QString s);
	QString path();
	QString title();
	int 	type();
	
	QVariant tag(tagsEnum t);
    protected:
	KUrl 	url;
	QString albumS;
	QString titleS;

    Phonon::MediaObject *mediaObject;
// protected slots:
//     void getMetaData();

};
};
#endif
