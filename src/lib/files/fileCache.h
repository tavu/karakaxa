#ifndef FILECACHE_H
#define FILECACHE_H

#include<QString>
#include <QSqlRecord>
#include<QHash>
#include<QMutex>
#include<QReadWriteLock>
#include<QLinkedList>

#include"tagList.h"

#include"fileTags.h"
#include<Basic/filesToDb.h>
namespace database
{
class fileToDb;
}

namespace audioFiles
{

class fileCacheFactory;

class fileCache :public QObject
{

    friend class fileCacheFactory;
    Q_OBJECT
    public:

        QString path()
        {
            return _path;
        }

        int       loadTags ( bool force=false );
        void      setRecord ( QSqlRecord &r, bool force=false );
        int       select ( bool force=false );
        QVariant  tagFromFile ( int t, int &err );
        QVariant  tagFromDb ( int t, int &err );
        QString   coverPath();
        QString   findCoverPath ( int &err );

        int       albumId ( int &err );


        void       setTag ( int t,QVariant var,int &err );
        void       setTagFromFile ( int t,QVariant var );
        void       setTagFromDb ( int t,QVariant var );


        int        prepareToSave();

        QList<tagChanges> savingEnd ( );

        bool exist() ;

    private:
        fileCache ( QString path );
        ~fileCache();
        
        tagRecord *tagTable;
        bool _exist;
        QString _path;

        fileTags *file;
//         database::fileToDb fdb;
        Basic::filesToDb *fdb;

        QMutex loadMutex;
//         QMutex readMutex;
        
        QList<tagChanges> changes;

    signals:
        void changed ( audioFiles::tagChangesL );
//         void removed();
        void doesExist(bool);
//      void moved();



//   signals:
//       void changed(QList<tagChanges>);

};//class

}//namespace

#endif
