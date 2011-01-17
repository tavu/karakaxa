#include"loadInfoThr.h"
#include<player.h>
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
     audioFile *f;
     for(;iter!=fileList.end();iter++)
     {	
 	f=audioFile::getAudioFile(*iter);
 	for (int i=TAGS_START;i<FRAME_NUM;++i)
 	{
 	    f->tag( (tagsEnum)i);
 	}
// 	audioFile::releaseAudioFile(f);
     }

}

void loadInfoThr::cleanup()
{
    terminate();
    foreach(QString s, fileList)
    {
        audioFile::releaseAudioFile(s);
    }
    fileList.clear();
    iter=fileList.end();
}
