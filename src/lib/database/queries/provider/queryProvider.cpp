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
    QString selectStr=selectionStr(_type,q,table);
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
            qStr.append( " where " + q->text(table) );
        }
        qDebug()<<qStr;
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
