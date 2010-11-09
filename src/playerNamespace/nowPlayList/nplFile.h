#ifndef NPTFILE_H
#define NPTFILE_H

#include<QString>
#include"nplTrack.h"
#include<playerNamespace.h>
using namespace player;
namespace player
{
class nplFile :public nplTrack
{
    public:

	nplFile(QString s);

	~nplFile();

	QString		title() ;
	QString 	path() ;
	QString 	type() ;
	int	 	length() ;
	
	QVariant	tag(tagsEnum);
	
	audioFile*	getAudioFile();

    private:

	audioFile *file;

};
};
#endif
