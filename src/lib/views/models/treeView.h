#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include<QTreeView>
#include <QModelIndex>
#include<QMouseEvent>
#include<QApplication>
#include<KUrl>
#include <QLinkedList>
#include<QMenu>
#include"treeViewDelegate.h"
#include <set>

namespace views
{

class treeView :public QTreeView
{
    Q_OBJECT
    public:

        treeView(QWidget *parent=0,QString name=QString());
        ~treeView();
        virtual void	setModel ( QAbstractItemModel * model );

        virtual void	mousePressEvent(QMouseEvent *event);
        virtual void 	setRatingColumn(const int n);
        virtual int 	ratingColumn() const;
        virtual void 	setNotHide(int n);
        virtual int	    notHide();
        virtual Qt::DropActions supportedDropActions () const;

        static QList<QUrl> getUrls(const QModelIndexList &list);

        bool playOnDoubleCl()
        {
            return _playOnDoubleCl;
        }

        void setPlayOnDoubleCl(bool b)
        {
            _playOnDoubleCl=b;
        }

    protected:
	   QPoint startPos;
       int _ratingColumn;
	   views::treeViewDelegate *delegate;

       virtual void mouseDoubleClickEvent ( QMouseEvent * event );
	   virtual void mouseMoveEvent(QMouseEvent *event);
	   virtual void performDrag();
	   virtual void contextMenuEvent(QContextMenuEvent *e);
               void headerRepaint();
	   virtual void leaveEvent(QEvent*)  ;
       virtual void dropEvent ( QDropEvent * event );

       void paintEvent(QPaintEvent * event);

    protected slots:
        virtual void commitData ( QWidget * editor ) ;
        virtual void rowsInserted ( const QModelIndex & parent, int start, int end );

    private:
        bool _playOnDoubleCl;
        
	
    public slots:
       virtual void reset();
	   virtual void writeSettings();
	   virtual void readSettings();
	   virtual void dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
	   virtual void closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint );
	   virtual void play(const QModelIndex &index);
	   
       virtual void updateStarWidget(QModelIndex parent, int start, int end);
       virtual void updateStarWidget();
	   
	   virtual void needExpanding(QModelIndex parent, int start, int end);
	   
	   virtual void itemClicked(const QModelIndex &);

       void editCurrent()
	   {
		  edit(currentIndex() );
	   }
	
    signals:
        void showContextMenu(QModelIndex,QModelIndexList);
	
};//class

    extern std::set<int> reorderL;

    
};//namespace
#endif
