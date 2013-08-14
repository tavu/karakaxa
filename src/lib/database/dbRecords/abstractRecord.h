#ifndef ABSTACT_RECORD_H
#define ABSTACT_RECORD_H

#include <QSqlError>
#include<QDebug>
#include<QSqlDatabase>

namespace database
{
    
namespace dbPrivate
{
    
class abstractRecord
{
    public:
        abstractRecord(){}

        virtual ~abstractRecord(){};
        virtual void setValue(int i,QVariant v)=0;
        //return null qvariant if there is an error and an empty one if there is no value at this field
        virtual QVariant getValue(int) const=0;
        virtual void changeEntry(int i,QVariant &v) =0;
        virtual bool hasEntry(int) const=0;
        
        virtual bool hasData(int t) const
        {
            if(!hasEntry(t))
            {
                return false;
            }
            return !getValue(t).isNull();
        }
        
        virtual QString table() const=0;
        
        virtual void setDatabase(QSqlDatabase &d)=0;
        

        virtual int save()=0;
        virtual int select()=0;

        virtual QSqlError lastError()=0;
        virtual QString lastErrorStr()=0;
        
        virtual bool isSelected() const = 0;
        virtual void setSelected(bool b)  = 0;
        
};//abstractRecord

}//dbPrivate

}//database

#endif