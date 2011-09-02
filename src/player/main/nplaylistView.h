#ifndef NPLAYLISTVIEW_H
#define NPLAYLISTVIEW_H

#include<QListView>
#include<QTreeView>
#include<QMouseEvent>
#include<QLabel>
#include<core.h>
class nplaylistView :public QTreeView
{
    Q_OBJECT
    public:

	   nplaylistView(QWidget *parent=0);
	   void mouseMoveEvent(QMouseEvent *event);
	   void mousePressEvent(QMouseEvent *event);
	   void performDrag();
	   Qt::DropActions supportedDropActions () const;
	   int sizeHintForColumn(int column) const;
	   
	   void setModel(QAbstractItemModel *model)
	   {
		  QAbstractItemModel *m=QTreeView::model();
		  QTreeView::setModel(model); 
		  if(m!=0)
		  {
			 disconnect(m, 0, this, 0);
		  }
		  connect(model,SIGNAL(rowsInserted ( const QModelIndex, int, int )),this ,SLOT(inserted(QModelIndex,int,int)) );
        }
    private:
	   QPoint startPos;
	   QAction *removeAction;
	   QAction *duplicateAction;


	   void contextMenuEvent(QContextMenuEvent *e);
	   QMenu* createMenu();
	   void keyPressEvent(QKeyEvent *event);

    protected:
	   void dragEnterEvent ( QDragEnterEvent * event );
	   void dragLeaveEvent ( QDragLeaveEvent * event );
	   void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	   void paintEvent(QPaintEvent * event);
	   void dropEvent ( QDropEvent * event );
	   void mouseDoubleClickEvent ( QMouseEvent * event ) ;
	   bool onDrag;
	   
    public slots:
	   void play(const QModelIndex &i);
    private slots:
	   void remove();	   
	   void duplicate();

};






#endif
