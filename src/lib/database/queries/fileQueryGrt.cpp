#include"fileQueryGrt.h"
database::filesQueryGrt::filesQueryGrt(QObject* parent)
  :queryGrt(parent)
{
//    connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

database::filesQueryGrt::filesQueryGrt(abstractQuery *qe,QObject* parent)
  :queryGrt(parent)
{
   q=qe;

//    connect(&thr,SIGNAL(finished()),this,SLOT(selectionFinished()) );
}

bool database::filesQueryGrt::select()
{
	/*
    emit selectionCalled();
    _needUpdate=false;
    thr.files.clear();
	resultsList.clear();
    if(q==0||!q->isValid() ||thr.isRunning() )
    {
        return false;
    }

   thr.start();
   thr.wait();
   _needUpdate=false;
   return true;
   */
	emit selectionCalled();
    _needUpdate=false;
	files.clear();
	resultsList.clear();
    if(q==0||!q->isValid() )
    {
        return false;
    }

   doSelect();
   _needUpdate=false;
   emit selectionMade();
   return true;

}

bool database::filesQueryGrt::doSelect()
{  
    QSqlDatabase dBase=db()->getDatabase();        
	bool ret;
    {
        QSqlQuery quer(dBase );

        if(!quer.exec( queryString() ) )
        {            
            ret=false;
        }
        else 
		{
			if(quer.size()>0 )
			{
				files.reserve(quer.size() );
				resultsList.reserve(quer.size() );
			}

			while ( quer.next() )
			{
				audioFiles::audioFile f(quer.record() );
				files.append(f);
				map.insert(f.path(),f);
				QVariant var;
				var.setValue(f);
				audioFiles::tagInfo t(audioFiles::FILES,var);
				resultsList<<t;
			}
			ret=true;
		}
    }
    
    db()->closeDatabase(dBase);
	return ret;
}

/*
void database::filesQueryGrt::selectionFinished()
{
	foreach(audioFiles::audioFile f,thr.files)
	{		
		QVariant var;
		var.setValue(f);
		audioFiles::tagInfo t(audioFiles::FILES,var);
		resultsList<<t;
	}
	emit selectionMade();
} 
*/

void database::filesQueryGrt::dbEvents(database::dbEventP e)
{
    using namespace audioFiles;
    if(needUpdate() )
    {
        return ;
    }
    
    if(e->type()==FILES_CHANG)
    {        
        dbEventAF *ev = static_cast<dbEventAF*>(e.data());
        
        foreach(const audioFile &f, ev->files)
        {
            if(q!=0 && q->match(f) )
            {
                setNeedUpdate();
                return ;
            }
        }
    }
//     queryGrt::dbEvents(e);
}
