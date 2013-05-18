#include"func.h"
#include<QFile>
#include<QTextCodec>
#include<kmimetype.h>
#include <kapplication.h>

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include<QFileInfo>
#include<QDir>

#include"configure.h"


QString Basic::titleFromPath(const QString &path)
{
    int l,r;
    r=path.lastIndexOf('.');
    l=path.lastIndexOf('/');

    return path.mid(l+1,r-l-1);
}

QString Basic::format(QString path)
{

    path=path.mid(path.lastIndexOf('.')+1 );
    return path;
}

QString Basic::folder(QString path)
{
    if(path.isEmpty() )
    {
        return QString();
    }
    return path.left(path.lastIndexOf('/') );
}

bool Basic::isStream(const QString s)
{
    return isStream(QUrl(s) );
}

bool Basic::isStream(const QUrl url)
{
    if (url.scheme() == "http" || url.scheme() == "mms" || url.scheme() == "smb" )
    {
        return true;
    }
    return false;
}

bool Basic::isAudio(const QString &url)
{     
    if(isPlaylist(url) )
    {
	   return false;
    }
    
    KMimeType::Ptr type = KMimeType::findByUrl(url );
    QStringList l=configure::files();    
    
    if (l.contains(type->name() ) )
    {
        return true;
    }
    return false;
}

bool Basic::isImage(const QString &url)
{
    QString s=Basic::format(url);
    
    s=s.toUpper();    
    if(configure::imagefiles().contains(s) )
    {
        return true;
    }
    
    return false;
}

bool Basic::isDirectory(const QString &url)
{
    KMimeType::Ptr type = KMimeType::findByUrl(url );

    if (type->name() == "inode/directory")
    {
        return true;
    }
    return false;
}

bool Basic::isPlaylist(const QString &url)
{
    QString tmp=format(url);
    QStringList l=configure::playListFiles();
    if (l.contains(tmp,Qt::CaseInsensitive) )
    {
        return true;
    }
    return false;
}

bool Basic::exists(const QString &url)
{
    QFile f(url);
    return f.exists();
}

void Basic::init()
{
    static bool flag=true;
    
    if(flag)
    {
      QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
      QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
        
      qInstallMsgHandler(karakaxaMsg);
      
      flag=false;            
    }
}

int Basic::getRandomN(int min,int max)
{
    return  qrand()/ (RAND_MAX + 1.0) * (max + 1 - min) + min ;
}

void Basic::karakaxaMsg(QtMsgType type, const char *msg)
{
     switch (type) 
	 {
		case QtDebugMsg:
#ifdef DEBUG			
			fprintf(stderr, "Debug: %s\n", msg);
#endif			
			break;
		case QtWarningMsg:
			fprintf(stderr, "Warning: %s\n", msg);
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s\n", msg);
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal: %s\n", msg);
			abort();
     }
}

bool Basic::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);
 
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
 
            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
 
    return result;
}