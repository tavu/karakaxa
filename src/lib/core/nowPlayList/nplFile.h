#ifndef NPTFILE_H
#define NPTFILE_H

#include<QString>
#include"nplTrack.h"
// #include<playerNamespace.h>
#include"../files/audioFile.h"
// using namespace core;
using namespace audioFiles;
namespace core
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
	QVariant	tag(int);
	
	audioFile*	getAudioFile();
	void 		play();

    private:

	audioFile *file;

};
};
#endif
