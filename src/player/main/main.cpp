#include"mainwindow.h"

#define KARAKAXA "karakaxa"
#include "application.h"
#include <KAboutData>
#include <KCmdLineArgs>
#include <unistd.h>

int main(int argc, char *argv[])
{
    KAboutData aboutData(KARAKAXA,NULL,ki18n(KARAKAXA),VERSION);
    aboutData.setLicense(KAboutData::License_GPL_V3);
    aboutData.addAuthor(ki18n("Ταβουλάρης Νίκος (tavu)"),ki18n("Developer"),"nik.tavu@gmail.com");

    KCmdLineArgs::init( argc, argv, &aboutData );
    karakaxa app(argc,argv);
    mainWindow *pl=new mainWindow();
    
    pl->show();
    int ret=app.exec();
    delete pl;
    
    return ret;
}


