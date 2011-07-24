#include"tagEditor.h"
#include"textEditor.h"
#include"ratingEditor.h"
#include"../ratingWidget/ratingWidget.h"
#include"numberEditor.h"
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
    foreach(QModelIndex in,list)
    {
	   model->setData(in,editor->value() ); 
    }
}
