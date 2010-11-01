#include<artistModel.h>
#include <QPixmap>
#include<QTextCodec>
#include<QIcon>
using namespace player;
artistModel::artistModel(QObject *parent)
        :QSqlQueryModel(parent)
{

// QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
// QTextCodec::setCodecForTr(QTextCodec::codecForName ("UTF-8"));
    size.setHeight(100);
    size.setWidth(100);
    itemSize.setHeight(100);
}


QVariant artistModel::data(const QModelIndex &index, int role) const
{

    if (role==Qt::DisplayRole)
    {
        QVariant value = QSqlQueryModel::data(index, role);
        if (value.toString().isEmpty() )
        {
            return QVariant("Unown Artist");
        }
    }
    if (role==Qt::DecorationRole)
    {
// 	  pic=pic.scaled(size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
        return decor.artistPic();
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

void artistModel::queryChange ()
{

}
