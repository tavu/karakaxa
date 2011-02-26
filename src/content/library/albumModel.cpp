#include"albumModel.h"
#include <QPixmap>

#define IMAGE 1
#define SIZE 170,150
using namespace player;
albumModel::albumModel(QObject *parent)
        :QSqlQueryModel(parent)
{
    maxSize.setHeight(230);
    maxSize.setWidth(230);

//     minSize.setHeight(80);
//     minSize.setHeight(80);
    itemSize.setHeight(180);
    itemSize.setWidth(180);
// 	  defaultPic=new QPixmap(size);
// 	  defaultPic->load("/home/tavu/src/player/data/album.png");
// 	  defaultPic->scaled(size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

void albumModel::resize(QSize &s)
{
    layoutAboutToBeChanged ();    
    if (s.height()>maxSize.height() )
    {
	itemSize=maxSize;
    }
    else
    {
	itemSize=s;
    }    
    layoutChanged();
}

QVariant albumModel::data(const QModelIndex &index, int role) const
{
    if (role==Qt::DisplayRole||role==Qt::ToolTipRole)
    {
        QVariant value = QSqlQueryModel::data(index, Qt::DisplayRole);
	
	return player::pretyTag(value,ALBUM);
    }

    if (role==Qt::DecorationRole)
    {
        QSqlRecord r=record( index.row() );
        QVariant value=r.value(IMAGE);

        if (!value.isValid()||value.isNull() )
        {
             return decor.albumPic();
// //  	      return decor.tagIcon(ALBUM).pixmap(itemSize);
// 	      return QVariant();
        }

        QPixmap pix;
        pix=decor.cover(value.toString());

        if (pix.isNull() )
        {
// 	    return decor.tagIcon(ALBUM).pixmap(itemSize);
            return decor.albumPic();
        }
        else
        {
// 	       pix=pix.scaled(size,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            return pix;
        }
    }

    if (role==Qt::SizeHintRole)
    {
// 	return property("size");
        return QVariant(itemSize);
    }

    QVariant value = QSqlQueryModel::data(index, role);
    return value;
}

void albumModel::queryChange ()
{
}

albumModel::~albumModel()
{

}

int albumModel::albumId(const int row)
{
    QSqlRecord r=record(row);

    if (r.isEmpty() )
    {
        return -1;
    }

    return r.value(2).toInt();
}





