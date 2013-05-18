#ifndef FILES_DO_DB_ABS_H
#define FILES_DO_DB_ABS_H
#include <qobject.h>
#include<QSqlRecord>
namespace Basic
{
    
class filesToDb
{
    public:
        filesToDb(){}
        virtual ~filesToDb(){};
        //select the data of the file
        virtual int select()=0;
        
        //return true if this object is field with the data from the database
        virtual bool isSelected()=0;
        //get the path of the cover of the album
        //null string if error;
        virtual QString albumArt()=0;
        
        //get the tag of the file
        //null QVariant on any error
        virtual QVariant tag(int t)=0;
        
        //prepare to save the data
        virtual int prepareToSave()=0;
                
        //set the tag of the file
        //previously call prepareToSave
        virtual int setTag ( int t,QVariant &value )=0;
        
        //comit the changes to the database
        virtual int commit()=0;
        
        //return the id of the file
        virtual int id()=0;
        
        //return the path of the file
        virtual QString path()=0;
        
        //return NOTINDB if the file exist in the database
        //return OK if it exist or UNOWN if it is now kwown from previous selections        
        virtual int inDb()=0;
        
        //return the last error
        virtual int error()=0;
        
        virtual int updateRecord(QSqlRecord &r)=0;
};

filesToDb* getFdb(QString path);

};//Basic
#endif