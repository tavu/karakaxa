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
// 	   void performDrag();
	   Qt::DropActions supportedDropActions () const;
	   int sizeHintForColumn(int column) const;
	   
	   QAction *removeAction()
	   {
	      return _removeAction;
	   }

	   QAction *goToCurrent();
	   
    private:
	   QAction *_removeAction;
	   QAction *duplicateAction;


	   void contextMenuEvent(QContextMenuEvent *e);
	   QMenu* createMenu();

    protected:
       void mouseDoubleClickEvent(QMouseEvent* event);
	   
    public slots:
       void goToCurrentTrack();
	   void play(const QModelIndex &index);
    private slots:
	   void remove();	   
	   void duplicate();

};






#endif
