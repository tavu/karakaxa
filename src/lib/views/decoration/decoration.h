#ifndef DECORATION_H
#define DECORATION_H

#include<QPalette>
#include<kicon.h>
#include <QPixmapCache>
#include<QStyleOptionViewItem>
#include<QModelIndex>
#include <Basic/tagsTable.h>


namespace views
{

class decoration
{      
    public:
        decoration();

        static KIcon icon(const QString s);

    QPalette palette()
    {
        return pal;
    }

        inline QPixmap albumPic()
        {
            return QPixmap(albumIcon );
        }

    KIcon next();

    KIcon previous();

    KIcon pause();

    KIcon play();

    KIcon muted();

    KIcon volumeHigh();

    KIcon volumeMedium();

    KIcon volumeLow();

    KIcon rating(bool black=false);

    KIcon playListIcon();


    KIcon tagIcon(int t);

    KIcon logo();


    void initPalete();


    QPixmap cover(const QString &path);

    QSize coverSize()
    {
        //scaling the pixmap is very slow.
        //that's why we scaled the images to pixSize before we save them to the cache
        //that makes the cache inapropriate if u want images larger than pixsize.
        return pixSize;
    }
    void init();

    static QPixmap decorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index);
    static QPixmap toPixmap(const QStyleOptionViewItem &option, const QIcon &icon,const QModelIndex &index);
private:
    QPalette pal;

    KIcon icons[audioFiles::FRAME_NUM];
    KIcon defaultIcon;

    QSize pixSize;
    QString albumIcon;
};

extern decoration *decor;

        QSize pixSize;
};

    extern decoration *decor;
    
};//namespace
#endif


