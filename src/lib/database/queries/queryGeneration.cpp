#include"queryGeneration.h"

#include<QDebug>
#include<audioFile.h>
#include<status/playerStatus.h>

#include"database.h"
#include"dbFunc.h"

using namespace audioFiles;

//==========queryGrt============
database::queryGrt::queryGrt(QObject *parent)
  :dbBase(parent),q(0)
{
    connect(db(),SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
    connect(db(),SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate(audioFiles::audioFile)) );
}

database::queryGrt::queryGrt(abstractQuery* qe, QObject* parent)
    :dbBase(parent),q(qe)
{
    connect(db(),SIGNAL(changed()),this,SLOT(setNeedUpdate()) );
    connect(db(),SIGNAL(updated(audioFiles::audioFile)),this,SLOT(setNeedUpdate(audioFiles::audioFile)) );
}

void database::queryGrt::setNeedUpdate(const audioFiles::audioFile f)
{
    if(_needUpdate)
    {
        return ;
    }
    
    if(q!=0)
    {
        _needUpdate = q->match(f);

        if(_needUpdate)
        {
            emit updateNeeded();
        }
    }
}


