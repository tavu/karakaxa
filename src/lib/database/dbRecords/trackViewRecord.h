#ifndef TRACK_VIEW_RECORD_H
#define TRACK_VIEW_RECORD_H

#include"abstractRecord.h"

namespace database
{
    
namespace dbPrivate
{
class trackRecord;
class baseRecord;
class trackViewRecord :public abstractRecord
{
    public:     
        trackViewRecord(QString path);
        trackViewRecord(int id);
        virtual ~trackViewRecord();
        
        virtual void setValue(int i,QVariant v);
        virtual QVariant getValue(int) const;
        virtual void changeEntry(int i,QVariant &v);
        virtual bool hasEntry(int) const;
                
        virtual int save();
        virtual int select();        
        
        virtual QString table() const;        
        virtual void setDatabase(QSqlDatabase &d);

        virtual QSqlError lastError();
        virtual QString lastErrorStr();
        
        virtual bool isSelected() const;
        
        void clearNewValue();
        
        baseRecord* getAlbumRecord() const;
        baseRecord* getTrackRecord() const;        
        
        int updateRecord(QSqlRecord &r);
        static QString path(QSqlRecord &r);
        
        
    private:
        trackRecord *track;
        bool _isSelected;
        
};//trackViewRecord


}//dbPrivate

};
#endif
