#ifndef KARAKAXA_APP
#define KARAKAXA_APP

#include <kuniqueapplication.h>
#define VERSION "0.7"
class karakaxa :public KUniqueApplication
{
    public:
        karakaxa(int argc, char *argv[]);
        void commitData(QSessionManager& manager );
        ~karakaxa();
    
};
#endif
