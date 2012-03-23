#include"libraryFolder.h"
#include"database.h"
#include<status/playerStatus.h>
#include "dbFunc.h"
database::libraryFolder::libraryFolder(QObject *parent):dbBase(parent)
{}

QStringList database::libraryFolder::libraryFolders()
{
    if(!list.isEmpty() )
    {
        return list;        
    }
    databs=db()->getDatabase();

    {
        QSqlQuery q("select path from library_folders",databs);
        q.exec();

        while (q.next() )
        {
            list<<q.value(0).toString();
        }        
    }
    db()->closeDatabase(databs);
    return list;
}

void database::libraryFolder::removeLibraryFolder(const QString &s)
{
    databs=db()->getDatabase();
    {
        QSqlQuery q(databs);
        q.prepare("delete from library_folders where path=?");
        q.addBindValue(s);
        q.exec();
    }
    db()->closeDatabase(databs);
    list.clear();
}

bool database::libraryFolder::addLibraryFolder(const QString &s)
{
    databs=db()->getDatabase();
    if(list.isEmpty() )
    {
        libraryFolder();
    }
    KUrl newU(s);
    foreach(QString s,list)    
    {
        KUrl u(s);
        if(u.isParentOf(newU) )
        {
            //we do not need to add the newU as library folder
            db()->closeDatabase(databs);
            core::status->addInfo(tr("Some library folders have been merged") );
            return false;
        }
    }

    bool ret;
    {
        QSqlQuery q(databs );
        q.prepare("insert into library_folders(path) values(?)");
        q.addBindValue(s);
        ret=q.exec();
    }

    if(ret)
    {
        list<<s;
    }

    db()->closeDatabase(databs);
    return ret;
}


QStringList database::libraryFolder::playLists()
{
    if(!plList.isEmpty() )
    {
        return plList;
    }
    databs=db()->getDatabase();

    {
        QSqlQuery q("select * from playlists",databs);
        q.exec();

        while (q.next() )
        {
            plList<<q.value(0).toString();
        }
    }
    db()->closeDatabase(databs);
    return plList;    
}

bool database::libraryFolder::removeFile(const QString& path)
{
    bool b;
    databs=db()->getDatabase();
    {
        QSqlQuery q(databs);
        q.prepare("delete from tracks where path=?");
        q.addBindValue(path);
        b=q.exec();
    }
    cleanUp();
    db()->closeDatabase(databs);
    return b;
}

bool database::libraryFolder::removeFolder(QString path)
{
    if(!path.endsWith ('/') )
    {
        path.append('/');        
    }
    
    toSqlSafe(path);
    path.append('%');
    
    databs=db()->getDatabase();
    {
        QSqlQuery q(databs);
        q.prepare("delete from tracks where path like "+path);
        if(!q.exec())
        {
            db()->closeDatabase(databs);
            return false;
        }
        q.prepare("delete from playlists where path like "+path);
        plList.clear();        
    }
    
    cleanUp();
    db()->closeDatabase(databs);

    return true;    
}

bool database::libraryFolder::addPlaylist(const QString& path)
{
    bool ret;
    {
        QSqlQuery q(databs );
        q.prepare("insert into playlists(path) values(?)");
        q.addBindValue(path);
        ret=q.exec();
    }

    if(ret && !plList.isEmpty())
    {
        plList<<path;
    }

    db()->closeDatabase(databs);
    return ret;
}

bool database::libraryFolder::removePlaylist(const QString& path)
{
    bool b;
    databs=db()->getDatabase();
    {
        QSqlQuery q(databs);
        q.prepare("delete from playlists where path=?");
        q.addBindValue(path);
        b=q.exec();
    }
    if(b)
    {
        plList.removeOne(path);
    }
    
    db()->closeDatabase(databs);
    return b;
}
