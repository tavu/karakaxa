#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include<QAbstractListModel>
#include<core.h>
#include<QThread>
// #include"../trackUrl.h"
using namespace core;
class playlistModel :public  QAbstractListModel
{      
    Q_OBJECT
    public:
	playlistModel(QObject* parent = 0);
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	void setPlPath(const QString &s);
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	void contextMenuEvent(QContextMenuEvent *e);
	
// 	virtual KUrl url(int row) const;
	virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
	
	
    public slots:
	void updateData();

    private:
	core::m3uPlaylist *pl;
	

  class playlistThr :public QThread
  {
      public:
	  playlistThr(QObject * parent = 0)
	    :QThread(parent)
	  {}
	  
	  void run();
	  mutable QList<audioFiles::audioFile> files;
  };

  playlistThr *thr;
};
#endif