#ifndef BASE_RECORD_H 
#define BASE_RECORD_H

#include<QObject>
#include<QSqlError>
#include <QSqlQuery>
#include<QMap>
#include<QVariant>

#include"entry.h"
#include"abstractRecord.h"

namespace database
{
namespace dbPrivate
{

class baseRecord :public  abstractRecord , public entry
{
    public:
        baseRecord(QString t=QString());
        virtual ~baseRecord();
        virtual void setValue(int i,QVariant v) ;
        QVariant getValue(int) const;
        virtual void changeEntry(int i,QVariant &v);
        
        bool hasEntry(int) const;
        
        void setDatabase(QSqlDatabase&);
        
        QVariant id() const;
        void setId(QVariant v);
        
        bool isRelated(int);
        baseRecord* getRelated(int) const;
        static baseRecord* getRelatedEntry(entry *e);
        
        virtual int save();
        int insert();        
        int select();
        int selectAll();
        
        void clearId();        
        
        QSqlError lastError();
        QString lastErrorStr();
        bool isSelected() const;
        void setSelected(bool b);
        
        QString table() const;
        
        //===implementation of entry===
        QString sqlType() const;
        bool hasChanged() const;
        QVariant value() const; //returns the id
        QVariant newValue() const; //returns the new id if it has changed
        int saveValue(); 
        void changeValue(QVariant &v); //change the id
        void setValue(QVariant v); //sets the id
        void clearNewValue(); 
        void clearData(); 
        //=========================
        
        
    protected:
        void addEntry(int,entry*);        
        //saves the data after save on the original entries
        virtual void saveDataLocaly();     
        
        QMap<int,entry*> entries;
        
        typedef QMap<int, entry*>::const_iterator constEntryIter;
        typedef QMap<int, entry*>::iterator entryIter;    
        
        int doSave();
        int doInsert();
        int doUpdate();
        
        void setError(QString s);
        
        void setError(QSqlError r);
        
        void clearError();
        
        void setTable(QString s);
        QSqlDatabase databs;
        
    private:
        
        QVariant _id;
        bool _hasChanged;        
        
        int selectFromId();
        int selectFromUnique();
        QString selectStr();
        int execSelect(QSqlQuery &q);
        
        int saveAllRelated();
        entryIter nextUnique(entryIter it);
        
        QVariant _newId;
        bool _needNewId;
        
        QSqlError _lastError;
        bool _isSelected;
        QString _table;
};
// Q_DECLARE_METATYPE(database::databasedbPrivate::baseRecord*);

}

}

#endif
 
