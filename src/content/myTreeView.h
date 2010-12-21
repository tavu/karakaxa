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
class myTreeView :public QTreeView
{
    Q_OBJECT
    public:

	myTreeView(QWidget *parent=0,QString name=QString());

	virtual void	setModel ( QAbstractItemModel * model );

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void setRatingColumn(const int n);
	virtual int ratingColumn() const;
	virtual void setNotHide(int n);
	virtual int notHide();


    protected:
	QPoint startPos;
	treeViewDelegate *delegate;

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void performDrag();


    private:
	//actions
	QAction *appendAcion;
	QAction *editAcion;
	QAction *deletAcion;
	QAction *editTrAcion;

    protected slots:
	virtual void fileEdit();
	

    public slots:
	virtual void writeSettings();
	virtual void readSettings();
	virtual void updateStarWidget(QModelIndex parent, int start, int end);	  
};
#endif
