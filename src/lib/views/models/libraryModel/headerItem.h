#ifndef HEADER_ITEM_H
#define HEADER_ITEM_H
#include <standardModel/standardModel.h>
#include <Basic/tagsTable.h>
#include<views/models/urlRole.h>
#include<views/decoration/decoration.h>
#include<views/viewsFunc.h>
namespace views
{
class headerItem :public standardItem
{
    public:
        headerItem():standardItem(){}
        virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const 
        {
            if(role == Qt::DisplayRole )
            {
                QString s=views::tagName(column);
                return QVariant(s);
            }
            if(role == BOLD_ROLE)
            {
                return QVariant(true);
            }
            return QVariant();
        }
        
        int columnCount() const
        {
            return Basic::FRAME_NUM;
        }
};

}
#endif