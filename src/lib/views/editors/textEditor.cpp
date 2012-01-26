#include"textEditor.h"
#include<QCompleter>
#include<QSqlTableModel>
#include<QSpinBox>
#include"../ratingWidget/ratingWidget.h"
#include<QLineEdit>

#define CHAR_LIMIT 3

views::textEditor::textEditor(int tag,QWidget *parent)
  :QLineEdit(parent),
  comp(0)
{
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
   setCompleter(comp);
}

QWidget* views::getEditor(int tag,QWidget *parent)
{
    using namespace audioFiles;
    switch (tag)
    {
       case ALBUM:
       {
          return new textEditor(ALBUM,parent);
       }
       case TITLE:
       {
          return new textEditor(TITLE,parent);
       }
       case COMPOSER:
       {
          return new textEditor(COMPOSER,parent);
       }
       case GENRE:
       {
          return new textEditor(GENRE,parent);
       }
       case COMMENT:
       {
          return new textEditor(COMMENT,parent);
       }
       case TRACK:
       {
            QSpinBox *editor=new QSpinBox(parent);
            editor->setMaximum(3000);
            editor->setMinimum(0);
            return editor;
       }
       case YEAR:
       {
            QSpinBox *editor=new QSpinBox(parent);
            editor->setMaximum(3000);
            editor->setMinimum(0);
            return editor;
       }
       case RATING:
       {
          return new ratingWidget(parent);
       }
       case LEAD_ARTIST:
       {
          return new textEditor(LEAD_ARTIST,parent);
       }
       case ARTIST:
       {
          return new textEditor(ARTIST,parent);
       }
       case PATH:
       {
          QLineEdit *editor=new QLineEdit(parent);
          editor->setReadOnly(true);
          return editor;
       }
       default:
       {
          return 0;
       }
    }
}