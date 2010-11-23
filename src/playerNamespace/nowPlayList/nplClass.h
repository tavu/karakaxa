#ifndef NPLCLASS_H
#define NPLCLASS_H
#include<QSharedPointer>
namespace player
{
     class nplTrack;
     class nplStream;
     class nplFile;
};
typedef QSharedPointer<player::nplTrack> nplPointer;
#endif
