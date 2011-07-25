#ifndef MYFILESYSTEMMODEL_H
#define MYFILESYSTEMMODEL_H
#include<KDirModel>
#include <QFileSystemModel>
#include<KDirLister>
#include<core.h>
#include<QThread>
#include<QLinkedList>
#include"loadInfoThr.h"

#define DIRCOLUMN 7
class myFileSystemModel :public KDirModel
{    
    Q_OBJECT
    public:
	myFileSystemModel(QObject *parent=0);
	int columnCount( const QModelIndex & parent=QModelIndex() ) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData( const QModelIndex & index, const QVariant & value, int role);	
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const ;
	void updateTrack(audioFile *f);
	int infoC();
	
	int tag(const QModelIndex &index)
	{
	   return index.column()-DIRCOLUMN;
	}

	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	KUrl url( int row) const;

    private:
	
	KDirLister *dirL;
	loadInfoThr thr;

    private slots:
	void insert(const KFileItemList &items);
	void callRest();
	
      signals:
	void updated();	
};
#endif
