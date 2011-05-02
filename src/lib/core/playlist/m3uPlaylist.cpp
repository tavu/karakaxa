#include"m3uPlaylist.h"
#include<QTextStream>
#include"../core.h"
#include<QTextStream>
using namespace audioFiles;
core::m3uPlaylist::m3uPlaylist(const QString s)
        :file(s)
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
            toFullPath(line);
            list.append(line);
        }
    }
    file.close();
    
    return true;
}

void core::m3uPlaylist::toFullPath(QString &s)
{
    if (core::isStream(s) )
    {
        return ;
    }

    if (s.startsWith('/') )
    {
        return ;
    }

    s.prepend(folder(_path)+'/' );
}

QStringList core::m3uPlaylist::urls() const
{
    return list;
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
        if (s.startsWith(f) )
        {
            s.replace(0,f.size(),QString() );
        }
        t<<s<<endl;
    }
    file.close();
    
    return true;
}

int core::m3uPlaylist::size() const
{
    return list.size();
}

QString core::m3uPlaylist::item(int pos) const
{
    if (pos>=list.size() )
    {
      return QString();	  
    }
    else
    {
      return list.at(pos);	
    }
}	


void core::m3uPlaylist::insert(int pos,QString u)
{
    if (pos>=list.size() )
    {
	list.prepend(u);	
    }
    else
    {	
      list.insert(pos,u);
    }
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
    }	
}

void core::m3uPlaylist::remove(int pos)
{
  if (pos>=list.size() )
  {
    return ;	
  }

  list.removeAt(pos);
}
