#ifndef SONGHEADER_H
#define SONGHEADER_H
#include<QHeaderView>
#include<QContextMenuEvent>
#include<QMenu>
#include"QTreeView"
#include<player.h>
// #include <Q3PopupMenu>
class treeViewHeader :public QHeaderView
{
    Q_OBJECT
    public:
	treeViewHeader(QTreeView *parent=0);
	~treeViewHeader();

	void setNotHide(int n);
	int notHide();
	QSize sizeHint() const;

    protected:
	QMenu *menu;
	QAction *hide;
	QAction *selectColumn;

	QTreeView *treeV;

	int notHid;
	int columnClicked;

	virtual void mousePressEvent(QMouseEvent *e);
	virtual void createMenu();
// 	void leaveEvent ( QEvent * event );
// 	void enterEvent ( QEvent * event );
	
	QLineF *lines;

    protected slots:
	void hideClickedColumn();
	virtual void selectColumnW();
	void toggleHideColumn(int);
	virtual void paintSection ( QPainter * painter, const QRect & rect, int logicalIndex ) const;	

};

#endif
