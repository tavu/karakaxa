#include"dbFunc.h"
#include "database.h"
#include"databaseEvent.h"
void database::toSqlSafe(QString &s)
{
    s.replace('\\',"\\\\");
    s.replace('\'',"\\\'");
    s.replace('\"',"\\\"");
//      s.replace('%',"\'");
}

void database::init()
{
    qRegisterMetaType<database::dbEventP>("database::dbEventP");
    databaseConection::init();
}

void database::cleanup()
{
    delete databaseConection::db;
}
