#include"m3uPlaylist.h"
#include<QTextStream>
#include"../core.h"
#include<QTextStream>
using namespace audioFiles;
core::m3uPlaylist::m3uPlaylist(const QString s,QObject *parent)
        :filePlaylist(parent),file(s)
{
    _path=s;
}

bool core::m3uPlaylist::load()
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug()<<"file does not exist";
        err=FILENOTFOUND;
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd() )
    {
        QString line = in.readLine();

        if (! line.startsWith('#') )
        {
            list.append(line);
            nplPointer p=nplTrack::getNplTrack(toFullPath(line) );    
            trackList.append(p);
        }
    }
    file.close();
    
    return true;
}


QStringList core::m3uPlaylist::urls() const
{
    QStringList l;
    for(int i=0;i<list.size();i++)
    {
        QString s=toFullPath( list[i]);
        l.append(s);
    }
    return l;
}

int core::m3uPlaylist::error() const
{
    return err;
}

bool core::m3uPlaylist::save()
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        err=FILENOTFOUND;
        return false;
    }
    
    QTextStream t( &file );
    QString f=core::folder(_path);
            
    foreach(QString s,list)
    {
        if (saveToRelativePath() && s.startsWith(f) )
        {
            s.replace(0,f.size(),QString() );
        }
        t<<s<<endl;
    }

    
    file.close();
    
    return true;
}


void core::m3uPlaylist::insertUrl(int pos,QString u)
{
    nplPointer p=nplTrack::getNplTrack(u);
    insert(pos,p);
}

void core::m3uPlaylist::insert(int pos, core::nplPointer p)
{
    if (pos>list.size() ||pos<0)
        pos=trackList.size();
    
    list.insert(pos,p->path());
    filePlaylist::insert(pos,p);
}


void core::m3uPlaylist::move( int from, int to )
{
    if (from>=list.size() ||  to>=list.size())
    {
        return ;	
    }
    else
    {	
      list.move(from,to);
      filePlaylist::move(from,to);
    }	
}

void core::m3uPlaylist::remove(int pos)
{
  if (pos>=list.size() )
  {
    return ;	
  }

  list.removeAt(pos);
  filePlaylist::remove(pos);
}
