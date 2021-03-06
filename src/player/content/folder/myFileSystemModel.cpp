#include"myFileSystemModel.h"
#include<views.h>
#include <kio/jobclasses.h>
#include <kio/copyjob.h>
#include"playlist/filePlaylist.h"
#define DIRCOLUMN 7
#include<Basic/func.h>


using namespace core;
myFileSystemModel::myFileSystemModel(QWidget *parent)
        :KDirModel(parent)
{
    setDropsAllowed(DropOnDirectory );
    dirL=KDirModel::dirLister();
    connect(dirL,SIGNAL(newItems(const KFileItemList &) ),this,SLOT(insert(const KFileItemList &) ) );
    connect(dirL,SIGNAL(clear() ),&thr,SLOT(cleanup() ) );
    connect(&thr,SIGNAL(finished () ),this,SLOT( callReset() ) );
}

void myFileSystemModel::callReset()
{
    beginResetModel ();
    endResetModel();
}

void myFileSystemModel::updateLibrary()
{

}


bool myFileSystemModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{

    if(!data->hasUrls() || action==Qt::IgnoreAction )
    {
        return false;
    }

    KUrl dest;
    if(parent.isValid() )
    {
        dest=itemForIndex(parent).url();
    }
    else
    {
        dest=dirLister()->url();
    }

    if(Basic::isPlaylist(dest.toLocalFile() ) )
    {
        core::nplList list;
        foreach(QUrl u,data->urls())
        {
            nplPointer p=core::nplTrack::getNplTrack(u);
            if( !p.isNull() )
            {
                list<<p;
            }
        }
        filePlaylist *pl=getPlaylist(dest.toLocalFile());
        pl->load();
        pl->insert(pl->size(),list);
        pl->save();
        return true;
    }
    return false;
    //TODO support drop action
#if 0
    KUrl::List urls;

    foreach(QUrl u,data->urls())
    {
        urls.append(KUrl(u) );
    }

    if(action==Qt::CopyAction)
    {
        KIO::copy(urls,dest );
    }
    else
    {
        KIO::move(urls,dest );
    }

    return true;
#endif
}


int myFileSystemModel::columnCount( const QModelIndex & parent ) const
{

    return KDirModel::columnCount(parent)+Basic::FRAME_NUM;
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

    if (role==Qt::DisplayRole || role==Qt::EditRole )
    {
        QVariant var;
        KFileItem item=itemForIndex(index);
        if (item.isDir() )	return QVariant();

        audioFile f(item.url().toLocalFile() );

        int filde=index.column()-DIRCOLUMN;

        var=f.tag(filde, audioFile::ONCACHE|audioFile::ONDATAB );

	   return views::pretyTag(var,filde);
    }
    if(role == TAG_ROLE )
    {

        return QVariant(index.column()-DIRCOLUMN );
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
        return views::tagName( section-DIRCOLUMN);
    }
    return QVariant();
}

void myFileSystemModel::insert(const KFileItemList &items)
{
    QLinkedList<audioFiles::audioFile> l;
    foreach(KFileItem item , items)
    {
        if( Basic::isAudio(item.url().toLocalFile() )  )
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
    static Qt::ItemFlags f= Qt::ItemIsEnabled | Qt::ItemIsSelectable |Qt::ItemIsDragEnabled;

    if(!index.isValid() || itemForIndex(index).isDir()||Basic::isPlaylist( url(index.row()).toLocalFile() ) )
    if(!index.isValid() ||Basic::isPlaylist( url(index.row()).toLocalFile() ) )    
    {
        return f|Qt::ItemIsDropEnabled;
    }

    int tag=index.column()-DIRCOLUMN;
    if(tag<0||tag==Basic::COUNTER||tag==Basic::LENGTH||tag==Basic::BITRATE||tag==Basic::RATING)
    {
        return f;
    }

    return f|Qt::ItemIsEditable;
}

KUrl myFileSystemModel::url( int row) const
{
    QModelIndex i=index(row,0);

    return  itemForIndex(i).url();

}

QModelIndex myFileSystemModel::parent ( const QModelIndex & ) const
{
    return QModelIndex();
}

bool myFileSystemModel::hasChildren(const QModelIndex& parent) const
{
    if(!parent.isValid())
        return true;
    
    return false;
}
