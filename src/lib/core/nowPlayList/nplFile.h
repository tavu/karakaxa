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
    Q_OBJECT
    public:

        nplFile(QString s);

        ~nplFile();

        QString		title() ;
        QString 	path() ;
        int	 	    type() ;
        int	 	    length() ;
        QString 	cover();

        nplTrack*	clone();
        QVariant	artist();
        QVariant	tag(int);

        audioFile*	getAudioFile();
        void 		play();

        void setLoadFlag(int f)
        {
            _loadFlag=f;
        }

        int loadFlag() const
        {
            return _loadFlag;
        }
        
    private:
        audioFile   *file;
        short int   _loadFlag;
    private slots:
        void emitCh(audioFiles::audioFile f);
    

};
};
#endif
