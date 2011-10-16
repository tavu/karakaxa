#include"loadInfoThr.h"
loadInfoThr::loadInfoThr(QObject *parent)
  :QThread(parent),
  canceled(false)
{
  setTerminationEnabled(true);
  iter=fileList.end();
  mutex=new QMutex();
}

void loadInfoThr::run()
{
     canceled=false;
     core::db->getDatabase();
     updateTracks();
     core::db->closeDatabase();
}

void loadInfoThr::updateTracks()
{	
	while(!canceled)
	{
		iter->load();
		mutex->lock();
		iter++;
		if(iter==fileList.end() )
		{
		    mutex->unlock();
		    break ;
		}
		mutex->unlock();		
	}
}

void loadInfoThr::addItems(QLinkedList<audioFiles::audioFile> &l)
{
    if(l.isEmpty() )
    {
	   return ;
    }
    mutex->lock();

    if(iter==fileList.end() )
    {
	   //if the list is empty propably the thread is not running
	   if(fileList.isEmpty() )
	   {
		  fileList+=l;
		  iter=fileList.begin();
		  mutex->unlock();
		  start();
	   }
	   else
	   {
		  //make iter2 to show the last valid item
		  QLinkedList<audioFiles::audioFile>::iterator iter2=fileList.end();
		  iter2--;
		  //append the list
		  fileList+=l;
		  //iter shows the first new item
		  iter=iter2++;		  
		  mutex->unlock();
		  //the thread is about to terminate. wait for it
		  wait();
		  start();
	   }
	   
    }
    else
    {
	   fileList+=l;
	   mutex->unlock();
    }
}


void loadInfoThr::cleanup()
{
    cancel();
    wait();
    mutex->lock();
    fileList.clear();
    iter=fileList.end();
    mutex->unlock();;
}
