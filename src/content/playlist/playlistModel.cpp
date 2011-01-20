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
	return files.at(index.row() )->tag( (tagsEnum)index.column(),flag );
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
    
    return QVariant();
}


void playlistModel::setPlPath(const QString &s)
{    
    if(pl!=0)
    {
	terminate();
	
	int end=files.size();
	for(int i=0;i<end;i++)
	{
	    audioFile::releaseAudioFile(files.at(0));
	}	
	delete pl;
    }
        
    pl=new m3uPl(s);
  
    pl->load();
    beginResetModel();
    files=pl->files();
    endResetModel();        
    
    start();    
}

void playlistModel::run()
{

    for(int j=0;j<pl->size();j++)
    {
	for (int i=TAGS_START;i<FRAME_NUM;++i)
	{
	    files.at(j)->tag( (tagsEnum)i);
	}
    }    
}

KUrl playlistModel::url(int row) const
{
    if(row>=files.size() )
    {
	return KUrl();
    }
    
    return KUrl(files.at(row)->getPath() );
}

Qt::ItemFlags playlistModel::flags(const QModelIndex &index) const
{

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    }

    return Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

