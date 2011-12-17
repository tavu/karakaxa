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
        static QWidget* getEditor(int tag,QWidget *parent=0);
};

};
#endif