#include"mainwindow.h"

// #include<player.h>
#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include <unistd.h>
#define VERSION "0.5"

int main(int argc, char *argv[])
{
    KAboutData aboutData("player",NULL,ki18n("player"),VERSION);
//ki18n("A new music player"),KLocalizedString(),KAboutData::License_GPL
    aboutData.setLicense(KAboutData::License_GPL_V3);
    
    aboutData.addAuthor(ki18n("Ταβουλάρης Νίκος (tavu)"),ki18n("Developer"),"nik.tavu@gmail.com");

    KCmdLineArgs::init( argc, argv, &aboutData );
//     QApplication app(argc,argv);
    KApplication app;
    app.setApplicationName("player");
    app.setOrganizationName("player");
    mainWindow *pl=new mainWindow();
    
    pl->show();

    
    int ret=app.exec();
//     sleep(5);
    core::cleanUp();
    return ret;
}


