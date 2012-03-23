#ifndef LIBRARYFOLDER_H
#define LIBRARYFOLDER_H

#include"dbBase.h"
#include<QStringList>

namespace database
{

class libraryFolder :public dbBase
{
    public:
        libraryFolder(QObject *parent=0);
        QStringList libraryFolders();        
        void removeLibraryFolder(const QString &s);
        bool addLibraryFolder(const QString &s);

        QStringList playLists();
        bool addPlaylist(const QString &path);
        bool removePlaylist(const QString &path);
        
        bool removeFile(const QString &path);
        bool removeFolder( QString path);

    private:
        QStringList list;
        QStringList plList;
};

};
#endif
