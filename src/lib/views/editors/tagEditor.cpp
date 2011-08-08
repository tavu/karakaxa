#include"tagEditor.h"
#include"textEditor.h"
#include"ratingEditor.h"
#include"../ratingWidget/ratingWidget.h"
#include"numberEditor.h"
#include"../models/urlRole.h"
#include"../../files/audioFiles.h"

views::tagEditor* views::tagEditor::getEditor(int tag,QWidget *parent)
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
		  return new numberEditor(TRACK,parent);
	   }
	   case YEAR:
	   {
		  return new numberEditor(YEAR,parent);
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
	   default:
	   {
		  return 0;
	   }
    }  
}

bool views::tagEditorFactory::setModelData(tagEditor* editor, QAbstractItemModel* model, const QModelIndex& index, const QModelIndexList& list)
{
    if(editor->tag()==audioFiles::RATING)
    {
	   model->setData(index,editor->value());
	   return true;
    }      
    
    if(list.isEmpty() )
    {
	   model->setData(index,editor->value() );
    }
    else
    {	   
	   QList<audioFiles::audioFile>l;
	   l.reserve(list.size() );
	   foreach(QModelIndex in,list)
	   {
		  QUrl u=in.data(URL_ROLE).toUrl();
		  if(u.isValid() )
		  {
			 l<<audioFiles::audioFile(u.toLocalFile() );
		  }
	   }

	   thr=new editMultFiles::editFiles(this);
	   thr->setFiles(l);
	   thr->setTag(editor->tag() );
	   thr->setValue(editor->value());
	   connect(thr,SIGNAL(finished()),this,SLOT(done())); 
	   thr->start();
    }
    
    return true;
}
