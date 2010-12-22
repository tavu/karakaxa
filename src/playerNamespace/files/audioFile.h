#ifndef AUDIOFILE
#define AUDIOFILE
#include"fileTags.h"
#include<QSqlDatabase>
#include<QMutex>
#include <QHash>
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlRecord>
// #include<player.h>
#include"playerNamespace.h"

namespace player
{

class audioFile :public QObject
{
    Q_OBJECT
    
    public:
	struct audioFileS_
	{
	    int used;
	    audioFile *p;
	};
	typedef struct audioFileS_ audioFileS;

	static const short int ONDATAB;
	static const short int ONCACHE;
	static const short int ONFILE;
	static const short int TITLEFP;
	static const short int DBCACHE;
	static const short int DEFAULTF;

	audioFile(const QString);


    // 	       virtual QVariant tags(tagsEnum t);
	QString getPath();
	virtual QVariant tag(tagsEnum t,short int f=DEFAULTF);

	virtual QVariant		       albumArtist();
	virtual QString			cover();

	virtual bool 			setTag(tagsEnum t,QVariant var);

	virtual bool 			setTitle (const QString &s);
	virtual bool 			setArtist (const QString &s);
	virtual bool 			setAlbum (const QString &s);
	virtual bool 			setComment (const QString &s);
	virtual bool 			setLeadArtist (const QString &s);
	virtual bool			setComposer(const QString &s);
	virtual bool 			setGenre (const QString &s);
	virtual bool 			setYear (const unsigned int &year);
	virtual bool 			setTrack (const unsigned int &i);
	virtual bool 			setRating(const unsigned int &rating);
	virtual bool 			setCounter(const unsigned int &num);

    // 	       virtual bool			isNull() const;
	bool				onCache(tagsEnum t);

	virtual bool 			select();
	virtual int 			albumId();

	void				clear();

	QString	folder()
	{
	    return player::folder(getPath() );
	}
	int				size();

	inline QString format()
	{
	    return player::format(getPath() );
	}

	inline int error()
	{
	    return file->error();
	}
	
	inline bool isMutable()
	{
	    //a mutable audio file does not send database updated signals when makes chnges to tags
	    return _mutable;
	}
	
	inline void setMutable()
	{
	    //a mutable audio file does not send database updated signals when makes chnges to tags
	    _mutable=true;
	}


	static player::audioFile* getAudioFile(QString path);
	static void releaseAudioFile(QString path);
	static void releaseAudioFile(audioFile *file);

    private:

	QSqlDatabase databs;
	QMutex mutex;
	bool setAlbumArtist(const QString &s,QSqlQuery &q);
	
	static fileTags* getFileTags(const QString path);

	static QHash<QString, audioFileS*> fileMap;
	static QMutex gMutex;

    protected:
      	
	QString	albumArt;
	mutable QVariant *table;
	mutable bool *flags;
	mutable bool recFlag;
	int fileSize;

	fileTags *file;
	QSqlRecord record;

	bool _mutable;
	

  protected slots:
	
	void recordClean();

};//class

};//namespace
#endif
