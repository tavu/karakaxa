#include"config.h"
#include<phonon/BackendCapabilities>
// #include<KGlobal>
#include<kstandarddirs.h>
#include<KSharedConfig>
#include <KMenuBar>

core::PlayerConfigure::PlayerConfigure()
{
//      supportesFilesList<<"*.mp3";

//      supportesFilesList= Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive );
//      supportesFilesList<< "audio/x-m4b"<<"*.mp3";

//     supportedImageFiles<<"BMP"<<"GIF"<<"JPG"<<"JPEG"<<"PNG"<<"PBM"<<"PGM"<<"PPM"<<"TIFF"<<"XBM"<<"XPM";
}

core::PlayerConfigure::~PlayerConfigure()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "Config" );
    group.writeEntry("menuBarShown", QVariant(_isMenuBarShown ) );
    group.config()->sync();
}


void core::PlayerConfigure::readSetings()
{
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "Config" );
    bool b=group.readEntry("menuBarShown",false );
    showMenuBar(b);
}


QStringList core::PlayerConfigure::files()
{
    return  Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive );
}

QStringList core::PlayerConfigure::playListFiles()
{
    QStringList l;
    return l<<QString("m3u");
}

void core::PlayerConfigure::showMenuBar(bool b)
{
    _isMenuBarShown=b;
    if(b)
    {
        mainWin->menuBar()->show();
    }
    else
    {
        mainWin->menuBar()->hide();
    }
}


QStringList core::PlayerConfigure::imagefiles()
{
    static QStringList supportedImageFiles;
    
    if(supportedImageFiles.isEmpty() )
    {
    	supportedImageFiles<<"BMP"<<"GIF"<<"JPG"<<"JPEG"<<"PNG"<<"PBM"<<"PGM"<<"PPM"<<"TIFF"<<"XBM"<<"XPM";
    }
    
    return supportedImageFiles;
}

    
QString core::PlayerConfigure::saveLocation( const QString &directory )
{
  globalDirsMutex.lock();    
  QString result = KGlobal::dirs()->saveLocation( "data", QString("karakaxa/") + directory, true );
  globalDirsMutex.unlock();  
  return result;    
}

KSharedConfigPtr core::PlayerConfigure::configFile(const QString& s,const QString &directory)
{
    return KSharedConfig::openConfig(saveLocation(directory)+s);
}


// QStringList core::PlayerConfigure::supportesFilesList;
// QStringList core::PlayerConfigure::supportedImageFiles;
QMutex core::PlayerConfigure::globalDirsMutex;

namespace core
{
  PlayerConfigure *config;
}
