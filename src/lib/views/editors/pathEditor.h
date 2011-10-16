#ifndef PATHEDITOR_H
#define PATHEDITOR_H

#include <QLineEdit>
#include "tagEditor.h"
#include <QVariant>
#include"../core.h"
namespace views
{

class pathEditor :public tagEditor
{
    public:
	pathEditor(int tag,QWidget *parent=0);
	pathEditor(QWidget *parent=0);
	
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
};

};
#endif