#ifndef ALBUM_VIEW_H
#define ALBUM_VIEW_H 

#include <QAbstractItemView>
#include<QHash>
#include<QSet>


class albumView :public QAbstractItemView
{
    Q_OBJECT
    public:
        albumView(QWidget *parent=0);
        void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible);
        QModelIndex indexAt ( const QPoint & point ) const;
        
        void setModel(QAbstractItemModel *m);
        void    setExpanded ( const QModelIndex & index, bool expanded );
        bool isExpanded(const QModelIndex & index);
        
    protected:
        int horizontalOffset () const;
        int verticalOffset () const;
        
        bool isIndexHidden ( const QModelIndex & index ) const;
        QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );
        
        void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags );
        QRect visualRect ( const QModelIndex & index ) const;
        QRegion visualRegionForSelection ( const QItemSelection & selection ) const;
                
        void rowsAboutToBeRemoved(const QModelIndex &parent,int start, int end);
        
        void paintEvent(QPaintEvent*);
        void resizeEvent(QResizeEvent *e);
        void scrollContentsBy(int dx, int dy);
        
    private:
        void calculateRectsIfNecessary() const;

        
        struct albumInfo
        {
            QRect rect;
            bool isExpanded;
        };
        mutable bool hashIsDirty;
        mutable QHash<int,struct albumInfo> albumRects;
        mutable QSet<int> expanded;
        int albumOffset;
        int rowHeight;
        int albumMinHeight;
        int albumInfoHeight;
        int albumWidth;
        int space;
        mutable QList<int> columnWidth;
        
        
        QRect itemRect(const QModelIndex &index) const;
        QRect albumRect(const QModelIndex &index) const;
        QRect viewportRectForRow(QRect rect) const;
        void calculateColumnRects(const QModelIndex &index) const;
        
        void drawChildren(const QModelIndex &index,QPainter *p);
        void drawAlbumText(QPainter* painter,const QModelIndex & index ) const;
        QRect albumTextRect(const QModelIndex &index)const;
        
    protected slots:
        void rowsInserted(const QModelIndex &parent, int start,int end);
        void currentChanged ( const QModelIndex & current, const QModelIndex & previous );
        void updateGeometries();
};

#endif