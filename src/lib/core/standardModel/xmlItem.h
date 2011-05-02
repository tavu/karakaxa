#ifndef XMLITEM_H
#define XMLITEM_H
#include"standardModel.h"
#include<QDomElement>
#include<QVector>
namespace core
{
  
  class xmlItem :public standardItem
  {
    Q_OBJECT    
      public:
	  xmlItem(const QString &tagName);
	  xmlItem();	
	  
	  
	  QString tagName() const;
      
      
	  virtual int  columnCount() const
	  {
	      return columns.size();
	  }
	  virtual bool removeRow(int row);
	  virtual bool removeRows(int row ,int count);
      
	  virtual bool insertRows ( int row, const QList< core::xmlItem* >& items );
	  virtual bool insertRow ( int row, core::xmlItem* item );

	  virtual QDomElement xml() const;
          virtual void setColumnCount(int);
            
	  virtual QVariant data ( int column,int role = Qt::UserRole + 1 ) const;
      
	  virtual int type();
	  
	  //map a specific attribute name to a spesific column
	  virtual bool setData (const QVariant& value, int column = Qt::EditRole, int role = Qt::EditRole );
	  
	  int attributeRole()
	  {
	      return _attributeRole;
	  }
	  
	  void setAttributeRole(int role)
	  {
	      _attributeRole=role;
	  }
	  
	  static const int XmlType;
	  
	  
      protected:
	  
	  QVector<QString> columns;
	  QDomElement element;
	  int _attributeRole;
  };
  
};


#endif