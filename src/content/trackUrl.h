#ifndef TRACKURL_H
#define TRACKURL_H
#include <kurl.h>
class trackUrl
{
public:
    virtual KUrl url( int row) const=0;
};
#endif
