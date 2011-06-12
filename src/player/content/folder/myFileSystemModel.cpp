#include"myFileSystemModel.h"
#include<views.h>
#define DIRCOLUMN 7
using namespace core;
myFileSystemModel::myFileSystemModel(QObject *parent)
        :KDirModel(parent)
{
    thr.iter=thr.fileList.end();
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),&thr,SLOT(cleanup() ) );
    connect(&thr,SIGNAL(finished () ),this,SLOT( callRest() ) );
}

void myFileSystemModel::callRest()
{
//     reset();
    emit dataChanged (index(0,DIRCOLUMN+1),index(rowCount()-1,DIRCOLUMN+FRAME_NUM-1 ) );
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+FRAME_NUM;
}

QVariant myFileSystemModel::data(const QModelIndex &index, int role) const
{   
    if(role == URL_ROLE)
    {
// 	qDebug()<<itemForIndex(index).url();
	return QVariant(itemForIndex(index).url() );
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
    KFileItem item=itemForIndex(index);
    audioFile f(item.url().toLocalFile() );
    int filde=index.column()-DIRCOLUMN;
    f.setTag(filde,value);
    
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
    foreach(KFileItem item , items)
    {
	if( core::isAudio(item.url().toLocalFile() )  )
        {
	    thr.fileList<<audioFiles::audioFile( item.url().toLocalFile() ); 
        }
    }
    if(thr.iter==thr.fileList.end() )
    {
	thr.iter=thr.fileList.begin();
    }
    thr.start();
}


int myFileSystemModel::infoC()
{
    return DIRCOLUMN;
}


Qt::ItemFlags myFileSystemModel::flags ( const QModelIndex & index ) const
{
    return KDirModel::flags(index) | Qt::ItemIsSelectable |Qt::ItemIsDragEnabled;
}

KUrl myFileSystemModel::url( int row) const
{
    QModelIndex i=index(row,0);

    return  itemForIndex(i).url();

}
