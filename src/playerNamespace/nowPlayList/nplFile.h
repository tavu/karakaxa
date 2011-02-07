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
	int	 	type() ;
	int	 	length() ;
	QString 	cover();
	
	QVariant	artist();	
	QVariant	tag(tagsEnum);
	
	audioFile*	getAudioFile();

    private:

	audioFile *file;

};
};
#endif
