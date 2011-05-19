#include"config.h"
#include<phonon/BackendCapabilities>
// #include<KGlobal>
#include<kstandarddirs.h>
#include<ksharedconfig.h>
core::PlayerConfigure::PlayerConfigure()
{
//      supportesFilesList<<"*.mp3";

//      supportesFilesList= Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive );
//      supportesFilesList<< "audio/x-m4b"<<"*.mp3";

//     supportedImageFiles<<"BMP"<<"GIF"<<"JPG"<<"JPEG"<<"PNG"<<"PBM"<<"PGM"<<"PPM"<<"TIFF"<<"XBM"<<"XPM";
}

QStringList core::PlayerConfigure::files()
{
    return  Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive )<<"*.mp3";
}

QStringList core::PlayerConfigure::playListFiles()
{
    QStringList l;
    return l<<QString("M3U");
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
  QString result = KGlobal::dirs()->saveLocation( "data", QString("player/") + directory, true );
  globalDirsMutex.unlock();  
  return result;    
}

KSharedConfigPtr core::PlayerConfigure::configFile(const QString& s)
{
    return KSharedConfig::openConfig(saveLocation()+s);
}


// QStringList core::PlayerConfigure::supportesFilesList;
// QStringList core::PlayerConfigure::supportedImageFiles;
QMutex core::PlayerConfigure::globalDirsMutex;

namespace core
{
  PlayerConfigure *config;
}