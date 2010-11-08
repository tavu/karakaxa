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
// 	  QString 	artist;
// 	  QString 	title;
// 	  QString 	album;
// 	  QString	path;
// 	  int		trackN;
// 	  int		length;
// 	  bool		onDatabase;

    QString	title() ;
    QString 	path() ;
    QString 	artist() ;
    QString 	album() ;
    QString 	type() ;
    int	 	length() ;
    int 	trackN() ;

private:

    audioFile *file;

};
};
#endif
