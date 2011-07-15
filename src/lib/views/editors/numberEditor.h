#ifndef NUMBEREDITOR_H
#define NUMBEREDITOR_H

#include <QSpinBox>
#include "tagEditor.h"
#include <QHBoxLayout>
#include <QVariant>

namespace views
{

class numberEditor :public tagEditor
{
   Q_OBJECT
    
    public:
	numberEditor(int tag,QWidget *parent=0)
	:tagEditor(tag,parent)
	{
	    edit=new QSpinBox(this);
	    QHBoxLayout *l=new QHBoxLayout(this);
	    
	    l->addWidget(edit);
	    
	    connect(edit,SIGNAL(valueChanged()),this,SLOT(valueChanger()) );
	}
	
	void setValue(const QVariant &v)
	{
	    edit->setValue(v.toInt() );
	}
	
	QVariant value()
	{
	    return QVariant( edit->value() );
	}
	
    private:
      
	QSpinBox *edit;

    private slots:
	
	void valueChanger()
	{
	    QVariant v(edit->value() );
	    emit valueChanged(v);
	}
      
    
};

};
#endif