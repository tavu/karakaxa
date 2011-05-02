#ifndef ABSTRACTPLAYLIST_H
#define ABSTRACTPLAYLIST_H
#include<QString>
#include"../nowPlayList/nplTrack.h"
/*
    this is an abstract interface for playlists
*/
namespace core
{
  
class abstractPlaylist
{      
    public:
      
        static const int OK=0;
	static const int FILENOTFOUND=1;
	static const int CANTOPENFILE=2;
	
	//insert an item having the path u at position pos
	virtual void insert(int pos,QString u)=0;
	//remove the item from position pos.
	virtual void remove(int pos)=0;	
	//move the item from position 'from' to position 'to'
	virtual void move(int frot,int to)=0;
	//return the path of the item at position pos
	virtual QString item(int pos) const=0;
	virtual QStringList urls() const=0;
	
	
	virtual int size() const=0;
	virtual QString path() const=0;
	
	virtual bool load()=0;
	virtual bool save()=0;
	virtual int  error() const=0;
	
// 	virtual nplTrack;
};

    core::abstractPlaylist* getPlaylist(const QString &url);
};
#endif