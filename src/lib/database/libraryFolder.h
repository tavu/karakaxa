#ifndef LIBRARYFOLDER_H
#define LIBRARYFOLDER_H

#include"dbBase.h"
#include<QStringList>
#include<KUrl>
namespace database
{

class libraryFolder :public dbBase
{
    public:
        libraryFolder(QObject *parent=0);
        ~libraryFolder(){}
        QStringList libraryFolders();        
        void removeLibraryFolder(const QString &s);
        bool addLibraryFolder(const QString &s);

        QStringList playLists();
        bool addPlaylist(const QString &path);
        bool addPlaylist(const QUrl u)
        {
            QString s=u.toLocalFile();
            return addPlaylist(s);
        }
        bool removePlaylist(const QString &path);
        
        bool removeFile(const QString &path);
		bool removeFiles(const QStringList paths);
        bool removeFolder( QString p);

        bool onDb(const KUrl &u);
        
    private:
        static QStringList list;
        static QStringList plList;
};

};
#endif
