#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include<QWidget>
#include<QModelIndex>
#include<QModelIndexList>
#include"editMultFiles.h"
namespace views
{

class tagEditor :public QWidget
{
    Q_OBJECT    
    public:
	
	tagEditor(int tag,QWidget *parent) :QWidget(parent)
	{
	    _tag=tag;
	}
	
	int tag() const
	{
	    return _tag;
	}
	
	virtual void setValue(const QVariant &v)=0;
	virtual QVariant value()=0;
	
    private:
	int _tag;
	
    signals:	 
	void valueChanged(QVariant);
	
    public:
	static tagEditor* getEditor(int tag,QWidget *parent=0);
};


class tagEditorFactory :public QObject
{
    Q_OBJECT
    
    public:
	tagEditorFactory(QObject *parent=0) :QObject(parent),thr(0)
	{}

	//returns the tag for that index. For error return -1.
	virtual int tagFromColumn(const int column) const=0;
	//For error return -1.
	virtual int columnFromTag(const int tag) const=0;
	//returns the appropriate aditor for that tag. the Default implementation returns tagEditor::getEditor
	virtual tagEditor* createEditor(int tag, QWidget *parent=0 ) const
	{
	    return tagEditor::getEditor(tag,parent);
	}
	
	tagEditor* createEditor(const QModelIndex &index, QWidget *parent=0 ) const
	{
	   int tag=tagFromIndex(index);
	   return createEditor(tag,parent);
	}
	
	virtual bool setModelData(tagEditor *editor,QAbstractItemModel *model,const QModelIndex &index,const QModelIndexList &list);
	
	//for error return -1
	virtual int tagFromIndex(const QModelIndex &index) const
	{
// 	    return 0;
 	    return tagFromColumn(index.column() );
	}
	
	
      protected:
	   editMultFiles::editFiles *thr;
	
      protected slots:
	
	  virtual void done()
	  {
	      if(thr!=0)
	      {
		    delete thr;
		    thr=0;
	      }
	  }
	  
};

};
#endif