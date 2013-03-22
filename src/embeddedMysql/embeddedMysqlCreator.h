#ifndef EMBEDDED_MYSQL_CREATOR_H
#define EMBEDDED_MYSQL_CREATOR_H

#include <QSqlDriverCreatorBase>
#include "qsql_mysql.h"

class embeddedMysqlCreator :public QSqlDriverCreatorBase
{
    public:
       embeddedMysqlCreator(){}
       QSqlDriver* createObject () const
       {
           return new QMYSQLDriverEmbedded();
       }

};

#endif