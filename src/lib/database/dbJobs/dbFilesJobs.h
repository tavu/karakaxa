#ifndef DB_FILES_JOBS_H
#define DB_FILES_JOBS_H

#include"dbThrJob.h"
#include"../libraryFolder.h"
#include <KIO/CopyJob>
#include<QFile>
#include"rescanJob.h"

namespace database
{


class removeFiles :public dbThrJob
{
	Q_OBJECT
	public:
		removeFiles(QStringList paths,QObject *parent=0) :dbThrJob(parent),_paths(paths){}

		void run();
		
	protected:
		QStringList _paths;		
		
	protected slots:
		void jobDone(KJob *j);
		
};

class createPl :public dbThrJob
{
	public:
		createPl(QString path,QObject *parent=0) :dbThrJob(parent),_path(path){}
		
		void run()
		{
			QFile file(_path);
			if ( !file.open(  QIODevice::WriteOnly ) )
			{
				return ;
			}
			file.close();
			libraryFolder f;
			f.addPlaylist(_path);
		}
	private:
		QString _path;
		
};


class removePl :public dbThrJob
{
	Q_OBJECT
	public:
		removePl(QString path,QObject *parent=0) :dbThrJob(parent),_path(path){}
		
		void run()
		{
			KIO::CopyJob *j=KIO::trash(_path );
			connect(j,SIGNAL( result( KJob* ) ),this,SLOT(jobDone(KJob*) ) );
		}
		
	private:
		QString _path;
		
	protected slots:
		void jobDone(KJob *j)
		{				
			if(j->error()!=0)
			{
				QFile fil(_path);
				if(!fil.exists() )
				{
					libraryFolder f;		
					f.removePlaylist(_path);
				}
			}
			else
			{
				libraryFolder f;
				f.removePlaylist(_path);
			}
		}
};

}
#endif