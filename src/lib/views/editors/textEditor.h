#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QLineEdit>
#include "tagEditor.h"
#include <QHBoxLayout>
#include <QVariant>

namespace views
{

class textEditor :public tagEditor
{
   Q_OBJECT
    
    public:
	textEditor(int tag,QWidget *parent=0)
	:tagEditor(tag,parent)
	{
	    edit=new QLineEdit(this);
	    QHBoxLayout *l=new QHBoxLayout(this);
	    
	    l->addWidget(edit);
	    
	    connect(edit,SIGNAL(editingFinished()),this,SLOT(valueChanger()) );
	}
	
	void setValue(const QVariant &v)
	{
	    edit->setText(v.toString() );
	}
	
	QVariant value()
	{
	    return QVariant( edit->text() );
	}
	
    private:
      
	QLineEdit *edit;

    private slots:
	
	void valueChanger()
	{
	    QVariant v(edit->text() );
	    emit valueChanged(v);
	}
      
    
};

};
#endif