#include"decoration.h"
#include"kglobal.h"
#define ALBUMICON ".data/album.png"
#include<kstandarddirs.h>
#include<QDebug>
#include<QApplication>
#include<KColorScheme>

using namespace audioFiles;

views::decoration::decoration()
     :pixSize(170,150)
{
    albumIcon=KGlobal::dirs()->findResource("data",QString("karakaxa/icons/album.png") );
//     initPalete();
}

KIcon views::decoration::tagIcon(int t)
{
    switch (t)
    {
        case ARTIST:
        case ALBUM_ARTIST:
            return icon("artist");
        case LEAD_ARTIST:
            return icon("lead-artist");
        case ALBUM:
            return icon("album");
        case RATING:
            return KIcon("rating");
        case COMMENT:    
            return KIcon("comment");
        case GENRE:
            return icon("genre");
        case TRACK:
            return icon("track");
        case LENGTH:
            return icon("clock");
         default:
            return icon("music");
      }
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
    return icon("play");
}
 KIcon views::decoration::muted()
{
    return icon("audio-volume-muted");
}
 KIcon views::decoration::volumeHigh()
{
    return icon("audio-volume-high");
}
 KIcon views::decoration::volumeMedium()
{
    return icon("audio-volume-medium");
}
 KIcon views::decoration::volumeLow()
{
    return icon("audio-volume-low");
}

KIcon views::decoration::playListIcon()
{
    return KIcon("audio-x-generic");
}

KIcon views::decoration::logo()
{
    return icon("karakaxa");
}

QPixmap views::decoration::albumPic()
{
    return QPixmap(albumIcon);
}

KIcon views::decoration::rating(bool black)
{
    if(black)
    {
        return icon("rating-black");
    }
    else
    {
        return KIcon("rating");
    }
}


namespace views
{
decoration *decor;
};
