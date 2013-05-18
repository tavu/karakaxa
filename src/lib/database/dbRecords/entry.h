#ifndef ENTRY_H
#define ENTRY_H

#include<QString>
#include<QVariant>
namespace database
{
    
namespace dbPrivate
{

class entry
{
    public:
        virtual ~entry(){};
        
        //the sql name of the column
        QString name() const
        {
            return _name;
        }
        
        void setName(const QString &name)
        {
            _name=name;
        }
        
        //the sql type of the colum px int(10)
        virtual QString sqlType() const=0;
        
        //if a new value exist
        virtual bool hasChanged() const=0;
        
        //if the entry is defined as unique at the database
        bool isUnique() const
        {
            return _unique;
        }
        
        void setUnique(bool b)
        {
            _unique=b;
        }
        
        bool isNotNull()
        {
            return _notNull;
        }
        
        void setNotNull(bool b)
        {
            _notNull=b;
        }
        
        //the value of the enty
        virtual QVariant value() const=0;
        
        //the new value of the entry
        virtual QVariant newValue() const=0;
        
        //return the new value if exist or if it is not returns the value
        virtual QVariant chosenValue() const
        {
            if(hasChanged())
            {
                return newValue();
            }
            return value();
        }
        //save the new value as a current value
        virtual int saveValue()=0;
        
        //set the new value of the entry and the hasChanged property
        //it is possible for the entry to make changes of the value(e.g simplification of string)
        virtual void changeValue(QVariant &v)=0;
        
        //sets the value of the entry. Neither the newValue  nor the hasChanged properties are changed
        virtual void setValue(QVariant v)=0;
        
        virtual void clearNewValue()=0;
        
        virtual void clearData()=0;
        
        
    protected:
        entry():_notNull(false),_unique(false){}
        
        QString _name;
        bool _unique;
        bool _notNull;


};//class

}//databasePrivate

}//database
#endif