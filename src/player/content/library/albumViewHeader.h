#ifndef ALBUM_VIEW_HEADER_H 
#define ALBUM_VIEW_HEADER_H
#include<views/models/treeViewHeader.h>

class albumViewHeader :public views::treeViewHeader
{
    Q_OBJECT
    public:
        albumViewHeader(QWidget *parent=0);
        QSize sizeHint() const;
    protected:
        void paintSection ( QPainter * painter, const QRect & rect, int logicalIndex ) const;   

};

#endif
