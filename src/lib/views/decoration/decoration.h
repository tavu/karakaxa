#ifndef DECORATION_H
#define DECORATION_H

#include<QPalette>
#include<kicon.h>
#include <QPixmapCache>
#include<QStyleOptionViewItem>
#include<QModelIndex>
// #include"../../files/tagsTable.h"
#include"../../files/tagsTable.h"

namespace views
{

class decoration
{      
    public:
	decoration();

	inline QPalette palette()
	{
	    return pal;
	}
	
	inline QPixmap albumPic()
	{
	    return QPixmap(albumIcon );
	}

	inline KIcon artist()
	{
	    return KIcon(artistIcon );
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
	inline KIcon muted()
	{
	    return KIcon("audio-volume-muted");
	}
	inline KIcon volumeHigh()
	{
	    return KIcon("audio-volume-high");
	}
	inline KIcon volumeMedium()
	{
	    return KIcon("audio-volume-medium");
	}
	inline KIcon volumeLow()
	{
	    return KIcon("audio-volume-low");
	}
	
	KIcon tagIcon(int t);
	
	
	QPixmap cover(const QString &path);
	
	inline QSize coverSize()
	{
	  //scaling the pixmap is very slow.
	  //that's why we scaled the images to pixSize before we save them to the cache
	  //that makes the cache unapropriate if u want images larger than pixsize.
	    return pixSize;
	}
	void init();
	
	static QPixmap decorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index);
	static QPixmap toPixmap(const QStyleOptionViewItem &option, const QIcon &icon,const QModelIndex &index);
    private:
	QPalette pal;

	//icons
	QString albumIcon;
	QString artistIcon;

	KIcon nextIcon;
	KIcon previousIcon;
	KIcon pauseIcon;
	KIcon playIcon;

	KIcon icons[audioFiles::FRAME_NUM];
	KIcon defaultIcon;
	
	QSize pixSize;
};

    extern decoration *decor;
    
};//namespace
#endif


