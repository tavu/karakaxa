#ifndef FOLDEREDIOTRFACTORY_H
#define FOLDEREDIOTRFACTORY_H

#include<QSortFilterProxyModel>
#include<views.h>
#include<QThread>
#include<core.h>

class folderEditorFactory :public views::tagEditorFactory
{
    Q_OBJECT
    public:
	folderEditorFactory(QObject *parent) :tagEditorFactory(parent){}
	int tagFromColumn(int column) const
	{
	    return column-7;
	}
	
	int columnFromTag(int tag) const
	{
	    return tag+7;
	}
	
	int tagFromIndex(const QModelIndex &index) const
	{	  
	   QModelIndex in=model->mapToSource(index);
	   if(!core::isAudio(in.data(URL_ROLE).toUrl().toLocalFile() ) )
	   {
		  return -1;
	   }
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
	
	
    private:
	  	   
	   QAbstractItemView *view;
	   QSortFilterProxyModel *model;
	   
    protected slots:
	   void done();
};
#endif