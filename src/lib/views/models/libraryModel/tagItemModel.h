#ifndef TAG_ITEM_MODEL_H 
#define TAG_ITEM_MODEL_H
#include <QAbstractItemModel>
#include<QList>
#include"tagItem.h"
#include"audioFile.h"
namespace views
{

class tagItemModel :public QAbstractItemModel
{
	Q_OBJECT
	public:
		tagItemModel(QObject * parent = 0);
		~tagItemModel();
		int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
		int columnCount ( const QModelIndex & index = QModelIndex() ) const;
		
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;
		QVariant data ( const QModelIndex & parent, int role = Qt::DisplayRole ) const;
		QVariant fileData ( audioFiles::audioFile  &f,int column, int role = Qt::DisplayRole ) const;
		
		QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
		QModelIndex parent ( const QModelIndex & index ) const;
		
		bool canFetchMore ( const QModelIndex & parent ) const;
		void fetchMore ( const QModelIndex & parent );
		bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
	
	private:
		tagItem* head;
		QList<int> _tags;
		
		tagItem*  itemFromIndex(const QModelIndex & index ) const
		{
			if(!index.isValid())
			{
				return head;
			}
			return static_cast<tagItem*>(index.internalPointer() );
		}
		
		int nextItemType(tagItem* item) const;
		
	private slots:
		void updateData(int);

};

};
#endif
