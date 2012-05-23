#include"application.h"

#include <KApplication>
#include <unistd.h>

#include<core.h>
#include<views.h>
#include<dbFunc.h>

karakaxa::karakaxa(int argc, char *argv[])
    :KUniqueApplication()
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
