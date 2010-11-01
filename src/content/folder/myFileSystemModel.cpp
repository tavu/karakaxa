#include"myFileSystemModel.h"
#include<player.h>
#define DIRCOLUMN 7
using namespace player;
myFileSystemModel::myFileSystemModel(QObject *parent)
        :KDirModel(parent),
        trackUrl()
{
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),this,SLOT(cleanup() ) );
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+FRAME_NUM;
}

QVariant myFileSystemModel::data(const QModelIndex &index, int role) const
{

    if (index.column()<DIRCOLUMN)
    {
        return KDirModel::data(index,role);
    }

    if (role==Qt::DisplayRole)
    {
        KFileItem item=itemForIndex(index);
        if (item.isDir() )	return QVariant();

        audioFile *f=audioFile::getAudioFile(item.url().toLocalFile() );

        if (f==0)	return QVariant();

        int filde=index.column()-DIRCOLUMN;

        if (!f->onCache((player::tagsEnum)filde) )
        {
            return QVariant();
        }
        QVariant var=f->tag( (player::tagsEnum)filde);

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
    foreach(KFileItem item , items)
    {
        if (!item.isDir())
        {
            audioFile *f=audioFile::getAudioFile(item.url().toLocalFile() );
            if (f!=0)
            {
                fileList<<item.url().toLocalFile();
                updateTrack(f);
            }
        }
    }
}

void myFileSystemModel::updateTrack(audioFile *f)
{
    for (int i=TAGS_START;i<FRAME_NUM;++i)
    {
        f->tag( (tagsEnum)i);
    }
}

int myFileSystemModel::infoC()
{
    return DIRCOLUMN;
}

void myFileSystemModel::cleanup()
{
    foreach(QString s, fileList)
    {
        audioFile::releaseAudioFile(s);
    }
    fileList.clear();
}

Qt::ItemFlags myFileSystemModel::flags ( const QModelIndex & index ) const
{
//       return KDirModel::flags(index);
    return KDirModel::flags(index) | Qt::ItemIsSelectable |Qt::ItemIsDragEnabled;
}

KUrl myFileSystemModel::url( int row) const
{
    QModelIndex i=index(row,0);

    return  itemForIndex(i).url();

}
