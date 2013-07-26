#ifndef ALBUM_VIEW_HEADER_H 
#define ALBUM_VIEW_HEADER_H
#include<views/models/treeViewHeader.h>

class albumViewHeader ://public views::treeViewHeader
                        public QHeaderView
{
    public:
        albumViewHeader(QWidget *parent=0);
        
    protected:
        void paintSection ( QPainter * painter, const QRect & rect, int logicalIndex ) const;  
        void leaveEvent ( QEvent * event );
    private:
        QPalette pal;
};

#endif
