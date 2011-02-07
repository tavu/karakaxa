#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include<QAbstractListModel>
#include<player.h>
#include<QThread>
#include"../trackUrl.h"
using namespace player;
class playlistModel :public  QAbstractListModel,  QThread
{      
    public:
	playlistModel(QObject* parent = 0);
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	void setPlPath(const QString &s);
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	void contextMenuEvent(QContextMenuEvent *e);
	
	virtual KUrl url(int row) const;
	virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
	
	void run();

// 	QString plPath(const QString &s)
//  	{
//  	    if(pl==0)	return QString();
//  	    
//  	    return pl->path();
//  	}
	
    private:
	player::m3uPl *pl;
	QList<audioFile*> files;
	
// 	void run();
	  
};
#endif