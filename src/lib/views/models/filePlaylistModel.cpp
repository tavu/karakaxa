#include"filePlaylistModel.h"
#include"../../core/nowPlayList/nplFile.h"
#include<Basic/status.h>
#include<QObject>
views::filePlaylistModel::filePlaylistModel(QObject *parent)
    :playlistModel(parent)
{
   thr=new playlistThr(this);
   connect(thr,SIGNAL(finished()),this,SLOT(callUpdate() ) );
}


void views::filePlaylistModel::setPlaylist(core::playlist* playlist)
{    
    thr->cancel();
    thr->wait();
    core::filePlaylist *fpl=dynamic_cast<core::filePlaylist*>(playlist);
    if(fpl==0)
    {
        playlistModel::setPlaylist(0);
        return ;
    }

    fpl->load();
    playlistModel::setPlaylist(playlist);    
    
    thr->pl=pl;
    thr->row=0;
    thr->num=pl->size();
    thr->canceled=false;
    thr->start();
//     connect(pl,SIGNAL(tracksInserted(int,int)),this,SLOT(updateData(int,int)) );
    
}


void views::filePlaylistModel::updateData(int row, int num)
{
    thr->wait();
    thr->row=row;
    thr->num=num;
    thr->canceled=false;
    thr->start();
}

void views::filePlaylistModel::callUpdate()
{
    QModelIndex topLeft ,bottomRight;
    topLeft=index(0,0);
    bottomRight=index(rowCount()-1,columnCount()-1 );

    emit dataChanged(topLeft,bottomRight);
}

void views::filePlaylistModel::playlistThr::run()
{
     using namespace core;
    
     for(int i=0;i<num && !canceled; i++)
     {
         nplPointer p=pl->item(row+i);
         if(p.isNull() )
         {
             Basic::msg()->error(QObject::tr("Some media coud not be shown"));
         }
         else if( p->type()==NPLAUDIOFILE)
         {
            nplFile *f=static_cast< nplFile*>(p.data());
            f->getAudioFile()->load();
         }
     }
}