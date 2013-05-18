#ifndef COLUMN_ENTRY_H
#define COLUMN_ENTRY_H
#include "entry.h"

namespace database
{
    
namespace dbPrivate
{
class columnEntry :public entry
{
    public:                
        
        columnEntry(QString name,QString sqlType,bool unique=false);
        
        //the sql type of the colum px int(10)
        virtual QString sqlType() const;
        
        //if a new value exist
        virtual bool hasChanged() const;
                
        //the value of the enty
        virtual QVariant value() const;
        
        //the new value of the entry
        virtual QVariant newValue() const;
        
        //save the new value as a current value
        virtual int saveValue();
        
        //set the new value of the entry and the hasChanged property
        //it is possible for the entry to make changes of the value(e.g simplification of string)
        virtual void changeValue(QVariant &v);
        
        //sets the value of the entry. Neither the newValue  nor the hasChanged properties are changed
        virtual void setValue(QVariant v);
        
        void clearData();
        
        void clearNewValue();
        
        bool allowValueChanges()
        {
            return _valluChangesAllowed;
        }
        
        void setAllowValueChanges(bool b)
        {
            _valluChangesAllowed=b;
        }
        
    private:
        bool _hasChanged;
        QString _sqlType;
        QVariant _value;
        QVariant _newValue;
        
        bool _valluChangesAllowed;
        
};//columnEntry
    
}//dbPrivate

}//database
#endif