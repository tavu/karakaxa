#ifndef DB_SELECTION_STRINGS_H 
#define DB_SELECTION_STRINGS_H
#include <QString>
#include <QSqlQuery>
#include <tagInfo.h>


namespace database
{
    QString viewsNames(int);
    QString selectionStr(int);
    
    audioFiles::tagInfo infoFromQuery(int t,const QSqlQuery &q);
    
    QString joins(int t);
    
}

#endif
