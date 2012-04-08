#include"fileQueryGrt.h"
database::filesQueryGrt::filesQueryGrt(QObject* parent)
  :queryGrt(parent),
  thr(this)
{
   connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

database::filesQueryGrt::filesQueryGrt(abstractQuery *qe,QObject* parent)
  :queryGrt(parent),
  thr(this)
{
   q=qe;

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

void database::filesQueryGrt::dbEvents(database::dbEventP e)
{
    using namespace audioFiles;
    if(needUpdate() )
    {
        return ;
    }
    
    if(e->type()==FILES_CHANG)
    {        
        dbEventAF *ev = static_cast<dbEventAF*>(e.data());
        
        foreach(const audioFile &f, ev->files)
        {
            if(q!=0 && q->match(f) )
            {
                setNeedUpdate();
                return ;
            }
        }
    }
//     queryGrt::dbEvents(e);
}
