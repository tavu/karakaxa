#include"loadInfoThr.h"
loadInfoThr::loadInfoThr(QObject *parent)
  :QThread(parent)
{
  setTerminationEnabled(true);
}

void loadInfoThr::run()
{
     updateTracks();
}

void loadInfoThr::updateTracks()
{
     for(;iter!=fileList.end();iter++)
     {	 	
	iter->load();
     }

}

void loadInfoThr::cleanup()
{
    terminate();
    fileList.clear();
    iter=fileList.end();
}
