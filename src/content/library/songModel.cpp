#include<songModel.h>
#include<player.h>
#include<QSqlRecord>
#include"QSortFilterProxyModel"
// #define ARTISTSL	13
#define ITEM_HEIGHT 20
using namespace player;
songModel::songModel(QWidget *parent)
        :QSqlQueryModel(parent ),
        _order(1),
	sortO(Qt::AscendingOrder)
{
//    setSourceModel(&queryM);   
//      setSort(0,Qt::DescendingOrder);
//     select();
//     connect(&db, SIGNAL(changed()),this,SLOT(refresh()) );
}

void songModel::setFilter(const QString &s)
{
    _filter=s;
    select();
    
//     queryM.removeColumn(0);
}

void songModel::select()
{
    //we make the selection again and we refresh the database
    
    QString q("select * from trackView where %1 order by %2 %3");
    q=q.arg(_filter);
    q=q.arg(_order);
    
    if(sortO==Qt::AscendingOrder)
    {
	q=q.arg("ASC");
    }
    else
    {
	q=q.arg("DESC"); 
    }
    
    setQuery(q,db.getDatabase());
    qDebug()<<query().lastQuery();
}



Qt::ItemFlags songModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant songModel::data(const QModelIndex &i, int role) const
{
    QModelIndex in=index(i.row(),i.column()+1);
    QVariant value = QSqlQueryModel::data(in, role);

    if (in.column()==TRACK && value.toInt()==0)
    {
        return QVariant();
    }
    if (in.column()==LENGTH )
    {
        if ( value.toInt()==0)
        {
            return QVariant();
        }
        return prettyLength(value.toInt() );
    }



    return value;
}

int songModel::columnCount ( const QModelIndex & index ) const
{
    QSqlQueryModel::columnCount(index)-1;
}

KUrl songModel::url(int row) const
{
    QModelIndex	i=index(row,PATH);
//     QModelIndex	index=mapToSource(i);
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
    //we need this as a slot
    clear();
    select();
}


QVariant songModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if(role==Qt::DisplayRole)
    {
	if (section==TRACK)
	{
	    return QVariant(QString("#") );
	}
	return QVariant(tagName( (tagsEnum)section) );
    }
    
    return QSqlQueryModel::headerData(section,orientation,role);
}


void songModel::sort ( int column, Qt::SortOrder order )
{
    setSort(column,order);
    select();
}

void songModel::setSort ( int column, Qt::SortOrder order )
{
    _order=column+2;
    sortO=order;
}
