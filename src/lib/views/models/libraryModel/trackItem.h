#ifndef TRACKMODEL_H
#define TRACKMODEL_H
#include <qobject.h>

// #include<queries/queryGeneration.h>
// #include<queries/fileQueryGrt.h>

#include<core/standardModel/standardModel.h>
#include<files/audioFiles.h>
#include<views.h>
#include"tagItem.h"

namespace views
{

class trackItem :public standardItem
{
    Q_OBJECT
    public:
        trackItem(audioFiles::audioFile f,QObject *parent=0);
        trackItem(audioFiles::tagInfo,QObject *parent=0);
        
        virtual int columnCount() const
        {
            return Basic::FRAME_NUM+1;
        }

        virtual bool setData (const QVariant &value,int column, int role );
        virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const;

        virtual Qt::ItemFlags flags ( int column) const
        {
            return standardItem::flags(column) |Qt::ItemIsEditable;
        }
        
        bool canFetchMore() const;

    protected:
        audioFiles::audioFile file;

    protected slots:
        void changed(audioFiles::tagChangesL);

};

}
#endif