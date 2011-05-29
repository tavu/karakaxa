#ifndef FILETODB
#define FILETODB

#include"fileTags.h"
#include<QSqlDatabase>
#include<QMutex>
#include<QSqlQuery>
#include<QSqlError>
// #include<player.h>
// #include"playerNamespace.h"

// class audioFile;

namespace audioFiles
{

class fileToDb
{
    public:	
      
	const static int OK;
	const static int DBERR;
	const static int NOTINDB;

	fileToDb(QString path)
	{
	    _path=path;
	}

	int commit();
	
	void setAlbum(const QString &s)
	{
	    _album=s;
	}
	
	void setArtist(const QString &s)
	{
	    _artist=s;
	}
	
	void setTag(int t,QVariant var);
	
// 	void save();
	
	static int 	setTitle (const QString path,const QString &s);
	static int 	setArtist (const QString path,const QString &s,const QString &album);
	static int 	setAlbum (const QString path,const QString &s);
	static int 	setComment (const QString path,const QString &s);
	static int 	setLeadArtist (const QString path,const QString &s,const QString &artist,const QString &album);
	static int	setComposer(const QString path,const QString &s);
	static int 	setGenre (const QString path,const QString &s);
	static int 	setYear (const QString path,const unsigned int &year);
	static int 	setTrack (const QString path,const unsigned int &i);
	static int 	setRating(const QString path,const unsigned int &rating);
	static int 	setCounter(const QString path,const unsigned int &num);
	static int 	setAlbumArt(const int albumId,QString art);

	static QSqlRecord 	record(const QString path,int &err);
	static QString	 albumArt(const int albumId,int &err);
    
    private:
	QString		_album;
	QString 	_artist;
	QString 	_path;
	int 		_id;
	int 		_tag;
	QVariant 	value;
	int 		tag;
      
	static bool setAlbumArtist(const QString &path,const QString &s,const QString &album,QSqlQuery &q);
};//class

};//namespace
#endif
