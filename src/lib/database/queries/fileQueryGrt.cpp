#include"fileQueryGrt.h"
database::filesQueryGrt::filesQueryGrt(QObject* parent)
  :queryGrt(parent),
  thr(this)
{
//    connect(database::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
//    connect(database::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );

   connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

database::filesQueryGrt::filesQueryGrt(abstractQuery *qe,QObject* parent)
  :queryGrt(parent),
  thr(this)
{
   q=qe;
//    connect(database::db,SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
//    connect(database::db,SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate()) );

   connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

bool database::filesQueryGrt::select()
{
    emit selectionCalled();
    _needUpdate=false;
    thr.files.clear();
    if(q==0||!q->isValid() ||thr.isRunning() )
    {
        return false;
    }

   thr.start();
   _needUpdate=false;
   return true;
}

void database::filesQueryGrt::selectionFinished()
{
   emit selectionMade();
} 
