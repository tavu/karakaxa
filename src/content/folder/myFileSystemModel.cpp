#include"myFileSystemModel.h"
#include<player.h>
#define DIRCOLUMN 7
using namespace player;
myFileSystemModel::myFileSystemModel(QObject *parent)
        :KDirModel(parent)
{
//     thr.iter=thr.fileList.end();
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),&thr,SLOT(cleanup() ) );
    connect(&thr,SIGNAL(finished() ),this,SLOT(changeData() ) ,Qt::QueuedConnection);
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+FRAME_NUM;
}

QVariant myFileSystemModel::data(const QModelIndex &index, int role) const
{ 
    if(role == URL_ROLE)
    {
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
//         audioFile *f=audioFile::getAudioFile(item.url().toLocalFile() );	
//         if (f==0)	return var;

        int filde=index.column()-DIRCOLUMN;
	
        var=f.tag(filde, audioFile::ONCACHE|audioFile::ONDATAB );	
	
// 	if(filde==RATING)
// 	{
// 	    if(var.isNull() )
// 	    {
// // 		return f->tag(RATING);
// 	    }
// 	}
	return player::pretyTag(var,filde);
	
    }        
    
    return QVariant();

}

QVariant myFileSystemModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if (section<DIRCOLUMN)
    {
        return KDirModel::headerData(section,orientation,role);
    }

    if (role ==Qt::DisplayRole)
    {
        return player::tagName( (tagsEnum)(section-DIRCOLUMN) );
    }    
    return QVariant();
}

void myFileSystemModel::insert(const KFileItemList &items)
{	
    thr.cancel();
    foreach(KFileItem item , items)
    {
        if (!item.isDir())
        {
// 	    files<<audioFile(item.url().toLocalFile() );
//             fileList<<item.url().toLocalFile();
            thr.fileList<<audioFile(item.url().toLocalFile() );
// 	    audioFile *f=audioFile::getAudioFile(item.url().toLocalFile());
        }
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

void myFileSystemModel::changeData()
{
    QModelIndex start=index(0, DIRCOLUMN );
    QModelIndex end=index(rowCount()-1,DIRCOLUMN+FRAME_NUM-1);
    //we emit that signal as the thread have finished and the data have been updated
    //we don't soure whitch data have changed so we include all data
    emit dataChanged(start,end);
}

