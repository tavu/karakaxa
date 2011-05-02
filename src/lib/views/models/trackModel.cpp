#include"trackModel.h"
#include<views.h>
#include<QSqlRecord>
#include"QSortFilterProxyModel"
#include<audioFiles.h>
#include"../core/database/database.h"
#include"urlRole.h"

views::trackModel::trackModel(QWidget *parent)
        :QSqlQueryModel(parent ),
        _order(1),
	sortO(Qt::AscendingOrder),
	doNotUpdate(false)
{
//    setSourceModel(&queryM);   
//      setSort(0,Qt::DescendingOrder);
//     select();
    connect(core::db, SIGNAL(changed()),this,SLOT(refresh()) );    
}

void views::trackModel::setFilter(const QString &s)
{
    _filter=s;
    select();
    
    
//     queryM.removeColumn(0);
}

void views::trackModel::select()
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
    
//     qDebug()<<q;
//     QSqlQuery query(q);
//     
//     if(!query.exec() )
//     {
// 	qDebug()<<query.lastError().text();
//     }
    
//     result =query.result();
     setQuery(q,core::db->getDatabase() );
    
//     emit(newQuery() );
}



Qt::ItemFlags views::trackModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant views::trackModel::data(const QModelIndex &i, int role) const
{      
  
    if(role==Qt::DisplayRole)
    {
      
	QSqlRecord r=record(i.row());
	if(r.isEmpty() )
	{
	    return QVariant();
	}
	return pretyTag(r.value(i.column()+1),i.column() );
    }
    else if(role==URL_ROLE)
    {        
	QSqlRecord r=record(i.row());
	if(r.isEmpty() )
	{
	    return QVariant();
	}

      
	QString s=r.value(PATH+1).toString();
	KUrl u(s);
	return QVariant(u);
    }
    else
    {
	return QSqlQueryModel::data(i,role);
    }
    
}

int views::trackModel::columnCount ( const QModelIndex & index ) const
{
    return FRAME_NUM;
}

KUrl views::trackModel::url(int row) const
{
    QModelIndex	i=index(row,PATH);
    
    QString s=record(row).value(PATH).toString() ;
    
    return KUrl(s);
}

bool views::trackModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    /*urlList conteins all urls of the selected indexes.with no dublicates.
     * we set the data to all of them
     */
    if(!audioFiles::fileList.isEmpty() )
    {
	QLinkedList<audioFile>::iterator it=audioFiles::fileList.begin();
	for(; it !=audioFiles::fileList.end()-1; it++ )
	{
	    it->setMutable(true);
	    it->setTag( (tagsEnum)index.column(),value );
	}
	it->setMutable(false);
	it->setTag( (tagsEnum)index.column(),value );
	audioFiles::fileList.clear();
    }
    else
    {
	audioFile f(url(index.column() ).toLocalFile() );
	f.setTag(index.column(),value );
    }
    
    /*it does not need to emit the dataChanged signall.
     * actualy we are not soure which indexes had changed.
     * However that's ok
     */ 
  
    return true;
}

void views::trackModel::refresh()
{
    //we need this as a slot    
//        clear();
       select();      
}


QVariant views::trackModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if(role==Qt::DisplayRole)
    {
	if (section==TRACK)
	{
	    return QVariant(QString("#") );
	}
	return QVariant(tagName( (tagsEnum)section) );
    }
    if(role==Qt::DecorationRole)
    {
	return QVariant(decor->tagIcon( section) );
    }
//     return QVariant();
    return QSqlQueryModel::headerData(section,orientation,role);
}


void views::trackModel::sort ( int column, Qt::SortOrder order )
{
    setSort(column,order);
    select();
}

void views::trackModel::setSort ( int column, Qt::SortOrder order )
{
    _order=column+2;
    sortO=order;
}
