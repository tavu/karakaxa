#ifndef TAG_LIST_H
#define TAG_LIST_H
#include<QVariant>

namespace audioFiles
{

struct changes
{
    int       tag;
    QVariant  value;
    int       error;
};
typedef struct changes tagChanges;
typedef QList<tagChanges> tagChangesL;

}
#endif