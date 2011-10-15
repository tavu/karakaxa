#ifndef FILECACHE_H
#define FILECACHE_H
#include<QString>
#include <QSqlRecord>
#include<QHash>
#include<QMutex>
#include<QReadWriteLock>
#include"fileTags.h"
#include"audioFiles.h"
#include<QSharedMemory>
#include<fileToDb.h>
// #include<player.h>

namespace audioFiles
{


//   using namespace audioFiles;
  
class fileCache
{
    
  struct fileCacheS
  {
    fileCache *p;
    int used;
  };
  
  
  public:
      
      inline QString path()
      {
	  return _path;
      }
      
      int 		loadTags(bool force=false);
      void 		setRecord(QSqlRecord &r, bool force=false);
      int 		select(bool force=false);
      QVariant 	tagFromFile(tagsEnum t, int &err);
      QVariant 	tagFromDb(int t, int& err);
	  
	 int 		albumId(int &err);
	 
	 
	 void 		setTag(tagsEnum t,QVariant var,int &err);
      void 		setTagFromFile(tagsEnum t,QVariant var);
	 void 		setTagFromDb(tagsEnum t,QVariant var);
	 	 
	 
	 int 		prepareToSave();
	 
      void 		savingEnd();
      
  private:
      fileCache(QString path);
      ~fileCache();
      tagRecord *tagTable;
      QSqlRecord record; 
      bool notInDb;
      bool tagsFlag;
      QString _path;   
      
	 fileTags *file;
	 fileToDb *fdb;
      
	 QReadWriteLock lock;
      
//       voidplayer::fileTags();
      
      
  public:
      static fileCache* 	getFileCache(QString path);
      static void		releaseFileCache(fileCache*);
      static void	 	releaseFileCache(QString path);
      
  private:
      static QHash<QString, fileCacheS*> fileCacheMap;
      static QMutex gMutex;
      QMutex loadMutex;

//   signals:
//       void changed(QList<tagChanges>);
      
};

}

#endif