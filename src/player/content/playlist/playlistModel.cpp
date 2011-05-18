#include"playlistModel.h"
#include<views.h>
playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
    pl(0)
{
    thr=new playlistThr(this);
    connect(thr,SIGNAL(finished()),this,SLOT(updateData() ) );
}

int playlistModel::rowCount ( const QModelIndex & parent ) const
{
    return thr->files.size();
}

int playlistModel::columnCount ( const QModelIndex & parent ) const
{
    return FRAME_NUM;
}

QVariant playlistModel::data(const QModelIndex & index, int role ) const
{    
    if(!index.isValid() )
    {
	return QVariant();
    }
    
    static int flag=audioFile::ONDATAB|audioFile::ONCACHE|audioFile::TITLEFP;
    
    if( role == Qt::DisplayRole)
    {      
//       QVariant var;
// 	audioFile f(files[ (index.row() ) ].path());
  	QVariant var=thr->files[ (index.row() ) ].tag( index.column(),flag );
	return views::pretyTag(var,(tagsEnum)index.column() );
	
    }    
    else if(role==URL_ROLE)
    {
	KUrl u(thr->files.at(index.row() ).path() );
	return QVariant(u);
    }
    
    return QVariant();    
}

QVariant playlistModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Vertical)
    {
	return QVariant();
    }
    if(role==Qt::DisplayRole)
    {
	return views::tagName(section);
    }
    if(role==Qt::DecorationRole)
    {
	return views::decor->tagIcon(section);
    }
    
    return QVariant();
}


void playlistModel::setPlPath(const QString &s)
{    
    if(pl!=0)
    {
 	thr->terminate();
 	beginResetModel();
	thr->files.clear();	
 	delete pl;
     }
     else
     {
	beginResetModel();
     }
        
    pl=new m3uPlaylist(s);
  
    pl->load();
    
    for(int i=0;i<pl->size();i++)
    {
	if(core::exists(pl->item(i)) )
	{
// 	    audioFile f=audioFile(pl->item(i);
	    thr->files<<audioFile(pl->item(i) ); 
	}	
    }
    endResetModel();        
    
    if(pl->size()>thr->files.size() )
    {
	status->addError(QObject::tr("Some media coud not be shown"));
    }
    else if(thr->files.isEmpty() )
    {
	status->addError(QObject::tr("Empty playlist"));
    }
    
    thr->start();
}

void playlistModel::playlistThr::run()
{
     for(int i=0;i<files.size();i++)
     {
 	files[i].load();
     }    
}

Qt::ItemFlags playlistModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

void playlistModel::updateData()
{
    QModelIndex topLeft ,bottomRight;
    topLeft=index(0,0);
    bottomRight=index(rowCount()-1,columnCount()-1 );
//     qDebug()<<topLeft;
//     qDebug()<<bottomRight;
    emit dataChanged(topLeft,bottomRight);
}
