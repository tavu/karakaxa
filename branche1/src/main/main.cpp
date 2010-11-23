#include"mainwindow.h"

#include<player.h>

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include <unistd.h>

QObject keef;
using namespace player;

#define VERSION "0.5"

int main(int argc, char *argv[])
{
//      QSqlDatabase p=player::db.getDatabase();



//      app.setApplicationName("Media Player");


    KAboutData aboutData("player",NULL,ki18n("player"),VERSION);
//ki18n("A new music player"),KLocalizedString(),KAboutData::License_GPL


    KCmdLineArgs::init( argc, argv, &aboutData );
//     QApplication app(argc,argv);
    KApplication app;
    app.setApplicationName("player");
    app.setOrganizationName("player");
    mainWindow *pl=new mainWindow();

    pl->show();
    return app.exec();
}


