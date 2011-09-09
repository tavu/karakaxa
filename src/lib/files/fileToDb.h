#ifndef FILETODB
#define FILETODB

#include"fileTags.h"
#include<QSqlDatabase>
#include<QMutex>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
// #include"../core/database/database.h"
// #include<player.h>
// #include"playerNamespace.h"

// class audioFile;

namespace audioFiles
{

class fileToDb
{
  public:

	fileToDb(QString path);
	~fileToDb();	

	int commit();
	
	int prepare();
	
	void setAlbum(const QString &s)
	{
	    _album=s;
	    qDebug()<<"fdb al "<<_album;
	}
	
	void setArtist(const QString &s)
	{
	    _artist=s;
	}
	
	int setTag(int t,QVariant var);
	
// 	void save();
	static QSqlRecord 	record(const QString path,int &err);
	QString			albumArt(const int albumId,int &err);
	
	void 			cleanUp();
	void 			clearArtist();
	void 			clearAlbum();
	void 			clearGenre();
	void 			clearComposer();
	
    private:
	int 	setTitle (const QString path,const QString &s);
	int 	setArtist (const QString path,const QString &s,const QString &album);
	int 	setAlbum (const QString path,const QString &s);
	int 	setComment (const QString path,const QString &s);
	int 	setLeadArtist (const QString path,const QString &s,const QString &artist,const QString &album);
	int	setComposer(const QString path,const QString &s);
	int 	setGenre (const QString path,const QString &s);
	int 	setYear (const QString path,const unsigned int &year);
	int 	setTrack (const QString path,const unsigned int &i);
	int 	setRating(const QString path,const unsigned int &rating);
	int 	setCounter(const QString path,const unsigned int &num);
	int 	setAlbumArt(const int albumId,QString art);

    
    
	QString	_album;
	QString 	_artist;
	QString 	_path;
	int 		_id;
	int 		_tag;
	QVariant 	value;
	int 		tag;
	
	QSqlDatabase    databs;
      
	 bool setAlbumArtist(const QString &path,const QString &s,const QString &album,QSqlQuery &q);
};//class

};//namespace
#endif
