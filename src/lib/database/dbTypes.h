#ifndef DBTYPES_H
#define DBTYPES_H

namespace database
{

    enum dbState
    {
        NORMAL=0 ,
        UPDATE   ,
        RESCAN
    };    
}
#endif