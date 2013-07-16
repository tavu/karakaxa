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


int database::queryProvider::select(abstractQuery* q)
{
    resultsList.clear();
    _lastError=QSqlError();
    return doSelect(q);
    
}

int database::queryProvider::doSelect(abstractQuery* q)
{    
    QString selectStr=selectionStr(_type);            
    QString table=viewsNames(_type);
    if(table.isEmpty() || selectStr.isEmpty() )
    {
        qDebug()<<"table names error ";
        qDebug()<<table;
        qDebug()<<selectStr;
        return Basic::UNOWN;
    }
    
    QString qStr="SELECT DISTINCT "+selectStr+" FROM "+table;
    
    
    QSqlDatabase dBase=db()->getDatabase();            
    {
        QSqlQuery quer(dBase );
        
        if(q!=0) 
        {
            if(!q->isValid() )
            {
                qDebug()<<"not a valid query ";
                return Basic::UNOWN;
            }
            qStr.append(joins(_type) );
            qStr.append( " where (" + q->text() + ")");
        }
        qDebug()<<qStr;
        if(!quer.exec( qStr ) )
        {    
            qDebug()<<quer.lastError().text();
            _lastError=quer.lastError();            
            return Basic::DBERR;
        }
        
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
    
        
    db()->closeDatabase(dBase);
    return Basic::OK;    
}

QSqlError database::queryProvider::lastError()
{
    return _lastError;
}

QString database::queryProvider::lastErrorStr()
{
    return _lastError.text();
}
