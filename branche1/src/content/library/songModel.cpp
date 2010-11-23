#include<songModel.h>
#include<player.h>
#include<QSqlRecord>
#include"QSortFilterProxyModel"
// #define ARTISTSL	13
#define ITEM_HEIGHT 20
using namespace player;
songModel::songModel(QWidget *parent)
        :QSqlTableModel(parent ,db.getDatabase())
{

//      setSourceModel(&queryM);



    setTable("trackView");
//      setHeaderData(TRV_TRACK, Qt::Horizontal, "#");
//       queryM.setHeaderData(TRV_LEAD_ARTIST, Qt::Horizontal, tr("Lead Artist") ,Qt::DisplayRole);
    removeColumns(0,TRV_HIDE);
//      setSort(0,Qt::DescendingOrder);
    select();
    connect(&db, SIGNAL(changed()),this,SLOT(refresh()) );
}

Qt::ItemFlags songModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant songModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlTableModel::data(index, role);

    if (index.column()==TRACK && value.toInt()==0)
    {
        return QVariant();
    }
    if (index.column()==LENGTH )
    {
        if ( value.toInt()==0)
        {
            return QVariant();
        }
        return prettyLength(value.toInt() );
    }



    return value;
}

KUrl songModel::url(int row) const
{
//      int k=PATH;
    QString s=record(row).value(PATH).toString() ;

    return KUrl(s);
}

bool songModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    qDebug()<<"column: "<<index.column();
    audioFile *f=audioFile::getAudioFile(url(index.row()).toLocalFile() );

    if (f==0)	return false;

    return true;
}

void songModel::refresh()
{
    //we make a slot from the function
    select();
}


QVariant songModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if (section==TRACK)
    {
        return QVariant(QString("#") );
    }
    return QSqlTableModel::headerData(section,orientation,role);
}
/*
int songModel::columnCount ( const QModelIndex & parent ) const
{
     return 14;
}*/

