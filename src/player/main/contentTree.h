#ifndef CONTENTTREE_H
#define CONTENTTREE_H
#include<QTreeView>
#include<QTimer>
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
        void dragMoveEvent ( QDragMoveEvent * event );
        void dropEvent ( QDropEvent * event )
        {
            //TODO drop the item on the content if support it
            return ;
        }

        Qt::DropActions supportedDropActions() const;
        void dragEnterEvent ( QDragEnterEvent * event );
        void dragLeaveEvent ( QDragLeaveEvent* event );
        QModelIndex dropIndex;
        QTimer *timer;
	 
    private slots:
        void dropTime();
};
#endif
