#include"pathEditor.h"
#include<QHBoxLayout>
#define CHAR_LIMIT 3

views::pathEditor::pathEditor(int tag,QWidget *parent)
  :tagEditor(tag,parent)
{
  edit=new QLineEdit(this);
  edit->setReadOnly(true);
  QHBoxLayout *l=new QHBoxLayout(this);  
  l->addWidget(edit);
  l->setContentsMargins(0,0,0,0);
}

 
views::pathEditor::pathEditor(QWidget *parent)
  :tagEditor(PATH,parent)
{
  edit=new QLineEdit(this);
  QHBoxLayout *l=new QHBoxLayout(this);  
  l->addWidget(edit);
  l->setContentsMargins(0,0,0,0);
}