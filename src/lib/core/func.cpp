#include"func.h"
#include<QFile>
#include<QTextCodec>
#include"../files/tagsTable.h"
// #include"coreNamespace.h"
#include<kmimetype.h>
#include"core.h"

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
      
      status=new playetStatus();
      config =new PlayerConfigure();
      db=new database();
      db->createConnection();
      engine =new soundEngine();
      npList=new nplaylist();
      contentHdl=new contentHandler();
//       l =new nplaylist();
      flag=false;            
    }
//       engine.init();
}

void core::cleanUp()
{    
    delete npList;
    delete engine;
    delete db;
    delete config;
    delete status;
    delete contentHdl;
    
}


int core::getRandomN(int min,int max)
{
    return  qrand()/ (RAND_MAX + 1.0) * (max + 1 - min) + min ;
}
/*
template <class RandomAccessIterator>
void core::randomShuffle ( RandomAccessIterator first, int size ) 
{
      RandomAccessIterator it,tmp;
      it=first;
      for(int i=0;i<size;i++)
      {	  	  
	  int r=getRandomN(0,size-1);
	  tmp=first+r;
 	  qSwap(*it,*tmp );
	  it++;
      }
	
} 
*/