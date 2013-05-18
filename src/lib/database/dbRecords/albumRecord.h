#ifndef ALBUM_RECORD_H
#define ALBUM_RECORD_H

#include"simplyRecord.h"
namespace database
{

namespace dbPrivate
{

class albumRecord :public baseRecord
{
    public:
        albumRecord();
        int type() const;
};//class

}//databasedbPrivate

}//database
#endif