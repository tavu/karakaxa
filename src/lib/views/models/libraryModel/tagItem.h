#ifndef TAG_ITEM_H 
#define TAG_ITEM_H

#include <standardModel/standardModel.h>
#include"tagSelector.h"

namespace views
{
class tagItemHead;
class tagItem :public standardItem
{
    Q_OBJECT
    public:
        tagItem(audioFiles::tagInfo &info);
        tagItem();
        virtual ~tagItem();
        virtual bool canFetchMore () const;      
        virtual void fetchMore ();
        virtual int columnCount() const;
        virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const ;
        virtual void update();
        
        void sort(int column, Qt::SortOrder order = Qt::AscendingOrder );
        
        virtual Qt::ItemFlags flags ( int column) const;
        
        virtual database::abstractQuery* filter() const;
                
    protected:
//         tagSelector *_ts;
        
        audioFiles::tagInfo _info;
        
        inline tagItem* parentItem() const;
        
        virtual int nextData() const;
        void insert(int row, standardItem *item);
//         virtual void appendData(int);
        
        standardItem* newItemInstance(audioFiles::tagInfo &info);
        bool populate();
        bool _isDirty;
        int _sort;
        Qt::SortOrder _sortOrder;
};

    
}
#endif
