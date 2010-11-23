#ifndef SMARTPLAYLISTDELEGATE_H
#define SMARTPLAYLISTDELEGATE_H
#include<QItemDelegate>
#include<QTreeWidget>
class smartPlaylistDelegate : public QItemDelegate
{
public:
    smartPlaylistDelegate ( QTreeWidget *parent = 0 );
// 	  void paint( QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index ) const;

    QWidget *createEditor( QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index ) const;

// 	  void setEditorData( QWidget *editor,const QModelIndex &index ) const;
// 	  void setModelData( QWidget *editor,QAbstractItemModel *model,const QModelIndex &index ) const;
// 	  void updateEditorGeometry( QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index ) const;
private:
    QTreeWidget *treeW;
};

#endif

