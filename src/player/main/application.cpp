#include"application.h"

#include <KApplication>
#include <unistd.h>

#include<core.h>
#include<views.h>
#include<dbFunc.h>
#include<files/audioFiles.h>

karakaxa::karakaxa(int argc, char *argv[])
#ifdef DEBUG
	:KApplication()
#else	
    :KUniqueApplication()
#endif	
{    
    setApplicationName("karakaxa");
    setApplicationVersion(VERSION);
    setOrganizationName("karakaxa");
}

void karakaxa::commitData(QSessionManager& manager)
{
    emit commitDataRequest(manager);
    closeAllWindows ();
}

karakaxa::~karakaxa()
{
      views::cleanUp();
      core::cleanUp();
      database::cleanup();
      audioFiles::cleanUp();
}
