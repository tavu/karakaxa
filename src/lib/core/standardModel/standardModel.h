#ifndef MYSTANDARDMODEL_H 
#define MYSTANDARDMODEL_H

#include<QStandardItemModel>
#include<QDomElement>

/*
  this is a model representation whitch every item represent a multiple columns row.
*/
class standardModel;

class standardItem :public QObject
{
    Q_OBJECT    
    friend class standardModel;
    friend class standardItem;
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
      
      //insert  row(s) at position row
      virtual bool insertRows ( int row, const QList< standardItem* >& items ) ;
      virtual bool insertRow ( int row, standardItem * item ) ;

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
      
      standardModel* model() const;
      
      standardItem* child (int row ) const;


      //the type of the default item
      static const int StandardType;;
      
      //pass this role to the data function to get the type
      static const int typeRole; 
      
    protected:      
      QList<standardItem *>children;
      standardModel *_model;
      void beginInsertColumns( int first, int last);
      void endInsertColumns();
      
    private:
	void insert(int row,standardItem *item);
	int _row;
	standardItem *_parent;
      
};

/*this is an abstact class.
 * the myStandardModel has head item of headItem class as top level items.
 * every modelIndex or qstandarditem belongs to a head item.
 * the head items are responsible for their children the model is as simpliest as posible.
 * that makes easy to have very diferent behavior on the same model for diferent items tha belongs to diferent heads
 */



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
	virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const; 
	
	standardItem* itemFromIndex(const QModelIndex &index) const;
	QModelIndex indexFromItem(const standardItem *item,int column) const;
	QModelIndex parent ( const QModelIndex & index ) const;
	
    private:
	standardItem *head;
};


#endif
