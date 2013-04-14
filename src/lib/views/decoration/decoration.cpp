#include"decoration.h"
#include"kglobal.h"
#define ALBUMICON ".data/album.png"
#include<kstandarddirs.h>
#include<QDebug>
#include<QApplication>
#include<KColorScheme>

using namespace audioFiles;

views::decoration::decoration()
//         :albumIcon("data/album.png"),
//         artistIcon("data/artist.png"),
    :previousIcon( "media-skip-backward" ),
     playIcon( "media-playback-start" ),
     nextIcon( "media-skip-forward" ),
     pauseIcon( "media-playback-pause" ),
     pixSize(170,150)
{
    artistIcon=KGlobal::dirs()->findResource("data",QString("karakaxa/icons/artist.png") );
    icons[ARTIST]=icon("artist");

    icons[LEAD_ARTIST]=icon("lead-artist");

    albumIcon=KGlobal::dirs()->findResource("data",QString("karakaxa/icons/album.png") );
    icons[ALBUM]=icon("album");

    icons[RATING]=KIcon("rating");
    icons[COMMENT]=icon("comment");
    icons[GENRE]=icon("genre");
    icons[TRACK]=icon("track");
    icons[LENGTH]=icon("clock");
    defaultIcon=icon("music");
    playerIcon=icon("karakaxa");

    playIcon=icon("play3");
    initPalete();
}

KIcon views::decoration::icon(const QString s)
{
    QString iconString("karakaxa/icons/");
    iconString=iconString.append(s).append(".png");
    QString iconPath=KGlobal::dirs()->findResource("data",iconString );

    if(iconPath.isNull() || iconPath.isEmpty()  )
    {
        return KIcon(s);
    }

    return KIcon(iconPath);
}


KIcon views::decoration::tagIcon(int t)
{
    if(t==audioFiles::ALBUM_ARTIST)
    {
        return icons[audioFiles::ARTIST];
    }
    if(t>=audioFiles::FRAME_NUM||t<0)
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




void views::decoration::init()
{
    pal=palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    pal.setColor(QPalette::AlternateBase,QColor(171,193,219) );
    pal.setColor(QPalette::Window,QColor(171,193,219) );

}


QPixmap views::decoration::cover(const QString &path)
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

QPixmap views::decoration::decorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    const QVariant value = index.model()->data(index, Qt::DecorationRole);
    QPixmap pixmap;

    switch (value.type())
    {
    case QVariant::Icon:
        pixmap =  toPixmap(option,qvariant_cast<QIcon>(value),index);
        break;

    case QVariant::Pixmap:
        pixmap = qvariant_cast<QPixmap>(value);
        break;


    default:
        pixmap = QPixmap();
    }

    return pixmap;
}

QPixmap views::decoration::toPixmap(const QStyleOptionViewItem &option, const QIcon &icon,const QModelIndex &index)
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

void views::decoration::initPalete()
{
    pal=qApp->palette();
    QColor c=KColorScheme(QPalette::Active, KColorScheme::Selection).background().color();
//     QColor c=KColorScheme(QPalette::Active, KColorScheme:).background().color();
    qreal h,sat,v;
    c.getHslF (&h,&sat,&v);

    c.setHslF(h,sat*0.4,v*1.30);

    pal.setColor(QPalette::Base,pal.color(QPalette::Window) );
    pal.setColor(QPalette::Window,c);
    c.setAlpha(30);
    pal.setColor(QPalette::AlternateBase,c);


}
 KIcon views::decoration::next()
{
    return icon("next");
}
 KIcon views::decoration::previous()
{
    return views::decoration::icon("previous");
}
 KIcon views::decoration::pause()
{
    return icon("pause");
}
 KIcon views::decoration::play()
{
    return icon("play4");
}
 KIcon views::decoration::muted()
{
    return KIcon("audio-volume-muted");
}
 KIcon views::decoration::volumeHigh()
{
    return KIcon("audio-volume-high");
}
 KIcon views::decoration::volumeMedium()
{
    return KIcon("audio-volume-medium");
}
 KIcon views::decoration::volumeLow()
{
    return KIcon("audio-volume-low");
}

KIcon views::decoration::playListIcon()
{
    return KIcon("audio-x-generic");
}

KIcon views::decoration::logo()
{
    return playerIcon;
}

namespace views
{
decoration *decor;
};
