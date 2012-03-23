#include"dbFunc.h"
#include "database.h"

void database::toSqlSafe(QString &s)
{
    s.replace('\\',"\\\\");
    s.replace('\'',"\\\'");
    s.replace('\"',"\\\"");
//      s.replace('%',"\'");
}

void database::init()
{
    databaseConection::db=new databaseConection();
    databaseConection::db->createConnection();
}
