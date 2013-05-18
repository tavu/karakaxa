#ifndef TRACK_RECORD_H
#define TRACK_RECORD_H

#include"baseRecord.h"
#include<QString>
namespace database
{
    
namespace dbPrivate
{

class trackRecord :public baseRecord
{
    public:
        trackRecord(QString path);
        trackRecord(){};
        ~trackRecord(){};
        int save();
    protected:
        
        void            clearArtist();
        void            clearAlbum();
        void            clearGenre();
        void            clearComposer();
        
};//class

}//dbPrivate

}//database
#endif