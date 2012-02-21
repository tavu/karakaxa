#include"m3uPlaylist.h"
#include<QTextStream>
#include"../core.h"
#include<QTextStream>
using namespace audioFiles;
core::m3uPlaylist::m3uPlaylist(const QString s,QObject *parent)
        :filePlaylist(s,parent)
{
}

bool core::m3uPlaylist::load()
{
    qDebug()<<"load";
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        status->addErrorP("can not open file "+path() );
        err=FILENOTFOUND;
        return false;
    }
    nplList l;
    QTextStream in(&file);
    while (!in.atEnd() )
    {
        QString line = in.readLine();

        if (! line.startsWith('#') )
        {
            nplPointer p=nplTrack::getNplTrack(toFullPath(line) );
            l.append(p);
        }
    }
    
    file.close();
    insertEv *e=new insertEv(0,l);
    insertEvent(e);
    delete e;
//     insert(0,l);
        
    return true;
}


QStringList core::m3uPlaylist::urls() const
{
    QStringList l;
    for(int i=0;i<trackList.size();i++)
    {
        QString s=toFullPath( trackList[i]->path() );
        l.append(s);
    }
    return l;
}


bool core::m3uPlaylist::save()
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        err=FILENOTFOUND;
        status->addErrorP("file does not exist");
        return false;
    }
    
    QTextStream t( &file );
    QString f=core::folder(_path);
            
    foreach(nplPointer p,trackList)
    {
        QString s=p->path();
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

