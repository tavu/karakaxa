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
    return FRAME_NUM;
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
	 	 
	 return t->tag(index.column());
    }
    if(role==URL_ROLE)
    {
	   return QVariant( KUrl(t->path() ) );
    }
    
    
    return QVariant();

}

QVariant nplModel::headerData ( int section, Qt::Orientation orientation, int role ) const
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
    return nplAbstractModel::headerData(section,orientation,role);
}


bool nplModel::dropMimeData ( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(column);
    if (row<0)
        row=npList->size();


    if (views::reorderL.size()==0 )
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
    set<int>::const_iterator it=views::reorderL.begin();

    int n=0;
    int k=0;
    for(;it!=views::reorderL.end();it++)
    {
	   if(*it<r )
	   {
		  npList->move(*it-n,r-1);
		  n++;
	   }
	   else
	   {
		  npList->move(*it,r+k);
		  k++;
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
    if(!index.isValid() )
	   return Qt::ItemIsDropEnabled;
    
    return Qt::ItemIsDragEnabled  | Qt::ItemIsEnabled |Qt::ItemIsSelectable;
}

bool nplModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    QString s=index.data(URL_ROLE).toUrl().toLocalFile();
    audioFile f(s);
    if(f.isValid() )
    {
        f.setTag(index.column(),value);
        if(f.error()==OK)
        {
            return true;
        }
    }
    return false;
}

