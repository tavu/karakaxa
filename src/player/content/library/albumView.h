#ifndef ALBUM_VIEW_H
#define ALBUM_VIEW_H

#include <QAbstractItemView>
#include "albumViewHeader.h"
#include<QHash>
#include<QSet>


class albumView :public QAbstractItemView
{
    Q_OBJECT
    public:
        albumView(QString name=QString(),QWidget *parent=0);
        ~albumView();
        void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible);
        QModelIndex indexAt ( const QPoint & point ) const;

        void setModel(QAbstractItemModel *m);
        void    setExpanded ( const QModelIndex & index, bool expanded );
        bool isExpanded(const QModelIndex & index) const;
        QRect visualRect ( const QModelIndex & index ) const;
        
        QList<QUrl>  urlsFromIndex(const QModelIndex &index) const;
    protected:
        int horizontalOffset () const;
        int verticalOffset () const;

        void startDrag ( Qt::DropActions supportedActions );

        bool isIndexHidden ( const QModelIndex & index ) const;
        QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );

        void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags );

        QRegion visualRegionForSelection ( const QItemSelection & selection ) const;

        void rowsAboutToBeRemoved(const QModelIndex &parent,int start, int end);

        QRect indexRect(const QModelIndex &index) const;

        void paintEvent(QPaintEvent*);
        void resizeEvent(QResizeEvent *e);
        void scrollContentsBy(int dx, int dy);

        void    mouseMoveEvent ( QMouseEvent * event );
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent ( QMouseEvent * event );
        
        void readSettings();
        void writeSettings();
    private:
        void calculateRectsIfNecessary() const;

        mutable bool hashIsDirty;
        mutable QHash<int,QRect> albumRects;
        mutable QSet<int> expanded;

        int albumOffset;
        int rowHeight;
        int albumMinHeight;
        int albumInfoHeight;
        int albumWidth;
        int space;

        QRect headerRect(int row) const;
        QRect itemsRect(int parentRow) const;
        QRect itemRect(const QModelIndex &index) const;
        QRect itemRect(int row,int column,int parentR) const;
        QRect albumRect(const QModelIndex &index) const        ;
        QRect viewportRectForRow(QRect rect) const;

        void paintHeader(QPainter *painter,QRect &rect,int logicalIndex);

    //         void calculateColumnRects(const QModelIndex &index) const;

        void drawChildren(const QModelIndex &index,QPainter *p);
        void drawAlbum(QPainter* painter,QStyleOptionViewItemV4 &option,const QModelIndex & index ) const;

        QStyleOptionViewItemV4 styleOptions(const QModelIndex &index) const;
        QModelIndex hoverIndex;
        QPoint mousePoint;
        int headerRow;

        inline bool isAlbum(const QModelIndex &index) const;
        inline void updateScrollBars() const;

        albumViewHeader *header;


    protected slots:
        void rowsInserted(const QModelIndex &parent, int start,int end);
        void currentChanged ( const QModelIndex & current, const QModelIndex & previous );
        void updateGeometries();
        void resetSlot();
        void columnsUpdated();
        void hideHeader();
        void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
        void doubleClickedSlot ( const QModelIndex &index );
};

#endif
