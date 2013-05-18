#ifndef PLAYERCONFIGURE_H
#define PLAYERCONFIGURE_H

#include<QStringList>
#include<QMutex>
#include<ksharedconfig.h>
#include<QSettings>
#include<KConfigGroup>

namespace Basic
{

class configure
{
    public:
        static void init();
        
//         PlayerConfigure();
        static QStringList files();
        static QStringList imagefiles();
        static QStringList playListFiles();
        static QString saveLocation ( const QString &directory = QString() );
        static KSharedConfigPtr configFile ( const QString &s =QString ( "karakaxa.conf" ),const QString &directory=QString() );
        
    private:
        static QMutex globalDirsMutex;
};

}
#endif
