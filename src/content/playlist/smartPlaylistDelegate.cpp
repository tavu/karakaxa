#include"smartPlaylistDelegate.h"
#include"smartPlaylistItem.h"
#include <QSpinBox>
smartPlaylistDelegate::smartPlaylistDelegate( QTreeWidget *parent )
        :QItemDelegate(parent)
{
    treeW=parent;
    treeW->setItemDelegate(this);
}

QWidget *smartPlaylistDelegate::createEditor( QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index ) const
{
//      smartPlaylistItem *item=static_cast<smartPlaylistItem *>(&index);
//      dQTreeWidgetItem *item=treeW->itemFromIndex(index);
//      if(item->type()==smartPlaylistItem::TAGTYPE)
//      {
// 	  QVariant var=item->data(1,Qt::UserRole);
//
// 	  if(var.toInt()==YEAR)
// 	  {
// 	       QSpinBox *spin=new QSpinBox(this);
// // 	       return spin;
// 	  }
//      }
}

