#include"playlistItem.h"
#include"items.h"
#include<KIcon>
#include<views.h>
#include<libraryFolder.h>
using namespace core;
playlistFolder::playlistFolder(const QString& name) 
  :standardItem(),
  childrenFlag(false)
{
    connect(database::db(),SIGNAL(newEvent(database::dbEventP)),this,SLOT(dbEvent(database::dbEventP)));
}

void playlistFolder::dbEvent(database::dbEventP e)
{
    using namespace database;

    if(canFetchMore() )//not loaded at all
    {
        return ;
    }
    
    if(e->type()==database::NEW_PL)
    {
        QList< standardItem* > items;
        foreach(QString s,e->urls)
        {
            playlistItem *item=new playlistItem(s);
            items<<item;
        }
        insertRows(rowCount() ,items);
    }
    if(e->type()==database::PL_REM)
    {
        for(int i=0;i<rowCount();i++)
        {
            standardItem *item=child(i);
            QString s=item->data(URL_ROLE).toString();
            if(e->urls.contains(s) )
            {
                removeRow(i);
            }
        }
    }
    if(e->type()==RESCAN_COMP||e->type()==UPDATE_COMP||e->type()==NEW_CONN)
    {
        clear();
    }
}


QVariant playlistFolder::data(int column, int role) const
{
    if(role==Qt::DisplayRole)
    {
        return QVariant(tr("playlists") );
    }
    if(role==Qt::DecorationRole)
    {
        return QVariant( KIcon("folder") );
    }
    if(role==Qt::SizeHintRole)
    {
      	if(sizeHint.isEmpty() )
        {
            return QVariant();
        }
        return sizeHint;
    }
    return QVariant();
}

int playlistFolder::columnCount() const
{
    return 1;
}


bool playlistFolder::hasChildren() const
{
    if(!childrenFlag)
    {
        return true;
    }
    return standardItem::hasChildren();
}

bool playlistFolder::canFetchMore() const
{
    if(!childrenFlag)
    {
        return true;
    }
    return false;
}

void playlistFolder::fetchMore()
{
     database::libraryFolder  lf;
     QStringList l=lf.playLists();
     QList< standardItem* > items;
     
     foreach(QString s,l)
     {
        playlistItem *item=new playlistItem(s);
        items<<item;
     }
     insertRows(0,items);
     childrenFlag=true;
}

int playlistFolder::type() const
{
    return PLAYLIST_FOLDER;
}

// 

playlistItem::playlistItem(const QString &p)
  :standardItem(),
  path(p)  
{
    name=Basic::titleFromPath(p);
}

int playlistItem::type() const
{
    return PLAYLIST_ITEM;
}

QVariant playlistItem::data(int column, int role ) const
{        
    if(column!=0)
    {
        return QVariant();
    }
     
    if(role==Qt::DisplayRole)
    {
        return QVariant(name);
    }
    if(role==ITEM_ROLE|| role==URL_ROLE)
    {
        return QVariant(path);
    }
    if(role==Qt::DecorationRole)
    {
        return views::decor->playListIcon();
    }

    return QVariant();
}

int playlistItem::columnCount() const
{
  return 1;
}



