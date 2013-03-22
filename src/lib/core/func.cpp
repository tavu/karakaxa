#include"func.h"
#include<QFile>
#include<QTextCodec>
#include"../files/tagsTable.h"
#include<kmimetype.h>
#include"core.h"
#include <kapplication.h>

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include<QFileInfo>
#include<QDir>

#ifdef USE_LAST_FM 
	#include<lastFmFunc.h>
#endif

QString core::titleFromPath(const QString &path)
{
    int l,r;
    r=path.lastIndexOf('.');
    l=path.lastIndexOf('/');

    return path.mid(l+1,r-l-1);
}

QString core::format(QString path)
{

    path=path.mid(path.lastIndexOf('.')+1 );
    return path;
}

QString core::folder(QString path)
{
    if(path.isEmpty() )
    {
        return QString();
    }
    return path.left(path.lastIndexOf('/') );
}

bool core::isStream(const QString s)
{
    return isStream(QUrl(s) );
}

bool core::isStream(const QUrl url)
{
    if (url.scheme() == "http" || url.scheme() == "mms" || url.scheme() == "smb" )
    {
        return true;
    }
    return false;
}

bool core::isAudio(const QString &url)
{     
    if(isPlaylist(url) )
    {
	   return false;
    }
    
    KMimeType::Ptr type = KMimeType::findByUrl(url );
    QStringList l=config->files();    
    
    if (l.contains(type->name() ) )
    {
        return true;
    }
    return false;
}

bool core::isImage(const QString &url)
{
    QString s=core::format(url);
    
    s=s.toUpper();    
    if(config->imagefiles().contains(s) )
    {
        return true;
    }
    
    return false;
}

bool core::isDirectory(const QString &url)
{
    KMimeType::Ptr type = KMimeType::findByUrl(url );

    if (type->name() == "inode/directory")
    {
        return true;
    }
    return false;
}

bool core::isPlaylist(const QString &url)
{
    QString tmp=format(url);
    QStringList l=config->playListFiles();
    if (l.contains(tmp,Qt::CaseInsensitive) )
    {
        return true;
    }
    return false;
}




bool core::exists(const QString &url)
{
    QFile f(url);
    return f.exists();
}

void core::init()
{
    static bool flag=true;
    
    if(flag)
    {
      QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
      QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
        
//       nplaylist *l=const_cast<nplaylist*>(npList);
      qInstallMsgHandler(karakaxaMsg);
      mainThr();
      
      
      qRegisterMetaType<audioFiles::audioFile>("audioFile");
      qRegisterMetaType<QVector<audioFiles::audioFile> >("QVector<audioFiles::audioFile>");
      qRegisterMetaType<QVector<audioFiles::audioFile> >("QVector<audioFile>");
      qRegisterMetaType<audioFiles::audioFile>("audioFiles::audioFile");
      
      status=new playetStatus();
      config =new PlayerConfigure();
      soundEngine::init();
      nplaylist::init();
      contentHdl=new contentHandler(qApp );
      
#ifdef USE_LAST_FM
	  lastFm::init();
#endif
      
      flag=false;            
    }
//       engine.init();
}

void core::cleanUp()
{
//     contentHdl->clear();
    delete status;    
    nplaylist::cleanUp();
    soundEngine::cleanUp();
//     delete db;
    delete config;
    delete contentHdl;
    
}


int core::getRandomN(int min,int max)
{
    return  qrand()/ (RAND_MAX + 1.0) * (max + 1 - min) + min ;
}

QThread* core::mainThr()
{
    static QThread *t=QThread::currentThread();
    
    return t;
}

void core::karakaxaMsg(QtMsgType type, const char *msg)
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

QWidget* core::spacerWidget(QWidget* parent)
{
    QWidget* spacer = new QWidget(parent);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	return spacer;
}

bool core::removeDir(const QString &dirName)
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