#include"decoration.h"
#include"kglobal.h"
#define ALBUMICON ".data/album.png"
#include<KStandardDirs>
#include<QDebug>

player::decoration::decoration()
//         :albumIcon("data/album.png"),
//         artistIcon("data/artist.png"),
        :previousIcon( "media-skip-backward" ),
        playIcon( "media-playback-start" ),
        nextIcon( "media-skip-forward" ),
        pauseIcon( "media-playback-pause" ),
        pixSize(170,150)
//         defaultIcon("data/music.png")
{
    QString artistS=KGlobal::dirs()->findResource("data",QString("player/icons/artist.png") );
    qDebug()<<"artist icon location "<<artistS;
    icons[ARTIST]=KIcon(artistS);
    
    albumIcon=KGlobal::dirs()->findResource("data",QString("player/icons/album.png") );
    qDebug()<<"album icon location "<<albumIcon;
    icons[ALBUM]=KIcon(albumIcon);
    
    icons[RATING]=KIcon("rating");
    
    QString defaultS=KGlobal::dirs()->findResource("data",QString("player/icons/music.png"));
    qDebug()<<"default icon location"<<defaultS;
    defaultIcon=KIcon(defaultS);
}

KIcon player::decoration::tagIcon(int t)
{
    if(t>=FRAME_NUM||t<0)
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
