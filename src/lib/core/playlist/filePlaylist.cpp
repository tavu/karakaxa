#include"filePlaylist.h"
#include"m3uPlaylist.h"
#include"../func.h"
#include "nowPlayList/nplaylist.h"
#include<libraryFolder.h>
#include"../status/playerStatus.h"
core::filePlaylist* core::getPlaylist(const QString &url)
{
    filePlaylist *ret=0;
    QString tmp=core::format(url);
    if (QString::compare("m3u",tmp,Qt::CaseInsensitive)==0)
    {
        ret=new m3uPlaylist(url);
    }

    return ret;
}

QString core::filePlaylist::toFullPath(const QString &s) const
{
    if (core::isStream(s) )
    {
        return QString(s);
    }

    if (s.startsWith('/') )
    {
        return QString(s);
    }
    QString ret(s);

    return ret.prepend(folder(path() )+'/' );
}

bool core::filePlaylist::create()
{
    if(!createFile() )
    {
        return false;
    }

    database::libraryFolder f;
    KUrl u(path() );
    if(f.onDb(u) )
    {
        f.addPlaylist(u);
    }
    return true;
}

bool core::filePlaylist::createFile()
{
    if ( file.open(  QIODevice::WriteOnly ) )
    {
        file.close();
        return true;
    }
    return false;
}
