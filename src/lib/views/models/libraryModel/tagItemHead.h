#ifndef TAG_ITEM_HEAD_H 
#define TAG_ITEM_HEAD_H
#include <standardModel/standardModel.h>
#include"tagItem.h"
#include<Basic/tagsTable.h>
#include<files/tagInfo.h>
#include<QList>
namespace views
{
class tagItemHead :public tagItem
{
    Q_OBJECT
    public:
        tagItemHead(QObject *parent=0);
        virtual ~tagItemHead();

        virtual int columnCount() const
        {
            return Basic::FRAME_NUM;
        }

        void addTag(int t)
        {
            _tagsL.append(t);
        }
        
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        QList<int> tagList() const
        {
            return _tagsL;
        }
        
        void setCustomFilter(database::abstractQuery* q)
        {
            _customFilter=q->clone();
        }
        
        virtual database::abstractQuery* filter() const
        {
            return _customFilter;
        }
        
        void updateIfDirty();
        
    protected:
        virtual int nextData() const;
        QList<int> _tagsL;                
        inline void setNeedUpdate();
        database::abstractQuery *_customFilter;
        
    protected slots:
         void checkUpdate(database::dbEventP e);
        
    signals:
        void updateNeeded(); 
        
};

}
#endif
