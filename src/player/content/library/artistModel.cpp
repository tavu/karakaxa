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
        _needUpdate(true)
{
    itemSize.setHeight(30);
    artistPic=views::decor->tagIcon(Basic::ARTIST).pixmap(30,30);
    artistQ=new database::artistQueryGrt(this);
}


QVariant artistModel::data(const QModelIndex &index, int role) const
{

    if (role==Qt::DisplayRole)
    {
        QVariant value = QStringListModel::data(index, role);

        return views::pretyTag(value,Basic::ARTIST);
    }
    if (role==Qt::DecorationRole)
    {
	   return artistPic;
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
    if(artistQ->needUpdate() )
    {
        artistQ->select();        
        setStringList(artistQ->result());
    }        
}


