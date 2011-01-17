#ifndef PLAYERCONFIGURE_H
#define PLAYERCONFIGURE_H

#include<QStringList>
#include<QMutex>
#include<KSharedConfigPtr>
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
      QString saveLocation( const QString &directory = QString() );
      KSharedConfigPtr configFile(const QString &s =QString("player.conf") );
      
  private:
      QStringList supportesFilesList;
      QStringList supportedImageFiles;
      
      QMutex globalDirsMutex;

// 	  QSettings settings;
};

}
#endif
