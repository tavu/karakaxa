#ifndef MYSTANDARDMODEL_H 
#define MYSTANDARDMODEL_H

#include<QStandardItemModel>
#include<QDomElement>

class myStandardItem :public QStandardItem
{
    public:
      myStandardItem(const QString & text);
      myStandardItem( const QIcon &icon, const QString &text );
      myStandardItem();
      
      //saves the state of this item including the state of each childre.
      //by default does nothin.
      virtual bool save();
      
      //return true if this item canFetchMore. by default return false
      virtual bool canFetchMore () const;      
      virtual void fetchMore ();
      
      /*Return true if this item has children.
       *The item could have no children but this function it is posible
       *to return true if the item can fetch more children
      */
      virtual bool hasChildr() const;
      
      //remove the child row at position int. if the removal was succefull return true;
      virtual bool removeR(int)=0;
      
      //append a row and return true on succed
      virtual bool addRow(myStandardItem *item)=0;
      
      //returns a QDomElement with the data of the item appropriate for saving xml
      //by default return a null QDomElement
      virtual QDomElement xml() const;
      
      virtual bool operator<( const QStandardItem & other ) const;
      
};

/*this is an abstact class.
 * the myStandardModel has head item of headItem class as top level items.
 * every modelIndex or qstandarditem belongs to a head item.
 * the head items are responsible for their children the model is as simpliest as posible.
 * that makes easy to have very diferent behavior on the same model for diferent items tha belongs to diferent heads
 */



class myStandardModel :public QStandardItemModel
{
//     Q_OBJECT
    public:
	myStandardModel(QObject * parent = 0 );
	virtual ~myStandardModel();

	virtual bool canFetchMore ( const QModelIndex & parent ) const;
	virtual void fetchMore ( const QModelIndex & parent ) ;
	virtual bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
	virtual myStandardItem* head(QModelIndex index) const;
	virtual bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
};


#endif
