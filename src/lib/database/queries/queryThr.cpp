#include"queryThr.h"
#include"../status/playerStatus.h"
#include"queryGeneration.h"
#include"database.h"

void database::queryThr::run()
{
    queryGrt *g=static_cast<queryGrt*>(parent() );
  
    QSqlDatabase dBase=db()->getDatabase();        
            
    {
        QSqlQuery quer(dBase );

        if(!quer.exec(g->queryString() ) )
        {
            core::status->addErrorP(quer.lastError().text() );
            core::status->addError("executing query error");
            db()->closeDatabase(dBase);
            return ;
        }

        int i=0;
        if(quer.size()>0 )
        {
            files.reserve(quer.size() );
        }

        while ( quer.next() )
        {
            audioFiles::audioFile f(quer.record() );
            files.append(f);
            map.insert(f.path(),f);
        }
    }
    
    db()->closeDatabase(dBase);        
}
