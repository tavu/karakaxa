#include"loadInfoThr.h"
#include<player.h>
loadInfoThr::loadInfoThr(QObject *parent)
  :QThread(parent),
  canceled(false)
{
//   setTerminationEnabled(true);
    iter=fileList.end();
}

void loadInfoThr::run()
{
     canceled=false;      
     
    if(iter==fileList.end() )
    {
	iter=fileList.begin();
    }
    updateTracks();
     
}

void loadInfoThr::updateTracks()
{

     for(;iter!=fileList.end() && !canceled ;iter++)
     {
	iter->load();
     }

}

void loadInfoThr::cleanup()
{
    cancel();
    iter=fileList.end();
}
