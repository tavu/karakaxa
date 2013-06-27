#include"libraryImpScan.h"

#include<QSqlQuery>
#include<QSqlError>

#include<Basic/status.h>


void database::libraryImpScan::createTmpTable()
{
    QSqlQuery q(database);
    q.exec("CREATE  TABLE tracksTmp     LIKE tracks");
    q.exec("CREATE  TABLE genresTmp     LIKE genres");
    q.exec("CREATE  TABLE artistsTmp    LIKE artists");
    q.exec("CREATE  TABLE albumsTmp     LIKE albums");
    q.exec("CREATE  TABLE composersTmp  LIKE composers");
    q.exec("CREATE  TABLE playlistsTmp  LIKE playlists");  
}

database::libraryImpScan::libraryImpScan(QObject* parent)
    :libraryImporter(parent)
{
    albumTable = QString("albumsTmp");
    trackTable = QString("tracksTmp");
    artistTable = QString ("artistsTmp");
    genreTable = QString ("genresTmp");
    composerTable = QString("composersTmp");
    playlistTable = QString("playlistsTmp");
    createTmpTable();
}

void database::libraryImpScan::save()
{
    Basic::msg()->logInfo("Saving new data");

    QSqlQuery q(database);

    q.exec("delete  from tracks");
    q.exec("delete  from genres");
    q.exec("delete  from albums");
    q.exec("delete  from artists");
    q.exec("delete  from composers");
    q.exec("delete  from playlists");

    if(!q.exec("INSERT INTO artists select * from artistsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO genres select * from genresTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO albums select * from albumsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO composers select * from composersTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO tracks select * from tracksTmp"))
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO playlists select * from playlistsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }

    if(!q.exec("drop table artistsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("drop table genresTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("drop table albumsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("drop table composersTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("drop table tracksTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
    if(!q.exec("drop table playlistsTmp") )
    {
        Basic::msg()->logErr(q.lastError().text() );
    }
}