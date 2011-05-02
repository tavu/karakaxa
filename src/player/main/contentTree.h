#ifndef CONTENTTREE_H
#define CONTENTTREE_H
#include<QTreeView>
class contentTree :public QTreeView
{
    Q_OBJECT
    public:
	contentTree(QWidget *parent=0) ;
	inline const QSize sizeHint() 
	{
	    return QSize(130,200);
	}

	void contextMenuEvent(QContextMenuEvent *e);
	
    protected:
      void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const;
};
#endif
