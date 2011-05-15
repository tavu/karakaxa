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
	  xmlItem(QDomDocument &doc,const QString &tagName);
	  xmlItem(const QDomElement &el);
	  xmlItem();
	  
	  
	  
	  QString tagName() const;
      
      
	  virtual int  columnCount() const
	  {
	      return columns.size();
	  }
	  virtual bool removeRow(int row);
	  virtual bool removeRows(int row ,int count);
      
	  virtual bool insertRows ( int row, const QList< standardItem* >& items );
	  virtual bool insertRow ( int row, standardItem* item );
	  
// 	  bool appendRow(standardItem* item);

	  virtual QDomElement xml() const;
          virtual bool insertColumns(int start,const QStringList &list);
            
	  virtual QVariant data ( int column,int role = Qt::UserRole + 1 ) const;
      
	  virtual int type();
	  
	  //map a specific attribute name to a spesific column
	  virtual bool setData (const QVariant& value, int column, int role = Qt::EditRole );
	  
	  virtual bool setTagName(const QString &name);
	  
	  int attributeRole()
	  {
	      return _attributeRole;
	  }
	  
	  void setAttributeRole(int role)
	  {
	      _attributeRole=role;
	  }
	  
	  void setXml(const QDomElement &el)
	  {
	      element=el;
	  }
	  
	  QDomDocument document()
	  {
	      return element.ownerDocument();
	  }
	  
	  
	  static const int XmlType;
	  static const int tagNameRole;
	  static const int attributeName;
	  
      protected:
	  
	  QVector<QString> columns;
	  QDomElement element;
	  int _attributeRole;
	  bool insertRowWithNoElement( int row, standardItem* item );
  };
  
};


#endif