#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include<QTreeView>
#include <QModelIndex>
#include<QMouseEvent>
#include<QApplication>
#include<KUrl>
#include<QMenu>
#include"treeViewDelegate.h"
#include"treeViewHeader.h"
// #include"editTrack.h"

namespace views
{

class treeView :public QTreeView
{
    Q_OBJECT
    public:

	treeView(QWidget *parent=0,QString name=QString());

	virtual void	setModel ( QAbstractItemModel * model );

	virtual void	mousePressEvent(QMouseEvent *event);
	virtual void 	setRatingColumn(const int n);
	virtual int 	ratingColumn() const;
	virtual void 	setNotHide(int n);
	virtual int	notHide();

    protected:
	QPoint startPos;
	views::treeViewDelegate *delegate;

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void performDrag();
	virtual void contextMenuEvent(QContextMenuEvent *e);
	void headerRepaint();
	virtual void leaveEvent(QEvent*)  ;

    protected slots:
	virtual void commitData ( QWidget * editor ) ;

    public slots:
	virtual void writeSettings();
	virtual void readSettings();
	virtual void updateStarWidget(QModelIndex parent, int start, int end);
	virtual void dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
	virtual void closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint );
	virtual void play(const QModelIndex index);
	
    signals:
	void showContextMenu(QModelIndex);
	
};//class

};//namespace
#endif
