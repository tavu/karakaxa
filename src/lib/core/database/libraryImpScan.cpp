#include"libraryImpScan.h"
#include "../status/playerStatus.h"
#include"QSqlQuery"
#include"QSqlError"

void core::libraryImpScan::createTmpTable()
{
    QSqlQuery q(database);
    q.exec("CREATE  TABLE tracksTmp     LIKE tracks");
    q.exec("CREATE  TABLE genresTmp     LIKE genres");
    q.exec("CREATE  TABLE artistsTmp    LIKE artists");
    q.exec("CREATE  TABLE albumsTmp     LIKE albums");
    q.exec("CREATE  TABLE composersTmp  LIKE composers");
    q.exec("CREATE  TABLE playlistsTmp  LIKE playlists");  
}

core::libraryImpScan::libraryImpScan(QObject* parent)
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

void core::libraryImpScan::save()
{
    status->addInfoP("Saving new data");    

    QSqlQuery q(database);

    q.exec("delete  from tracks");
    q.exec("delete  from genres");
    q.exec("delete  from albums");
    q.exec("delete  from artists");
    q.exec("delete  from composers");
    q.exec("delete  from playlists");

    if(!q.exec("INSERT INTO artists select * from artistsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO genres select * from genresTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO albums select * from albumsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO composers select * from composersTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO tracks select * from tracksTmp"))
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("INSERT INTO playlists select * from playlistsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }

    if(!q.exec("drop table artistsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("drop table genresTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("drop table albumsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("drop table composersTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("drop table tracksTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
    if(!q.exec("drop table playlistsTmp") )
    {
        status->addErrorP(q.lastError().text() );
    }
}