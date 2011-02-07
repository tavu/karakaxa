#include"playlistItem.h"
#include"items.h"
#include<player.h>

playlistItem::playlistItem(const QString &p)
  :myStandardItem(),
  path(p)
{
    setText(player::titleFromPath(p));
    setIcon(KIcon("audio-x-generic") );
}

int playlistItem::type() const
{
    return PLAYLIST_ITEM;
}

bool playlistItem::removeR(int)
{
    return false;
}

bool playlistItem::addRow(myStandardItem *item)
{
    return false;
}

QVariant playlistItem::data(int role ) const
{
        
    if(role==ITEM_ROLE)
    {
	return QVariant(path);
    }
    return myStandardItem::data(role);
}


playlistFolder::playlistFolder(const QString& name) 
  :myStandardItem(name),
  childrenFlag(false)
{
    setIcon(KIcon("folder"));
}

bool playlistFolder::hasChildr() const
{
    if(!childrenFlag)
    {
	return true;
    }
    return myStandardItem::hasChildren();
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
     QSqlQuery q=db.playlists();

     while (q.next())
     {
	  playlistItem *item=new playlistItem(q.value(0).toString() );
	  appendRow(item);	  
     }
     childrenFlag=true;
}

int playlistFolder::type() const
{
    return PLAYLIST_FOLDER;
}

bool playlistFolder::addRow(myStandardItem* item)
{
    Q_UNUSED(item);
    return false;
}

bool playlistFolder::removeR(int)
{
    return false;
}


