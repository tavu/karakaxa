#include"playlistModel.h"

playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
     QThread(parent),
    pl(0)
{
    
}

int playlistModel::rowCount ( const QModelIndex & parent ) const
{
    return files.size();
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
    
    static int flag=audioFile::DBCACHE|audioFile::ONCACHE|audioFile::TITLEFP;
    
    if( role == Qt::DisplayRole)
    {      
	QVariant var=files.at(index.row() )->tag( (tagsEnum)index.column(),flag );
	return player::pretyTag(var,(tagsEnum)index.column() );
	
    }    
    else if(role==URL_ROLE)
    {
	KUrl u(files.at(index.row() )->getPath() );
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
	return player::tagName((tagsEnum) section);
    }
    if(role==Qt::DecorationRole)
    {
	return decor.tagIcon(section);
    }
    
    return QVariant();
}


void playlistModel::setPlPath(const QString &s)
{    
    if(pl!=0)
    {
 	terminate();
 	beginResetModel();
 	int end=files.size();
 	for(int i=0;i<end;i++)
 	{
 	    audioFile::releaseAudioFile(files.at(i));
 	}	
 	delete pl;
     }
     else
     {
	beginResetModel();
     }
        
    pl=new m3uPl(s);
  
    pl->load();
    beginResetModel();
    files=pl->files();
    qDebug()<<files.size();
    endResetModel();        
    
    if(pl->size()>files.size() )
    {
	statusBar.showMessage(QObject::tr("Some media coud not be shown"));
    }
    else if(files.isEmpty() )
    {
	statusBar.showMessage(QObject::tr("Empty playlist"));
    }
    
    start();
}

void playlistModel::run()
{
 
     for(int j=0;j<files.size();j++)
     {
 	for (int i=TAGS_START;i<FRAME_NUM;++i)
 	{
 	    files.at(j)->tag( (tagsEnum)i);
 	}
     }    
}

KUrl playlistModel::url(int row) const
{
    qDebug()<<"row "<<row;
    if(row>=files.size() ||row<0 )
    {
 	return KUrl();
    }
    KUrl u=KUrl(files.at(row)->getPath() );
    qDebug()<<u;
    return u;
}

Qt::ItemFlags playlistModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

