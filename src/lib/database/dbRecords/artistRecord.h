#ifndef ARTIST_RECORD_H 
#define ARTIST_RECORD_H

#include"baseRecord.h"
namespace database
{

namespace dbPrivate
{

class artistRecord :public baseRecord
{
    public:
        artistRecord();
        int type() const;
};//class

}//databasePrivate

}//database
#endif
