#ifndef FOLDEREDIOTRFACTORY_H
#define FOLDEREDIOTRFACTORY_H

#include<QSortFilterProxyModel>
#include<views.h>
#include<QThread>

class folderEditorFactory :public views::tagEditorFactory
{
    Q_OBJECT
    public:
	folderEditorFactory(QObject *parent) :tagEditorFactory(parent){}
	int tagFromColumn(int column) const
	{
// 	    qDebug()<<"COL "<<column-7;
	    return column-7;
	}
	
	int columnFromTag(int tag) const
	{
	    return tag+7;
	}
	
	int tagFromIndex(const QModelIndex &index) const
	{	  
	   QModelIndex in=model->mapToSource(index);	   
	   return tagFromColumn(in.column() );
	}
	
	void setModel(QSortFilterProxyModel *m)
	{
	   model=m;
	}
	
	void setView(QAbstractItemView *v)
	{
	  view=v;
	}
	
	bool setModelData(views::tagEditor* editor, QAbstractItemModel* model, const QModelIndex& index, const QModelIndexList& list);
	
    private:
	  	   
	   QAbstractItemView *view;
	   QSortFilterProxyModel *model;
	   
    private slots:
	   void thrFinished();
};


class editThr :public QThread
{
    public:
	   editThr(int tag,QVariant value,const QLinkedList<audioFiles::audioFile> &l,QObject* parent = 0) :QThread(parent) 
	   {
		fileList=l;
		this->tag=tag;
		this->value=value;
	   };
	   
    protected:
	   void run();
	   int tag;
	   QVariant value;
	   QLinkedList<audioFiles::audioFile> fileList;
	   
};


#endif