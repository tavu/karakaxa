#include"artistModel.h"
#include <QPixmap>
#include<QTextCodec>
#include<QIcon>
#include<views.h>
#include<core.h>
using namespace core;
artistModel::artistModel(QObject *parent)
        :QStringListModel(parent),
        q(0),
        _needUpdate(false)
{
    size.setHeight(100);
    size.setWidth(100);
    itemSize.setHeight(100);
    artistPic=views::decor->tagIcon(ARTIST).pixmap(50,50);
       
}


QVariant artistModel::data(const QModelIndex &index, int role) const
{

    if (role==Qt::DisplayRole)
    {
        QVariant value = QStringListModel::data(index, role);

        return views::pretyTag(value,ARTIST);
    }
    if (role==Qt::DecorationRole)
    {
	return artistPic;
// 	  pic=pic.scaled(size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
//         return decor.artistPic();
    }
    if (role==Qt::SizeHintRole)
    {
        return QVariant(itemSize);
    }
    if (role==Qt::UserRole)
    {
        return QStringListModel::data(index, Qt::DisplayRole);
    }

    return QVariant();
}

void artistModel::updateQueries()
{
//     beginResetModel();
    if(q!=0 && q->isValid() )
    {
	setStringList(core::queryGrt::artists(q) );
    }
    else
    {
	setStringList(core::queryGrt::artists() );
    }
//     endResetModel();
}


