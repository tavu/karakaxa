#include"albumModel.h"
#include <QPixmap>

#define IMAGE 1
#define SIZE 170,150
#define TEXT_H 30

using namespace player;
albumModel::albumModel(QObject *parent)
        :QSqlQueryModel(parent),
        pix(0)
{
    maxSize.setHeight(200);
    maxSize.setWidth(230);

    itemSize.setHeight(150);
    itemSize.setWidth(180);

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
 	itemSize.setWidth(itemSize.width()-10);
    }
//     resizePix();
    imageSize=itemSize;
    imageSize.setHeight(itemSize.height()-TEXT_H);
    layoutChanged();
}

void albumModel::resizePix()
{
    if(pix!=0)
    {
      delete []pix;
    }
    pix=new QPixmap[rowCount()];
    
    for(int i=0;i<rowCount();i++)
    {
// 	QSqlRecord r=record( i );
	QVariant value=record(i).value(IMAGE);
	pix[i]=decor.cover(value.toString());
	if(pix[i].isNull() )
	{
	    pix[i]=decor.albumPic();	    
	}
	pix[i]=pix[i].scaled(imageSize, Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
    }
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
// 	return pix[index.row() ];
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
//   resizePix();
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





