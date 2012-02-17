#include"filePlaylistModel.h"
#include"../../core/nowPlayList/nplFile.h"
#include"../../core/status/playerStatus.h"
#include<QObject>
views::filePlaylistModel::filePlaylistModel(QObject *parent)
    :playlistModel(parent)
{
   thr=new playlistThr(this);
   connect(thr,SIGNAL(finished()),this,SLOT(updateData() ) );
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

    playlistModel::setPlaylist(playlist);
    thr->pl=pl;
    connect(pl,SIGNAL(tracksInserted(int,int)),this,SLOT(updateData(int,int)) );
    fpl->load();
}


void views::filePlaylistModel::updateData(int row, int num)
{
    thr->wait();
    thr->row=row;
    thr->num=num;
    thr->canceled=false;
    thr->start();
}

void views::filePlaylistModel::playlistThr::run()
{
     using namespace core;
    
     for(int i=0;i<num && !canceled; i++)
     {
         nplPointer p=pl->item(row+i);
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