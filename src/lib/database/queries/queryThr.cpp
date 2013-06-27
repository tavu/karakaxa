#include"queryThr.h"
#include<Basic/status.h>
#include"queryGeneration.h"
#include"../database.h"

void database::queryThr::run()
{
    queryGrt *g=static_cast<queryGrt*>(parent() );
  
    QSqlDatabase dBase=db()->getDatabase();        
            
    {
        QSqlQuery quer(dBase );

        if(!quer.exec(g->queryString() ) )
        {
            Basic::msg()->logErr(quer.lastError().text() );
            Basic::msg()->error("executing query error");
            db()->closeDatabase(dBase);
            return ;
        }

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
