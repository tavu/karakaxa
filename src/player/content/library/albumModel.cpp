#include"albumModel.h"
#include <QPixmap>
#include<views.h>
#define IMAGE 1
#define SIZE 170,150
#define TEXT_H 30

using namespace views;
albumModel::albumModel(QObject *parent)
        :QAbstractListModel(parent),
        pix(0),
        searchQ(0)
{
    maxSize.setHeight(200);
    maxSize.setWidth(190);

    itemSize.setHeight(150);
    itemSize.setWidth(150);
    
    albumGrt=new database::albumQueryGrt(this);

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

void albumModel::resizePix()
{
  /*
    if(pix!=0)
    {
      delete []pix;
    }
    pix=new QPixmap[rowCount()];
    
    for(int i=0;i<rowCount();i++)
    {
// 	QSqlRecord r=record( i );
	QVariant value=record(i).value(IMAGE);
	pix[i]=decor->cover(value.toString());
	if(pix[i].isNull() )
	{
	    pix[i]=decor->albumPic();	    
	}
	pix[i]=pix[i].scaled(imageSize, Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
    }
    */
}

QVariant albumModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() )
    {
       return QVariant();
    }
    
    if (role==Qt::DisplayRole||role==Qt::ToolTipRole)
    {       	
		return pretyTag(albums[index.row()].name,ALBUM);
    }

    if (role==Qt::DecorationRole)
    {
	QString cover=albums[index.row()].cover;

        if (cover.isEmpty() )
        {
             return decor->albumPic();
// //  	      return decor->tagIcon(ALBUM).pixmap(itemSize);
// 	      return QVariant();
        }

        QPixmap pix;
        pix=decor->cover(cover);

        if (pix.isNull() )
        {
            return decor->albumPic();
        }
        else
        {
            return pix;
        }
    }

    if (role==Qt::SizeHintRole)
    {
        return QVariant(itemSize);
    }

    return QVariant();
}

albumModel::~albumModel()
{

}

int albumModel::albumId(const int row)
{
    if(row<0||row>=albums.size() )
    {
		return -1;
    }
  
    return albums[row].id;
}

void albumModel::update()
{
//     if(!albumGrt->needUpdate() )
//     {
// 	return ;
//     }
    beginResetModel(); 
    /*
    albumGrt->setArtist(artist);
    if(searchQ!=0 && searchQ->isValid() )
    {
	albumGrt->setQuery(searchQ->clone() );
    }
    else
    {
	albumGrt->setQuery(0);	
    }
    */
//     qDebug()<<albumGrt->queryString();
    albumGrt->select();
    albums=albumGrt->result();
    endResetModel();
}




