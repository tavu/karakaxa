#ifndef DB_SELECTION_STRINGS_H 
#define DB_SELECTION_STRINGS_H
#include <QString>
#include <QSqlQuery>
#include <tagInfo.h>
#include <queries/abstractQuery.h>


namespace database
{
    QString selectionColumns(QString ,int);
    QString selectionStr(int tag,const abstractQuery *q,QString &table,QString &joinTable);
    
    audioFiles::tagInfo infoFromQuery(int t,const QSqlQuery &q);
    
    
    QString tagFromSql(QString table,int tag);
    
    QString tagFromTrackView(int t);
    QString tableName(int tag);
    
}

#endif
