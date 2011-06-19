#include"loadInfoThr.h"
loadInfoThr::loadInfoThr(QObject *parent)
  :QThread(parent)
{
  setTerminationEnabled(true);
  iter=fileList.end();
}

void loadInfoThr::run()
{
     core::db->getDatabase();
     updateTracks();
     core::db->closeDatabase();
}

void loadInfoThr::updateTracks()
{
     for(;iter!=fileList.end();iter++)
     {	
// 	qDebug()<<"E";  
     	iter->load();
// 	qDebug()<<"ET "<<iter->status();
//  	iter->load(audioFiles::audioFile::LOAD_FILE);
     }

}

void loadInfoThr::cleanup()
{
//     terminate();
    fileList.clear();
    iter=fileList.end();
    qDebug()<<"cleared";
}
