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
	
	
	QPixmap cover(const QString &path);
	
	inline QSize coverSize()
	{
	  //scalding the pixmap is very slow.
	  //that's why we scaled the images to pixSize before we save them to the cache
	  //that makes the cache unapropriate if u want images larger than pixsize.
	    return pixSize;
	}
	
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


