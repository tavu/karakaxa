#include"dbBase.h"
#include<QSqlQuery>
#include<QSqlError>

#include<status/playerStatus.h>
#include"database.h"
void database::dbBase::cleanUp()
{
    clearArtist();
    clearAlbum();
    clearGenre();
    clearComposer();

}


void database::dbBase::clearArtist()
{
     QSqlQuery q(databs );

     q.prepare("delete from artists where artists.id not in (select tracks.lead_artist from tracks) and artists.id not in (select tracks.artist from tracks)");

     if (!q.exec() )
     {
        core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::clearAlbum()
{
     QSqlQuery q(databs );

     q.prepare("delete from albums where albums.id not in (select tracks.album from tracks)");

     if (!q.exec() )
     {
        core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::clearGenre()
{
     QSqlQuery q(databs );

     q.prepare("delete from genres where genres.id not in (select tracks.genre from tracks)");

     if (!q.exec() )
     {
       core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::clearComposer()
{
     QSqlQuery q(databs );

     q.prepare("delete from composers where composers.id not in (select tracks.composer from tracks)");

     if (!q.exec() )
     {
        core::status->addErrorP("setting albumArt error "+q.lastError().text() );
     }
}

void database::dbBase::getDb()
{
	databs=db()->getDatabase();
}
		
void database::dbBase::closeDb()
{
	db()->closeDatabase(databs);
}