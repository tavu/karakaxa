#ifndef FILES_TO_DB_IMPL_H
#define FILES_TO_DB_IMPL_H

#include<Basic/filesToDb.h>
#include"trackViewRecord.h"
#include"database/dbBase.h"
namespace database
{

class filesToDbImpl :public Basic::filesToDb , public dbBase
{
    public:
        filesToDbImpl(QString path,QObject *parent=0);
        filesToDbImpl(int id,QObject *parent=0);
        
        //select the data of the file
        int select();
        
        //get the path of the cover of the album
        //null string if error;
        QVariant albumArt();
        
        int fetchAlbumArt();
        
        bool isSelected();
        
        //get the tag of the file
        //null QVariant on any error       
        QVariant tag(int t);
        
        //prepare to save the data
        int prepareToSave();
                
        //set the tag of the file
        //previously call prepareToSave
        int setTag ( int t,QVariant &value );
        
        //comit the changes to the database
        int commit();
        
        //return the id of the file
        int id();
        
        //return the path of the file
        QString path();
                
        int inDb();
        
        //return the last error
        int error();
        
        int updateRecord(QSqlRecord &r);       
        
    private:
        
//         dbPrivate::baseRecord *record();
        
        dbPrivate::trackViewRecord *track;        
        QSqlDatabase    databs;
        int _error;
        int _inDb;
};

}

#endif