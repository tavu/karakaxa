#include"folderEditorFactory.h"

/*
bool folderEditorFactory::setModelData(views::tagEditor* editor, QAbstractItemModel* model, const QModelIndex& index, const QModelIndexList& list)
{
//     return tagEditorFactory::setModelData(editor,model,index,list);
    if(editor->tag()==audioFiles::RATING)
    {
	   model->setData(index,editor->value());
	   return true;
    }
  
    QLinkedList<audioFiles::audioFile>l;
    
    if(list.isEmpty() )
    {
	   model->setData(index,editor->value() );
    }
    else
    {
	   foreach(QModelIndex in,list)
	   {
		  QUrl u=in.data(URL_ROLE).toUrl();
		  if(u.isValid() )
		  {
			 l<<audioFiles::audioFile(u.toLocalFile() );
		  }
	   }
	   
	   editThr *thr=new editThr(editor->tag(),editor->value(),l,this);
	   connect(thr,SIGNAL(finished()),this,SLOT(thrFinished() ) );
	   thr->start();
    }
    
    return true;
}

*/


void folderEditorFactory::done()
{    
//      delete sender();
     views::tagEditorFactory::done();
     view->viewport()->update();          
}


