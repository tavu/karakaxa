#include"nplaylistModel.h"
#include<QList>
#include<QUrl>
#include<QMimeData>
#include<QStringList>
#include<KIcon>
#include"nowPlayList/nplaylist.h"
#include"views.h"

// #include "myUrl.h"
using namespace core;
using namespace views;


nplModel::nplModel( QObject * parent)
        :playlistModel(parent)
{
    setPlaylist(npList);
}


bool nplModel::dropMimeData ( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(column);

    if(!data->hasUrls() )
    {
        return false;
    }

    if (views::reorderL.size()==0 )
    {
        npList->addMediaList( data->urls(),row );
    }
    else
    {
         reorder(row,views::reorderL);
    }
    
    return true;
}

/*
void nplModel::reorder(int r)
{
    std::set<int>::const_iterator it=views::reorderL.begin();

    int n=0;
    int k=0;
    for(;it!=views::reorderL.end();it++)
    {
	   if(*it<r )
	   {
		  npList->move(*it-n,r-1);
		  n++;
	   }
	   else
	   {
		  npList->move(*it,r+k);
		  k++;
	   }
    }
}

*/