#ifndef NPLAYLISTVIEW_H
#define NPLAYLISTVIEW_H

#include<QListView>
#include<QTreeView>
#include<QMouseEvent>
#include<QLabel>
#include<core.h>
#include<views.h>
class nplaylistView :public views::treeView
{
    Q_OBJECT
    public:

	   nplaylistView(QWidget *parent=0);
	   void mouseMoveEvent(QMouseEvent *event);
	   void mousePressEvent(QMouseEvent *event);
	   void performDrag();
	   Qt::DropActions supportedDropActions () const;
	   int sizeHintForColumn(int column) const;
	   
	   QAction *removeAction()
	   {
	      return _removeAction;
	   }

	   QAction *goToCurrent();
	   
    private:
	   QPoint startPos;
	   QAction *_removeAction;
	   QAction *duplicateAction;


	   void contextMenuEvent(QContextMenuEvent *e);
	   QMenu* createMenu();
	   void keyPressEvent(QKeyEvent *event);

    protected:
        void mouseDoubleClickEvent(QMouseEvent* event);
	   void dragEnterEvent ( QDragEnterEvent * event );
	   void dragLeaveEvent ( QDragLeaveEvent * event );
	   void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	   void paintEvent(QPaintEvent * event);
	   void dropEvent ( QDropEvent * event );
// 	   void mouseDoubleClickEvent ( QMouseEvent * event ) ;
	   bool onDrag;
	   
    public slots:
       void goToCurrentTrack();
	   void play(const QModelIndex &index);
    private slots:
	   void remove();	   
	   void duplicate();

};






#endif
