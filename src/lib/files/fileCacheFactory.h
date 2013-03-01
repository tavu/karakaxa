#ifndef FILE_CHACHE_FACTORY
#define FILE_CHACHE_FACTORY
#include<QString>
#include<QLinkedList>
#include<QMutex>
#include<QHash>
namespace audioFiles
{
class fileCache;

class fileCacheFactory
{
    private:
        struct fileCacheS
        {
            fileCache *p;
            int used;
        };
        
        //disable creating objects
        fileCacheFactory();
        
    

    public:
        static fileCache*  getFileCache ( QString path );
        static QLinkedList<fileCache *>    getAllCache();
        static void           releaseFileCache ( fileCache * );
        static void           releaseFileCache ( QString path );
        
    private:
        static QHash<QString, fileCacheS *> fileCacheMap;
        static QMutex gMutex;
};
void checkAudioFilesExist();
}

#endif
