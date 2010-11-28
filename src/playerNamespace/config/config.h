#ifndef PLAYERCONFIGURE_H
#define PLAYERCONFIGURE_H

#include<QStringList>
#include<QSettings>
namespace player
{

class PlayerConfigure
{
public:
    PlayerConfigure();
    QStringList files();
    QStringList imagefiles();
    QStringList playListFiles();
private:
    QStringList supportesFilesList;
    QStringList supportedImageFiles;

// 	  QSettings settings;
};

}
#endif
