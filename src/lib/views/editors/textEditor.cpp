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
  
   comp=new QCompleter(this);	
   comp->setCaseSensitivity(Qt::CaseInsensitive);	   
   comp->setCompletionColumn(0);
   
   completerM.setQuery(core::queryGrt::queryStringAll(tag) );   
	   
   comp->setModel(&completerM);
   edit->setCompleter(comp);

  
}

void views::textEditor::textChanged(const QString& text)
{
    static QString s;
    
    if(text.size() > CHAR_LIMIT)
    {
	     
	   if(comp!=0)
	   {
		delete comp;
	   }
	   comp=new QCompleter(this);
	   comp->setCaseSensitivity(Qt::CaseInsensitive);
	   comp->setCompletionColumn(tag()+1); 	   
  
	   edit->setCompleter(comp);
	   
	   tagQ.init(tag(),core::queryGrt::STARTS,text);
	   qDebug()<<"tag1 "<<tag();
	   qDebug()<<"Q "<<q->queryString(tag() );
	   QSqlQueryModel *m=new QSqlQueryModel(this);
// 	   completerM.setQuery(q->queryString(tag() ) );
	   m->setQuery(q->queryString(tag() ) );
	   comp->setModel(m);	   	   
	   
    }
}
