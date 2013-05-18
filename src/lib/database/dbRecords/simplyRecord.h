#ifndef SIMPLE_RECORD_H
#define SIMPLE_RECORD_H
#include"baseRecord.h"

namespace database
{
    
namespace dbPrivate
{
//a record with only one entry and its id
class simpleRecord :public database::dbPrivate::baseRecord
{
    public:
        simpleRecord(int t);
        int type() const;
    protected:
        int _type;

    static QString tableFromType(int t);    
};

}

}
#endif