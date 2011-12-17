#include"playlistModel.h"
#include<views.h>
#include<core.h>
playlistModel::playlistModel(QObject *parent)
    :QAbstractListModel(parent),
    pl(0)
{
    thr=new playlistThr(this);
    connect(thr,SIGNAL(finished()),this,SLOT(updateData() ) );
}

playlistModel::~playlistModel()
{
    thr->cancel();
    thr->wait();
    if(pl!=0)
        delete pl;
}


int playlistModel::rowCount ( const QModelIndex & parent ) const
{
    if(pl==0)
        return 0;
    
    return pl->size();
}

int playlistModel::columnCount ( const QModelIndex & parent ) const
{
    return FRAME_NUM;
}

QVariant playlistModel::data(const QModelIndex & index, int role ) const
{       
    if(!index.isValid() || pl==0)
    {
        return QVariant();
    }

    nplPointer p=pl->item(index.row());
    if(p.isNull() )
    {
        return QVariant();
    }
    
    if( role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant var=p->tag(index.column());
        return views::pretyTag(var,(tagsEnum)index.column() );
    }
    else if(role==URL_ROLE)
    {
        KUrl u(p->path() );
        return QVariant(u);
    }
    else if(role == TAG_ROLE)
    {
        return QVariant(index.column() );
    }
    return QVariant();
}

bool playlistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(pl=0)
        return false;
    
    nplPointer f=pl->item(index.row() );
    if(f->type()==NPLAUDIOFILE)	
    {			
	   audioFile file(f->path() );		
	   file.setTag(index.column(),value);
	   
	   if(file.error()==OK)
	   {
		  return true;
	   }
    }
    
    return false;
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
	   thr->cancel();
       thr->wait();
	   beginResetModel();	   
	   delete pl;
     }
     else
     {
	   beginResetModel();
     }
        
    pl=core::getPlaylist(s);
  
    pl->load();
    thr->pl=pl;
    endResetModel();        
    
    thr->canceled=false;
    thr->start();
}

void playlistModel::playlistThr::run()
{
     for(int i=0;i<pl->size() && !canceled; i++)
     {
         nplPointer p=pl->item(i);
         if(p.isNull() )
         {
             status->addError(QObject::tr("Some media coud not be shown"));
         }
         else if( p->type()==NPLAUDIOFILE)
         {
            nplFile *f=static_cast< nplFile*>(p.data());
            f->getAudioFile()->load();
         }
     }
}

Qt::ItemFlags playlistModel::flags(const QModelIndex &index) const
{
    static Qt::ItemFlags ret=Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
    if(pl==0)
    {
        return ret & ~Qt::ItemIsEnabled;
    }
    nplPointer p=pl->item(index.row() );

    if(p.isNull() || !p->isValid() )
    {
        return ret & ~Qt::ItemIsEnabled;
    }

    if (index.column()==BITRATE||index.column()==LENGTH||index.column()==COUNTER)
    {
        return ret & ~Qt::ItemIsEditable;
    }

    return ret;
}

void playlistModel::updateData()
{
    qDebug()<<"UPP";
    QModelIndex topLeft ,bottomRight;
    topLeft=index(0,0);
    bottomRight=index(rowCount()-1,columnCount()-1 );
    
    emit dataChanged(topLeft,bottomRight);
}
