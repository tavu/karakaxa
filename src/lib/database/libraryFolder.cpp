#include"libraryFolder.h"
#include"database.h"
#include<Basic/status.h>
#include "dbFunc.h"
#include"databaseEvent.h"
#include <QDir>

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

    dbEventP e(new dbEvent(LF_REM) );
    e->urls<<s;
    db()->emitEvent(e);
    
}

bool database::libraryFolder::onDb(const KUrl& u)
{
    if(list.isEmpty() )
    {
        libraryFolders();
    }
    
    foreach(QString s,list)
    {
        KUrl url(s);
        if(url.isParentOf(u) )
        {
            
            return true;
        }
    }
    return false;
}


bool database::libraryFolder::addLibraryFolder(const QString &s)
{
    databs=db()->getDatabase();

    KUrl newU(s);

    if(onDb(newU) )
    {
        db()->closeDatabase(databs);
        Basic::msg()->info(tr("Some library folders have been merged") );
        return false;
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

    dbEventP e(new dbEvent(NEW_LF) );
    e->urls<<s;
    db()->emitEvent(e);

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

    dbEventP e(new dbEvent(FILES_REM) );
    e->urls<<path;
    db()->emitEvent(e);
    
    return b;
}

bool database::libraryFolder::removeFiles(const QStringList paths)
{
    bool b;
    databs=db()->getDatabase();
	dbEventP e(new dbEvent(FILES_REM) );
	dbEventP folE(new dbEvent(FILES_REM) );
    {
		foreach(QString path,paths)
		{
			QSqlQuery q(databs);
			QDir d(path);
			if(d.exists() )
			{
				QString p=path;
				if(!p.endsWith ('/') )
				{
					p.append('/');        
				}
				toSqlSafe(p);
				p.append('%');
				
				q.prepare("delete from tracks where path like "+p);
				if(q.exec())
				{					
					e->urls<<path;
				}
			}
			else
			{
				q.prepare("delete from tracks where path=?");
				q.addBindValue(path);
				b=q.exec();
				if(b)
				{
					e->urls<<path;
				}
			}
		}
    }
    cleanUp();
    db()->closeDatabase(databs);
	if(e->urls.size()!=0)
	{
		db()->emitEvent(e);	
	}
	if(folE->urls.size()!=0)
	{
		db()->emitEvent(folE);
	}
    
    return true;

}


bool database::libraryFolder::removeFolder(QString p)
{
	QString path=p;
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

    dbEventP e(new dbEvent(FILES_REM) );
    e->urls<<p;
    e->setProperty("folder",QVariant(true) );
    db()->emitEvent(e);

    return true;    
}

bool database::libraryFolder::addPlaylist(const QString& path)
{
    databs=db()->getDatabase();
    bool ret;
    {
        QSqlQuery q(databs );
        q.prepare("insert into playlists(path) values(?)");
        q.addBindValue(path);
        ret=q.exec();

        if(!ret)
        {
            Basic::msg()->logErr(q.lastError().text() );
        }
    }



    if(ret && !plList.isEmpty())
    {
        plList<<path;
    }

    db()->closeDatabase(databs);

    dbEventP e(new dbEvent(NEW_PL) );
    e->urls<<path;
    db()->emitEvent(e);
    
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

    dbEventP e(new dbEvent(PL_REM) );
    e->urls<<path;
    db()->emitEvent(e);
    
    return b;
}

QStringList database::libraryFolder::list=QStringList();
QStringList database::libraryFolder::plList=QStringList();