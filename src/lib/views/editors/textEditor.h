#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QLineEdit>
#include "tagEditor.h"
#include <QHBoxLayout>
#include <QVariant>
#include"../core.h"
#include <QStringListModel>
namespace views
{

class textEditor :public tagEditor
{
   Q_OBJECT
    
    public:
	textEditor(int tag,QWidget *parent=0);

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
	 core::tagQueryGrt  *q;
	 core::queryGrt::tagQuery tagQ;
	  
	 QCompleter *comp;
	 	 
	 QStringListModel completerM;
	 
    private slots:
	
	 void valueChanger()
	 {
		QVariant v(edit->text() );
		emit valueChanged(v);
	 }
	 
	 void textChanged(const QString &text);
      
    
};

};
#endif