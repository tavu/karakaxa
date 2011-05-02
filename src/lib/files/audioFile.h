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
#include"audioFiles.h"
#include"fileCache.h"

namespace audioFiles
{

class audioFile :public QObject
{
//     using namespace audioFiles;
    Q_OBJECT
    
    public:

	static const short int ONDATAB;
	static const short int ONCACHE;
	static const short int LOAD_FILE;
	static const short int TITLEFP;
	static const short int SELECT;
	static const short int DEFAULTF;

	audioFile(const QString);
	audioFile(const audioFiles::audioFile& f);
	audioFile* operator=(const audioFile &f);
	
	virtual ~audioFile();

	inline QString path() const
	{
	    return cache->path();
	}
	virtual QVariant tag(int t,const short int f=DEFAULTF);
	
	virtual QVariant		albumArtist();
	virtual QString			cover();

	virtual bool 			setTag(int t,QVariant var);
	virtual void			setTags(QList<int> tags,QList<QVariant> values);
	virtual int 			albumId();


	QString	folder();

	int size();

	QString format();

	inline int error()
	{
	    //return the last error
	    return err;
	}
	inline int status()
	{
	    //return an int that shows from where the last tag was loaded
	    return stat;
	}
	inline bool isMutable() const
	{
	    //a mutable audio file does not send database updated signals when makes chnges to tags
	    return _mutable;
	}
	
	inline void setMutable(bool f)
	{
	    //a mutable audio file does not send database updated signals when makes chnges to tags
	    _mutable=f;
	}

	void load();

    private:	
      
	bool prepareToSave();
	void save();	
	int err;
	int stat;
	

    protected:
      	
	QString	albumArt;
	mutable bool recFlag;
	int fileSize;

	fileTags *file;
	
	bool saveFlag;
	bool _mutable;
	
	mutable fileCache* cache;
	

//    protected slots:
	
// 	void recordClean();

};//class

};//namespace
#endif
