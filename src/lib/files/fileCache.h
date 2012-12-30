#ifndef FILECACHE_H
#define FILECACHE_H
#include<QString>
#include <QSqlRecord>
#include<QHash>
#include<QMutex>
#include<QReadWriteLock>
#include<QLinkedList>

#include<fileToDb.h>

#include"fileTags.h"
// #include"audioFiles.h"

// #include<database.h>
namespace database
{
    class fileToDb;
}

namespace audioFiles
{


//   using namespace audioFiles;
  
class fileCache :public QObject
{

  struct fileCacheS
  {
    fileCache *p;
    int used;
  };
  
  Q_OBJECT
  public:

      QString path()
      {
        return _path;
      }

      int 		loadTags(bool force=false);
      void 		setRecord(QSqlRecord &r, bool force=false);
      int 		select(bool force=false);
      QVariant 	tagFromFile(tagsEnum t, int &err);
      QVariant 	tagFromDb(int t, int& err);
      QString   coverPath();
      QString   findCoverPath(int& err);

      int 		albumId(int &err);


	 void 		setTag(tagsEnum t,QVariant var,int &err);
     void 		setTagFromFile(tagsEnum t,QVariant var);
	 void 		setTagFromDb(tagsEnum t,QVariant var);


	 int 		prepareToSave();

     void 		savingEnd(QList<tagChanges>);
	 
	 bool 		exist() ;	 

  private:
      fileCache(QString path);
      ~fileCache();
      tagRecord *tagTable;
      QSqlRecord record;
      bool notInDb;
	  bool _exist;
      QString _path;

	 fileTags *file;
	 database::fileToDb *fdb;

     QString _coverPath;
 	 QMutex loadMutex;
 	 QMutex readMutex;
//      QReadWriteLock rwLock;

  public:
      static fileCache* 	getFileCache(QString path);
	  static QLinkedList<fileCache*> 	getAllCache();
      static void		    releaseFileCache(fileCache*);
      static void	 	    releaseFileCache(QString path);

  private:
      static QHash<QString, fileCacheS*> fileCacheMap;
      static QMutex gMutex;


    signals:
        void changed(audioFiles::tagChangesL);
		void removed();
// 		void moved();
      


//   signals:
//       void changed(QList<tagChanges>);

};//class

void checkAudioFilesExist();
	
}//namespace

#endif