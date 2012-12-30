#ifndef KARAKAXA_APP
#define KARAKAXA_APP

#include <kuniqueapplication.h>
#define VERSION "0.7"

#ifdef DEBUG
class karakaxa :public KApplication
#else
class karakaxa :public KUniqueApplication
#endif
{
    public:
        karakaxa(int argc, char *argv[]);
        void commitData(QSessionManager& manager );
        ~karakaxa();
    
};
#endif
