#include"configure.h"
#include<phonon/BackendCapabilities>
#include<kstandarddirs.h>
#include<KSharedConfig>


/*
Basic::configure::configure()
{
}
*/


QStringList Basic::configure::files()
{
    return  Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive );
}

QStringList Basic::configure::playListFiles()
{
    QStringList l;
    return l<<QString("m3u");
}

QStringList Basic::configure::imagefiles()
{
    static QStringList supportedImageFiles;
    
    if(supportedImageFiles.isEmpty() )
    {
    	supportedImageFiles<<"BMP"<<"GIF"<<"JPG"<<"JPEG"<<"PNG"<<"PBM"<<"PGM"<<"PPM"<<"TIFF"<<"XBM"<<"XPM";
    }
    
    return supportedImageFiles;
}

    
QString Basic::configure::saveLocation( const QString &directory )
{
  globalDirsMutex.lock();    
  QString result = KGlobal::dirs()->saveLocation( "data", QString("karakaxa/") + directory, true );
  globalDirsMutex.unlock();  
  return result;    
}

KSharedConfigPtr Basic::configure::configFile(const QString& s,const QString &directory)
{
    return KSharedConfig::openConfig(saveLocation(directory)+s);
}

QMutex Basic::configure::globalDirsMutex;


