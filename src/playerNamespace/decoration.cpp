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
    
    QString commentIcon=KGlobal::dirs()->findResource("data",QString("player/icons/comment.png") );
    icons[COMMENT]=KIcon(commentIcon);
    
    QString trackIcon=KGlobal::dirs()->findResource("data",QString("player/icons/track.png") );
    icons[TRACK]=KIcon(trackIcon);
    
    QString lengthIcon=KGlobal::dirs()->findResource("data",QString("player/icons/clock.png") );
    icons[LENGTH]=KIcon(lengthIcon);
    
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

QPixmap player::decoration::decorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    const QVariant value = index.model()->data(index, Qt::DecorationRole);
    QPixmap pixmap;

    switch (value.type())
    {
	case QVariant::Icon:
	    pixmap =  toPixmap(option,qvariant_cast<QIcon>(value),index);
	    break;

	case QVariant::Pixmap:        pixmap = qvariant_cast<QPixmap>(value);
	    break;


	default:
	    pixmap = QPixmap();
    }
 
    return pixmap;
}

QPixmap player::decoration::toPixmap(const QStyleOptionViewItem &option, const QIcon &icon,const QModelIndex &index)
{
    QIcon::Mode mode   = option.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled;
    QIcon::State state = option.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
    QSize s=option.decorationSize;
    
    if(s.isValid())
    {
	int h=option.rect.height();
	s=QSize(h,h);
    }

//     int h=option.rect
//     s=QSize(h,h);
    
    const QSize size = icon.actualSize(s, mode, state);
    return icon.pixmap(size, mode, state);
}