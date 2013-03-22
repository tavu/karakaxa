#ifndef PLAYERCONFIGURE_H
#define PLAYERCONFIGURE_H

#include<QStringList>
#include<QMutex>
#include<ksharedconfig.h>
#include<QSettings>
#include<KConfigGroup>

namespace core
{

class PlayerConfigure
{
  public:
      PlayerConfigure();
      static QStringList files();
      static QStringList imagefiles();
      static QStringList playListFiles();
      static QString saveLocation( const QString &directory = QString() );
      static KSharedConfigPtr configFile(const QString &s =QString("karakaxa.conf"),const QString &directory=QString() );
	 
  private:
//       static QStringList supportesFilesList;
//       static QStringList supportedImageFiles;
      
      static QMutex globalDirsMutex;

// 	  QSettings settings;
};

    extern PlayerConfigure *config;

}
#endif
