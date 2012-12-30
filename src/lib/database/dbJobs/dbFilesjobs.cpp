#include"dbFilesJobs.h"
#include"../libraryImpUpdate.h"


void database::removeFiles::run()
{
	KIO::CopyJob *j=KIO::trash(_paths );
	connect(j,SIGNAL( result( KJob * ) ),this,SLOT(jobDone(KJob*) ) );
}

void database::removeFiles::jobDone(KJob *j)
{
// 	libraryImpUpdate *importer = new libraryImpUpdate();
	if(j->error()!=0)
	{
		db()->update();
	}
	else
	{
		libraryFolder f;
		f.removeFiles(_paths);
	}
}
