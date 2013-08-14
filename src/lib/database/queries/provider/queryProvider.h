#ifndef QUERY_PROVIDER_H
#define QUERY_PROVIDER_H

#include"../../dbRecords/baseRecord.h"
#include"../abstractQuery.h"
#include<files/tagInfo.h>
#include<QSqlError>
#include <QStringList>
#include<Qt>

namespace database
{

class queryProvider
{
    public:
        queryProvider(int type);
        
        //populates the resultsList
        int select(abstractQuery *p=0,QList<int> order=QList<int>(),Qt::SortOrder sortOrder = Qt::AscendingOrder );
        int select(abstractQuery* q,int order,Qt::SortOrder sortOrder = Qt::AscendingOrder);
 
        QList<audioFiles::tagInfo> results();
        
        QStringList resultsStr();
        int type()
        {
            return _type;
        }
        
        QSqlError lastError();
        QString lastErrorStr();
        
    private:        
        QList<audioFiles::tagInfo> resultsList;
        QSqlError _lastError;
        int doSelect(abstractQuery *p,QList<int> order,Qt::SortOrder sortOrder); 
        int _type;
        QString table;
        
};//queryProvider

}//database
#endif