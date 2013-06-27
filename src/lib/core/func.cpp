#include"func.h"
#include<QFile>
#include<QTextCodec>
#include<kmimetype.h>
#include"core.h"
#include <kapplication.h>

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include<QFileInfo>
#include<QDir>

#ifdef USE_LAST_FM 
	#include<lastFmFunc.h>
#endif

void core::init()
{
    static bool flag=true;
    
    if(flag)
    {
      
      qRegisterMetaType<audioFiles::audioFile>("audioFile");
      qRegisterMetaType<QVector<audioFiles::audioFile> >("QVector<audioFiles::audioFile>");
      qRegisterMetaType<QVector<audioFiles::audioFile> >("QVector<audioFile>");
      qRegisterMetaType<audioFiles::audioFile>("audioFiles::audioFile");
      
      config =new PlayerConfigure();
      soundEngine::init();
      nplaylist::init();
      contentHdl=new contentHandler(qApp );
      
#ifdef USE_LAST_FM
	  lastFm::init();
#endif
      
      flag=false;            
    }
}

void core::cleanUp()
{     
    nplaylist::cleanUp();
    soundEngine::cleanUp();
    delete config;
    delete contentHdl;
    
}
