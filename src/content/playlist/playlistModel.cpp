#include"playlistModel.h"

playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
    QThread(parent),
    pl(0),
    audio(0)
{
    
}

int playlistModel::rowCount ( const QModelIndex & parent ) const
{
    if(pl==0)	return 0;
    
    return pl->size();
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
	return audio[index.row()]->tag( (tagsEnum)index.column(),flag );
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
	
	for(int i=0;i<pl->size();i++)
	{
	    audioFile::releaseAudioFile(audio[i]);
	}	
	delete pl;
    }
    
    pl=new m3uPl(s);
    pl->load();
    
    audio=new audioFile* [ pl->size() ];
    
    for(int i=0;i<pl->size();i++)
    {
	audio[i]=audioFile::getAudioFile(pl->item(i) );
    }
    start();    
}

void playlistModel::run()
{
    for(int j=0;j<pl->size();j++)
    {
	for (int i=TAGS_START;i<FRAME_NUM;++i)
	{
	    audio[j]->tag( (tagsEnum)i);
	}
    }    
}


