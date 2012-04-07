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
    
}

database::queryGrt::queryGrt(abstractQuery* qe, QObject* parent)
    :dbBase(parent),q(qe)
{
    connect(db(),SIGNAL( newEvent(dbEventP)),this,SLOT(dbEvents(dbEventP)) );    
}

void database::queryGrt::dbEvents(database::dbEventP e)
{
    int t=e->type();
    if(t==FILES_REM || t==FILES_INS || t==UPDATE_COMP || t==RESCAN_COMP || t==NEW_CONN)
    {
        setNeedUpdate();
        return ;
    }
}

void database::queryGrt::setNeedUpdate()
{
    if(_needUpdate==true)
    {
        return ;
    }
    _needUpdate=true;
    emit updateNeeded();        
}
