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
#include"audioFilesFunc.h"
#include"tagsTable.h"
// #include"fileCache.h"
#include<QUrl>
namespace audioFiles
{
class fileCache;
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

		audioFile();
		audioFile(QUrl u);

		audioFile(const QString);
		audioFile(const audioFiles::audioFile &f);
		audioFile(QSqlRecord r,bool force=false);

		audioFile* operator=(const audioFile &f);

		virtual ~audioFile();

		QString path() const;

		QVariant 			tag(int t,const short int f=DEFAULTF) const;

		QVariant			albumArtist();
		QString			    cover();

		bool 			    setTag(int t,QVariant var);
		void				setTags(QList<int> tags,QList<QVariant> values);
		int 				albumId();


		QString			    folder();

		int 				size();

		QString 			format();



		int error() const
		{
			//return the last error
			return err;
		}

		int status() const
		{
			//return an int that shows from where the last tag was loaded
			return stat;
		}

		tagChangesL tagChanged() const
		{
			return changes;
		}

		void load(const short int f=SELECT|LOAD_FILE);

		bool isValid() const;
		bool exist(bool force=false);

		void setRecord(QSqlRecord r,bool force=false);
		bool inDataBase(bool force=false);

    private:

		bool setTagPrivate(int t,QVariant var);

		void save();
		mutable int err;
		mutable int stat;


    protected:

		QString	albumArt;
		mutable bool recFlag;
		int fileSize;


		bool saveFlag;

		mutable fileCache* cache;
		QList<tagChanges> changes;

		bool _exist;

    protected slots:
		void emitChanged(audioFiles::tagChangesL l)
		{
			emit changed(l);
		}
		
		void invalidSlot()
		{
			_exist=false;
			emit invalided();
		}

    signals:
      void changed(audioFiles::tagChangesL);
	  void invalided();

	  
// 	void recordClean();

};//class

};//namespace
Q_DECLARE_METATYPE(audioFiles::audioFile)

#endif
