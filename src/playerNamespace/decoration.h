#ifndef DECORATION_H
#define DECORATION_H

#include<QPalette>
#include<KIcon>
#include <QPixmapCache>

namespace player
{

class decoration
{
public:
    decoration();

    inline QPalette palette()
    {
        return pal;
    }
    inline KIcon album()
    {
        return KIcon(albumIcon);
    }

    inline QPixmap albumPic()
    {
        return QPixmap(albumIcon );
    }

    inline KIcon artist()
    {
        return KIcon(artistIcon );
    }

    inline QPixmap artistPic()
    {
        return QPixmap(artistIcon );
    }

    inline KIcon next()
    {
        return nextIcon;
    }
    inline KIcon previous()
    {
        return previousIcon;
    }
    inline KIcon pause()
    {
        return pauseIcon;
    }
    inline KIcon play()
    {
        return playIcon;
    }

    QPixmap cover(const QString &path);

private:
    QPalette pal;

    //icons
    QString albumIcon;
    QString artistIcon;

    KIcon nextIcon;
    KIcon previousIcon;
    KIcon pauseIcon;
    KIcon playIcon;

    QSize pixSize;
};

};//namespace
#endif
