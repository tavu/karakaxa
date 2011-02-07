#include"m3u.h"
#include<QTextStream>
#include<player.h>
#include<QTextStream>
player::m3uPl::m3uPl(const QString s)
        :file(s)
{
    path=s;
}

QList<audioFile*> player::m3uPl::files()
{
    QList<audioFile*> audioL;
    for(int i=0;i<list.size();i++)
    {
	audioFile *f=audioFile::getAudioFile(list.at(i) );
	if(f!=0 && f->isValid() )
	{
	    audioL<<f;
	}	
    }
    return audioL;
}


void player::m3uPl::load()
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug()<<"file does not exist";
        error=QObject::tr("file does not exist");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (! line.startsWith('#') )
        {
            toLocal(line);
            list.append(line);
        }
    }
    file.close();
}

void player::m3uPl::toLocal(QString &s)
{
    if (player::isStream(s) )
    {
        return ;
    }

    if (s.startsWith('/') )
    {
        return ;
    }

    s.prepend(folder()+'/' );
}

QList<QString> player::m3uPl::urls() const
{
    return list;
}

QString player::m3uPl::getError() const
{
    return error;
}

void m3uPl::save()
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        error=QObject::tr("file does not exist");
        return;
    }
    QTextStream t( &file );
    QString f=folder();

    foreach(QString s,list)
    {
        if (s.startsWith(f) )
        {
            s.replace(0,f.size(),QString() );
        }
        t<<s<<endl;
    }
    file.close();
}



