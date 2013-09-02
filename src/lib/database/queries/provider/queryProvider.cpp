#include"queryProvider.h"
#include <Basic/tagsTable.h>
#include<tagInfo.h>
#include<dbRecords/trackViewRecord.h>
#include"dbSelectionStrings.h"
#include<database/database.h>
#include<QDebug>
database::queryProvider::queryProvider(int type) :_type(type)
{

}

QList<audioFiles::tagInfo> database::queryProvider::results()
{
    return resultsList;
}

QStringList database::queryProvider::resultsStr()
{
    QStringList l;
    foreach(audioFiles::tagInfo t,resultsList)
    {
        l<<t.data().toString();
    }
    return l;
}


int database::queryProvider::select(abstractQuery* q,QList<int> order,Qt::SortOrder sortOrder )
{
    resultsList.clear();
    _lastError=QSqlError();
    return doSelect(q,order,sortOrder);
    
}

int database::queryProvider::select(abstractQuery* q,int order,Qt::SortOrder sortOrder )
{
    resultsList.clear();
    _lastError=QSqlError();
    QList<int>l;
    l<<order;
    return doSelect(q,l,sortOrder);
    
}

int database::queryProvider::doSelect(abstractQuery* q,QList<int> order,Qt::SortOrder sortOrder)
{    
    QString joinTable;
    QString selectStr=selectionStr(_type,q,table,joinTable);
    QString qStr=selectStr;
    int ret;
    QSqlDatabase dBase=db()->getDatabase();            
    {
        QSqlQuery quer(dBase);
        
        if(q!=0) 
        {
            if(!q->isValid() )
            {
                qDebug()<<"not a valid query ";
                return Basic::UNOWN;
            }
            
            if(!joinTable.isEmpty())
            {
                qStr.append( " where " + q->text(joinTable) );
            }
            else
            {
                qStr.append( " where " + q->text(table) );
            }
        }
        
        if(order.size()!=0)
        {
            foreach(int t,order)
            {
                qStr.append( " ORDER BY " + tagFromSql(table,t)  ) +"," ;
            }
            //remove las ','
            qStr.remove(qStr.size()-1,0);
            if(sortOrder==Qt::AscendingOrder)
            {
                qStr.append(" ASC ");
            }
            else
            {
                qStr.append(" DESC ");
            }

        }
                
//         qDebug()<<qStr;
        if(!quer.exec( qStr ) )
        {    
            qDebug()<<quer.lastError().text();
            _lastError=quer.lastError();            
            ret=Basic::DBERR;
        }
        else
        {
            if(quer.size()>0 )
            {            
                resultsList.reserve(quer.size() );
            }
            
            while ( quer.next() )
            {
                audioFiles::tagInfo t=infoFromQuery(_type,quer);
                resultsList<<t;
            }
        }
        ret=Basic::OK;
    }
    
        
    db()->closeDatabase(dBase);
    return ret;
}

QSqlError database::queryProvider::lastError()
{
    return _lastError;
}

QString database::queryProvider::lastErrorStr()
{
    return _lastError.text();
}
