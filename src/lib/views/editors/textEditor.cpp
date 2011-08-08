#include"textEditor.h"
#include<QCompleter>
#include<QSqlTableModel>

#define CHAR_LIMIT 3

views::textEditor::textEditor(int tag,QWidget *parent)
  :tagEditor(tag,parent),
  comp(0)
{
  edit=new QLineEdit(this);
  QHBoxLayout *l=new QHBoxLayout(this);  
  l->addWidget(edit);
  l->setContentsMargins(0,0,0,0);
  setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
  
  connect(edit,SIGNAL(editingFinished()),this,SLOT(valueChanger()) );  
//   connect(edit,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)) );  
  
   if(tag==audioFiles::TITLE)
   {
	 return ;
   }
   
   q=new core::tagQueryGrt(this);
   q->setTag(tag);
   q->select();
   comp=new QCompleter(this);	
   comp->setCaseSensitivity(Qt::CaseInsensitive);	   
   comp->setCompletionColumn(0);
   
   completerM.setStringList(q->result() );   
	   
   comp->setModel(&completerM);
   edit->setCompleter(comp);

  
}

void views::textEditor::textChanged(const QString& text)
{
}
