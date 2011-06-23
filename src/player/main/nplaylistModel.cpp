#include"nplaylistModel.h"
#include<QList>
#include<QUrl>
#include<QMimeData>
#include<QStringList>
#include<KIcon>
#include"nowPlayList/nplaylist.h"
#include"views.h"

// #include "myUrl.h"
using namespace core;
using namespace views;


nplModel::nplModel( QObject * parent)
        :nplAbstractModel(parent),
        size(0)
{
}

int nplModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}


QVariant nplModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid() )
    {
        return QVariant();
    }

    nplPointer t=npList->getTrack(index.row() );

    if (role==Qt::DisplayRole || role==Qt::ToolTipRole)
    {	
	 if (t.isNull())	return QVariant();
	 
	 if(index.column()==0)
	 {
		return t->tag(TRACK);
	 }
	 else
	 {
		return t->title();
	 }	
    }
    if(role==URL_ROLE)
    {
	   return QVariant( KUrl(t->path() ) );
    }
    
    
    return QVariant();

}

QVariant nplModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if(section==0)
    {
	if(role==Qt::DecorationRole)
	{
	    return decor->tagIcon(TRACK);
	}
	if(role==Qt::DisplayRole)
	{
	    return QVariant();
	}
    }
    if(section==1)
    {
	if(role==Qt::DisplayRole)
	{
	    return tr("title");
	}
	if(role==Qt::DecorationRole)
	{
	    return decor->tagIcon(TITLE);
	}
    }
    return nplAbstractModel::headerData(section,orientation,role);
}


bool nplModel::dropMimeData ( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(column);
    if (row<0)
        row=npList->size();

    if (reorderL.size()==0 )
    {
        npList->addMediaList( data->urls(),row );
    }
    else
    {
        reorder(row);
    }
    return true;
}

void nplModel::setReorder(set< int >& l)
{
    reorderL=l;
}

void nplModel::clearReorder()
{
    reorderL.clear();
}

void nplModel::reorder(int r)
{
    set<int>::const_iterator it=reorderL.begin();

    int n=0;
//     while (it!=reorderL.end() )
//     {
//         if (*it<r)
//         {
//             npList->move(*it-n,r-1);
//             n++;
//         }
//         else
//         {
//             npList->move(*it,r);
//         }
//         it++;
//     }
    
    for(;it!=reorderL.end();it++)
    {		
	if(*it<r)
	{
	    npList->move(*it-n,r-1);
	    n++;
	}
	else
	{
	    npList->move(*it,r);
	}
    }
}


Qt::DropActions nplModel::supportedDropActions () const
{
    return Qt::CopyAction|Qt:: MoveAction|Qt::IgnoreAction;
}

QStringList nplModel::mimeTypes () const
{
    QStringList qstrList;
    qstrList.append("text/uri-list");
    return qstrList;
}

Qt::ItemFlags nplModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled  | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}
