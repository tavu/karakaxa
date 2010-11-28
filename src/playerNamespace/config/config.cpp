#include"config.h"
#include<phonon>
player::PlayerConfigure::PlayerConfigure()
{
//      supportesFilesList<<"*.mp3";

//      supportesFilesList= Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive );
//      supportesFilesList<< "audio/x-m4b"<<"*.mp3";

    supportedImageFiles<<"*.BMP"<<"*.GIF"<<"*.JPG"<<"*.JPEG"<<"*.PNG"<<"*.PBM"<<"*.PGM"<<"*.PPM"<<"*.TIFF"<<"*.XBM"<<"*.XPM";
}

QStringList player::PlayerConfigure::files()
{
    return  Phonon::BackendCapabilities::availableMimeTypes().filter( "audio/", Qt::CaseInsensitive )<<"*.mp3";
}

QStringList player::PlayerConfigure::playListFiles()
{
    QStringList l;
    return l<<"*.m3u";
}

QStringList player::PlayerConfigure::imagefiles()
{
    return supportedImageFiles;
}
