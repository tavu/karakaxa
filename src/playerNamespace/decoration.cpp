#include"decoration.h"
#define ALBUMICON "/home/tavu/src/player/data/album.png"

player::decoration::decoration()
        :albumIcon("/home/tavu/src/player/data/album.png"),
        artistIcon("/home/tavu/src/player/data/artist.png"),
        previousIcon( "media-skip-backward" ),
        playIcon( "media-playback-start" ),
        nextIcon( "media-skip-forward" ),
        pauseIcon( "media-playback-pause" ),
        pixSize(170,150),
        defaultIcon("/home/tavu/player/trunk/data/music.png")
{
    icons[ARTIST]=KIcon("/home/tavu/src/player/data/artist.png");
    icons[ALBUM]=KIcon("/home/tavu/src/player/data/album.png");
    icons[RATING]=KIcon("rating");
}

KIcon player::decoration::tagIcon(int t)
{
    if(t>=FRAME_NUM)
    {
	return defaultIcon;
    }
    KIcon i=icons[t];
    if(i.isNull() )
    {
	return defaultIcon;
    }
    return i;
}




void player::decoration::init()
{
    pal=palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    pal.setColor(QPalette::AlternateBase,QColor(171,193,219) );
    pal.setColor(QPalette::Window,QColor(171,193,219) );
    
}


QPixmap player::decoration::cover(const QString &path)
{
    QPixmap pm;

    if (!QPixmapCache::find(path, &pm))
    {
        pm.load(path);
        if (pm.isNull())
        {
            return pm;
        }
        pm=pm.scaled(pixSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        QPixmapCache::insert(path, pm);
    }

    return pm;
}
