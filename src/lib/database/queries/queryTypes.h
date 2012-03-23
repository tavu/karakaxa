#ifndef QUERIESTYPES_H
#define QUERIESTYPES_H

namespace database
{
    static const short int MATCHQ=0;
    static const short int TAGQ=1;

    enum equal
    {
        EQUAL=0,
        STARTS,
        ENDS,
        CONTAINS,
        GREATER,
        LESS
    };

    
}
#endif
