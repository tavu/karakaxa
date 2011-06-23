#include"abstractPlaylist.h"
#include"m3uPlaylist.h"
#include"../func.h"
core::abstractPlaylist* core::getPlaylist(const QString &url)
{
    abstractPlaylist *ret=0;
    QString tmp=core::format(url);
    if (QString::compare("m3u",tmp,Qt::CaseInsensitive)==0)
    {
	 ret=new m3uPlaylist(url);
    }
    
    return ret;
}

void core::abstractPlaylist::toFullPath(QString &s)
{
    if (core::isStream(s) )
    {
        return ;
    }

    if (s.startsWith('/') )
    {
        return ;
    }

    s.prepend(folder(path() )+'/' );
}
