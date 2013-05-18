#ifndef PLAYERCONFIGURE_H
#define PLAYERCONFIGURE_H

#include<QStringList>
#include<QMutex>
#include<ksharedconfig.h>
#include<QSettings>
#include<KConfigGroup>
#include <KMainWindow>

namespace core
{

class PlayerConfigure
{
  public:
      PlayerConfigure();
      ~PlayerConfigure();
      static QStringList files();
      static QStringList imagefiles();
      static QStringList playListFiles();
      static QString saveLocation( const QString &directory = QString() );
      static KSharedConfigPtr configFile(const QString &s =QString("karakaxa.conf"),const QString &directory=QString() );
  
      void setMainWindow(KMainWindow *w)
      {
          mainWin=w;
      }
      
      KMainWindow* mainWindow()
      {
          return mainWin;
      }
      
      void showMenuBar(bool b);
      bool menuBarShown()
      {
          return _isMenuBarShown;
      }
      void readSetings();
  private:
//       static QStringList supportesFilesList;
//       static QStringList supportedImageFiles;
      KMainWindow *mainWin;
      static QMutex globalDirsMutex;
      bool _isMenuBarShown;

// 	  QSettings settings;
};

    extern PlayerConfigure *config;

}
#endif
