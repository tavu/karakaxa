#include"artistModel.h"
#include <QPixmap>
#include<QTextCodec>
#include<QIcon>
#include<views.h>
using namespace core;
artistModel::artistModel(QObject *parent)
        :QSqlQueryModel(parent)
{

// QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
// QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
    size.setHeight(100);
    size.setWidth(100);
    itemSize.setHeight(100);
    artistPic=views::decor->tagIcon(ARTIST).pixmap(50,50);
}


QVariant artistModel::data(const QModelIndex &index, int role) const
{

    if (role==Qt::DisplayRole)
    {
        QVariant value = QSqlQueryModel::data(index, role);

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
        return QSqlQueryModel::data(index, Qt::DisplayRole);
    }

    return QSqlQueryModel::data(index, role);
}


