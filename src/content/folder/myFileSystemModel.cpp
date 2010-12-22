#include"myFileSystemModel.h"
#include<player.h>
#define DIRCOLUMN 7
using namespace player;
myFileSystemModel::myFileSystemModel(QObject *parent)
        :KDirModel(parent),        
        trackUrl()
{
    thr.iter=thr.fileList.end();
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),&thr,SLOT(cleanup() ) );
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+FRAME_NUM;
}

QVariant myFileSystemModel::data(const QModelIndex &index, int role) const
{  
    if(role==Qt::SizeHintRole)
    {
	return QVariant();
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

        audioFile *f=audioFile::getAudioFile(item.url().toLocalFile() );
	qDebug()<<"eeeeeeeeeeeeeeeeeeeeeeeee";
        if (f==0)	return var;

        int filde=index.column()-DIRCOLUMN;
	
        var=f->tag((tagsEnum)filde, audioFile::ONCACHE|audioFile::DBCACHE );	
	
	if(filde==RATING)
	{
	    if(var.isNull() )
	    {
// 		return f->tag(RATING);
	    }
	}
 	audioFile::releaseAudioFile(f);
	
        if (filde==LENGTH)
        {
            return prettyLength(var.toInt());
        }
        
        return var;
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
   qDebug()<<"AAAAAAAAAAAAAAAAAA";
    foreach(KFileItem item , items)
    {
        if (!item.isDir())
        {
            
            thr.fileList<<item.url().toLocalFile();
	    audioFile *f=audioFile::getAudioFile(item.url().toLocalFile());
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
