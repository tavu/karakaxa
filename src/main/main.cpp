#include <QApplication>
#include"mainwindow.h"

#include<player.h>

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include <unistd.h>

QObject keef;
using namespace player;
int main(int argc, char *argv[])
{
//      QSqlDatabase p=player::db.getDatabase();



//      app.setApplicationName("Media Player");


    KAboutData aboutData(
        // The program name used internally.
        "tutorial1",
        // The message catalog name
        // If null, program name is used instead.
        0,
        // A displayable program name string.
        ki18n("Tutorial 1"),
        // The program version string.
        "1.0",
        // Short description of what the app does.
        ki18n("Displays a KMessageBox popup"),
        // The license this code is released under
        KAboutData::License_GPL,
        // Copyright Statement
        ki18n("(c) 2007"),
        // Optional text shown in the About box.
        // Can contain any information desired.
        ki18n("Some text..."),
        // The program homepage string.
        "http://example.com/",
        // The bug report email address
        "submit@bugs.kde.org"
    );




    KCmdLineArgs::init( argc, argv, &aboutData );
    QApplication app(argc,argv);

    mainWindow *pl=new mainWindow();

    pl->show();
    return app.exec();
}


