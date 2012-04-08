#ifndef MYSTANDARDMODEL_H 
#define MYSTANDARDMODEL_H

#include<QStandardItemModel>
#include<QDomElement>
#include<QDebug>

/*
  this is a model representation whitch every item represent a multiple columns row.
*/
class standardModel;

class standardItem :public QObject
{
    Q_OBJECT    
    friend class standardModel;
//     friend void  insert(int row, standardItem* item);
    public:      
      standardItem();
      
      //saves the state of this item including the state of each childre.
      //by default does nothing.
      virtual bool save();
            
      //return true if this item canFetchMore. by default return false
      virtual bool canFetchMore () const;      
      virtual void fetchMore ();
      
      /*Return true if this item has children.
       *The item could have no children but this function it is posible
       *to return true if the item can fetch more children
      */
      virtual bool hasChildren () const;
      
      //remove the child row at position int. if the removal was succefull return true;
      virtual bool removeRow(int row);
      virtual bool removeRows(int row ,int count);
      
      standardItem* takeRow(int row) ;
      
      //insert  row(s) at position row
      virtual bool insertRows ( int row, const QList< standardItem* >& items );                  
      virtual bool insertRow ( int row, standardItem * item );
      virtual bool appendRow ( standardItem * item );

      virtual void clear();
      //return the row of the item
      int row() const;
      
      //return the numbers of the columns
      virtual int columnCount() const=0;
      
      //return the numbers of the children;
      virtual int rowCount() const;
      
      standardItem* parent() const;
            
      virtual bool operator<( const standardItem& other ) const;
            
      virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const = 0;
      virtual bool setData (const QVariant &value,int column, int role );

      //return a type indentifier of the item
      virtual int type() const;
      
      virtual Qt::ItemFlags flags ( int column) const;
      
      standardModel* model() const;
      
      standardItem* child (int row ) const;

      //if you set that item as a header item the header data of the model will shown according to that function.
      virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

      //the type of the default item
      static const int StandardType;
      
      //pass this role to the data function to get the type
      static const int typeRole;
      
    protected:
      void prealocateChildren(int n);
      int freeChildrenSpace()
      {
        return children.capacity()-children.size();
      }
      
      void squeezeChildren()
      {
	  children.squeeze();
      }
      
      
      void insert(int row,standardItem *item);
      
      QVector<standardItem *>children;
      standardModel *_model;
      
      void beginInsertColumns( int first, int last);
      void endInsertColumns();
      void dataChanged ( const int first, const int last);
      void dataChanged ( const int column)
      {
	  dataChanged(column,column);
      }
      
      inline void beginRemoveRows(int first, int last );
      
      inline void endRemoveRows();
      
      void beginInsertRows(int start,int end);
      
      void endInsertRows();
      
      
    private:	
	int _row;
	standardItem *_parent;
      
};



class standardModel :public QAbstractItemModel
{
//     Q_OBJECT
    friend class standardItem;
    
    public:
	standardModel(QObject * parent = 0 );
	virtual ~standardModel();

	virtual bool canFetchMore ( const QModelIndex & parent ) const;
	virtual void fetchMore ( const QModelIndex & parent ) ;
	virtual bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
// 	virtual standardItem* head(QModelIndex index) const;
	virtual bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
	virtual bool removeRow ( int row, const QModelIndex & parent = QModelIndex() );
	virtual bool removeRow ( standardItem *item );		
		
	virtual bool insertRow ( int row, standardItem* item, const QModelIndex& parent = QModelIndex() );
	virtual bool insertRows ( int row, const QList< standardItem* >& items, const QModelIndex& parent );
	virtual bool appendRow ( standardItem* item, const QModelIndex& parent = QModelIndex() );
  	
	virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const; 

	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
	{
	    return head->headerData(section,orientation,role);
	}
	
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;
	
	bool setData (const QModelIndex& index, const QVariant& value, int role );
	
	void setHeadItem(standardItem *h);
	
	standardItem* headItem()
	{
	    return head;
	}
	
	virtual int rowCount(const QModelIndex& index=QModelIndex()) const;
	virtual int columnCount(const QModelIndex& index=QModelIndex() ) const;
	
	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	
	standardItem* itemFromIndex(const QModelIndex &index) const;
	QModelIndex indexFromItem(const standardItem *item,int column) const;
	QModelIndex parent ( const QModelIndex & index ) const;		
	
// 	void refresh()
// 	{
// 	    emit layoutAboutToBeChanged () ;
// 	    emit layoutChanged ();
// 	}
// 	
    private:
        void emitDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
	
	
        class defaultHeadItem :public standardItem
        {
        public:
            int columnCount() const
            {
                return 1;
            }

            QVariant data (int column, int role = Qt::UserRole + 1 ) const
            {
                Q_UNUSED(column)
                Q_UNUSED(role)
                return QVariant();
            }
        };

        standardItem *head;
};



#endif
