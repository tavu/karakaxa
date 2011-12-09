#include"myFileSystemModel.h"
#include<views.h>
#define DIRCOLUMN 7
using namespace core;
myFileSystemModel::myFileSystemModel(QObject *parent)
        :KDirModel(parent)
{
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),&thr,SLOT(cleanup() ) );
    connect(&thr,SIGNAL(finished () ),this,SLOT( callRest() ) );
}

void myFileSystemModel::callRest()
{
    beginResetModel ();
    endResetModel();
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+FRAME_NUM;
}

QVariant myFileSystemModel::data(const QModelIndex &index, int role) const
{   
    if(role == URL_ROLE)
    {
	   return QVariant(url(index.row() ) );
    }
  
    if (index.column()<DIRCOLUMN)
    {
        return KDirModel::data(index,role);
    }

    if (role==Qt::DisplayRole)
    {
	   QVariant var;
        KFileItem item=itemForIndex(index);
        if (item.isDir() )	return QVariant();
	
        audioFile f(item.url().toLocalFile() );	

        int filde=index.column()-DIRCOLUMN;
	
        var=f.tag(filde, audioFile::ONCACHE|audioFile::ONDATAB );	
	   
	   return views::pretyTag(var,filde);
    }        
    
    return QVariant();

}

bool myFileSystemModel::setData( const QModelIndex & index, const QVariant & value, int role)
{
    int tag=index.column()-DIRCOLUMN;
    QUrl u=index.data(URL_ROLE).toUrl();
    
    if(u.isValid() )
    {
	   audioFile f(u.toLocalFile() );
	   f.setTag(tag,value);
  	   emit dataChanged(index,index);
	   return true;
    }
    
    return true;
}

QVariant myFileSystemModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if (section<DIRCOLUMN)
    {
        return KDirModel::headerData(section,orientation,role);
    }

    if (role ==Qt::DisplayRole)
    {
        return views::tagName( (tagsEnum)(section-DIRCOLUMN) );
    }    
    return QVariant();
}

void myFileSystemModel::insert(const KFileItemList &items)
{    
    QLinkedList<audioFiles::audioFile> l;
    foreach(KFileItem item , items)
    {
	   if( core::isAudio(item.url().toLocalFile() )  )
        {
		  l<<audioFiles::audioFile( item.url().toLocalFile() );
        }
    }
    thr.addItems(l);    
}


int myFileSystemModel::infoC()
{
    return DIRCOLUMN;
}


Qt::ItemFlags myFileSystemModel::flags ( const QModelIndex & index ) const
{
    static Qt::ItemFlags f= Qt::ItemIsEnabled | Qt::ItemIsSelectable |Qt::ItemIsDragEnabled|Qt::ItemIsEditable;
    return f;
}

KUrl myFileSystemModel::url( int row) const
{
    QModelIndex i=index(row,0);

    return  itemForIndex(i).url();

}
