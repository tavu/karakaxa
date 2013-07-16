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
        tagItem(tagSelector *s);
        tagItem();
        virtual ~tagItem();
        virtual bool canFetchMore () const;      
        virtual void fetchMore ();
        virtual int columnCount() const;
        virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const ;
        virtual void update();
        
        const tagSelector * selector() const
        {
            return _ts;
        }
        
        
    protected:
        tagSelector *_ts;
        tagItem* head();
        
        inline tagItem* parentItem() const;
        
        virtual int nextData() const;
        
        virtual void appendData(int);
        
        standardItem* newItemInstance(tagSelector *s);
        
};

    
}
#endif
