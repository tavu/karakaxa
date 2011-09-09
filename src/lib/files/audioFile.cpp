#include"audioFile.h"
#include<QtDebug>
#include<QFileInfoList>
#include<QDir>
// #include<player.h>
#include"fileToDb.h"
#include"mp3Tags.h"
#include"../core/database/database.h"
#include"../core/func.h"
#define TRV_HIDE 1


// using namespace player;



const short int audioFiles::audioFile::ONDATAB=   0b00010000;
const short int audioFiles::audioFile::SELECT =   0b00000001;
const short int audioFiles::audioFile::ONCACHE=   0b00000010;
const short int audioFiles::audioFile::LOAD_FILE =0b00000100;
const short int audioFiles::audioFile::TITLEFP=   0b00001000;
const short int audioFiles::audioFile::DEFAULTF=SELECT|ONDATAB|ONCACHE|LOAD_FILE|TITLEFP;

audioFiles::audioFile::audioFile()
        :QObject(),
        fileSize(0),
        saveFlag(true),
        cache(0),
        fdb(0)
{    
}

audioFiles::audioFile::audioFile(const QString url)
        :QObject(),
        fileSize(0),
        saveFlag(true)
{
    cache=audioFiles::fileCache::getFileCache(url);
    
//     connect(cache,SIGNAL(changed(QList<tagChanges>) ),this,SLOT(emitChanged(QList<tagChanges>) ) );
}

audioFiles::audioFile::audioFile(QSqlRecord r, bool force)
    :QObject(),
     fileSize(0),
     saveFlag(true)
{
    cache=audioFiles::fileCache::getFileCache(r.value(PATH+1).toString() );
    cache->setRecord(r,force);
//     connect(cache,SIGNAL(changed(QList<tagChanges>) ),this,SLOT(emitChanged(QList<tagChanges>) ) );
}


audioFiles::audioFile::audioFile(const audioFile &f)
        :QObject(),
        saveFlag(true)
{
     if( !f.path().isEmpty() )
     {
	cache=audioFiles::fileCache::getFileCache(f.path() );
// 	connect(cache,SIGNAL(changed(QList<tagChanges>) ),this,SLOT(emitChanged(QList<tagChanges>) ) );
     }
//      changes.clear();
     changes.append(f.changes);
     fileSize=f.fileSize;

}



audioFiles::audioFile::~audioFile()
{
    audioFiles::fileCache::releaseFileCache(cache);
//     delete file;
}


QVariant audioFiles::audioFile::tag(int t, const short int f) const
{
  
/*
    this function return the tag info from the file.
    it tags a flag as an argument witch specifies the place tha the tag would be red.
    we can take the tag from the database by executing a select query(ONDATAB).
    we can save the returned values from the query and using it without executing select again(DBCACHE).
    we can read the tag from the file(ONFILE).that proces also save the tag on a cache.
    at last we can use that cache to read the tag(ONCACHE).
    
    a flag can has a lot of values using bit OR '|'.
    the order tha we would search for the values is DBCACHE,ONCACHE,ONDATAB,ONFILE
    if you want another order use this function more than one with different flag.
    
*/
    QVariant ret;
         
    if(cache==0)
    {
	err=INVALID_FILE;
	return ret;
    }

    if(t>=FRAME_NUM)
    {
	err=UNOWN;
	stat=-1;
	return ret;
    }    
    if (t==PATH)
    {
	stat=-1;
        return path();
    }
    if (f & ONDATAB)
    {
	//the first field of the record conteins the albumId
	   ret=cache->tagFromDb(t+1, err);
        if (err==OK)
        {
	    if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) )
	    {	    
		stat= TITLEFP;
		ret=core::titleFromPath(path());
		return ret;
	    }
	    stat=ONDATAB;
	    return ret;
        }
    }
    if (f & ONCACHE)
    {	      
	stat=ONCACHE;
	ret=cache->tagFromFile((tagsEnum) t, err);
	
	//if we have loaded the tags information but there is no title frame and the TITLEFP is seted we return the file name.
	if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) && err!=TAGS_NOT_LOADED)
        {	    
 	    stat= TITLEFP;
 	    ret=core::titleFromPath(path());
        }
        if(err==OK)
	{
	    return ret;
	} 
    }

    if (f & SELECT)
    {
       err=cache->select();
       if(err==OK)
       {
	  stat=SELECT;
	  QString s=cache->tagFromDb((tagsEnum) t, err).toString().trimmed();	  
	  ret=QVariant(s);
       }
    }

    if (f & LOAD_FILE)
    {
	cache->loadTags();
        ret=cache->tagFromFile((tagsEnum) t, err);
	
	//if we have loaded the tags information but there is no title frame and the TITLEFP is seted we return the file name.
	if (t==TITLE && ret.toString().isEmpty() && (f & TITLEFP) && err!=TAGS_NOT_LOADED)
        {	    
	    stat= TITLEFP;
 	    ret=core::titleFromPath(path());
	    return ret;
        }
        stat=ONCACHE;
        return ret;
    }
    err=UNOWN;
    stat=-1;
    return ret;        
}

bool audioFiles::audioFile::setTag(int t,QVariant var)
{            
    if(cache==0)
    {
	   err=INVALID_FILE;
	   return false;
    }
  
    if(t>=FRAME_NUM || t<0)
    {
	   err=UNOWN;
	   return false;
    }    
  
    if(!prepareToSave())
    {
	   return false;
    }      
    
    fdb->setAlbum ( tag(ALBUM,ONDATAB|SELECT).toString()  );
    fdb->setArtist( tag(ARTIST,ONDATAB).toString() );
    
    file->setTag( (tagsEnum)t,var);
    err=file->error();
    
    if(err==OK)
    {
	cache->setTag((tagsEnum)t,var,1);
	err=fdb->setTag(t,var);
    }
    else if(err==NS_TAG)
    {	
	err=fdb->setTag(t,var);
    }
      
    if(err==OK)
    {
      cache->setTag((tagsEnum)t,var,2);
    }
    

    tagChanges change;
    change.tag=t;
    change.value=var;
    change.error=err;
    
    changes<<change;
        
    save();

    if(err==OK||err==NOTINDB)
    {
	 return true;  
    }

    return false;
}

void audioFiles::audioFile::setTags(QList<int> tags,QList<QVariant> values)
{
    if(cache==0)
    {
	err=INVALID_FILE;
	return ;
    }
    
    if(tags.isEmpty() ||tags.size()!=values.size() )
    {
	err=UNOWN;
	return ;
    }
    if(!prepareToSave() )
    {
	return ;
    }
    
    saveFlag=false;
    for(int i=0;i<tags.size();i++ )
    {
	setTag(tags.at(i),values.at(i) );
    }
    
    saveFlag=true;
    save();
      
}

QVariant  audioFiles::audioFile::albumArtist()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return QVariant();
    }
    
    QString s=tag(LEAD_ARTIST).toString();
    s=s.simplified();
    if ( !s.isEmpty() )
    {
        return QVariant(s);
    }

    return tag(ARTIST);
}

QString audioFiles::audioFile::cover()
{
    fdb=new fileToDb(path() );
    QString coverPath=fdb->albumArt(albumId(),err);
    
    //if there is no album art on database we search on directory
    if(coverPath.isEmpty() )
    {
	   QLinkedList<QString> covers; 
	   QDir dir(core::folder(path() ) );
	   QFileInfoList infoList=dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot); 
	   
	   for (int i=0;i<infoList.size();i++)  
	   {
		  if(core::isImage(infoList.at(i).absoluteFilePath() ) )
		  {
			 covers<<infoList.at(i).absoluteFilePath();
		  }
	   }
	   
	   QString album=tag(ALBUM).toString();
 	   audioFiles::bestCover(covers,album,coverPath);	
    }    
    
    qDebug()<<"COVER "<<coverPath;
    return coverPath;
}

int audioFiles::audioFile::size()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return 0;
    }
    
    if (fileSize==0)
    {
        QFile f(path() );
        fileSize=f.size();
    }
    return fileSize;
}

int audioFiles::audioFile::albumId()
{
    if(cache==0)
    {
	err=INVALID_FILE;
	return -1;
    }
    
    err=cache->select();
    
    if(err!=OK)
    {
	return -1;
    }
    return cache->tagFromDb(0,err).toInt();
}

bool audioFiles::audioFile::prepareToSave()
{
    if(!saveFlag)
    {
      err=OK;
      return true;
    }
    
    changes.clear();
    file=audioFiles::getFileTags(path()); 
    fdb=new fileToDb(path() );
    
    if(file->isValid() )
    {
	   err=fdb->prepare();
    }
    else
    {
	   err=INVALID_FILE;
    }    
    
    if(err==OK)
    {
	   cache->lockForSaving();
	   return true;
    }
    
    return false;
}

void audioFiles::audioFile::save()
{
    if(!saveFlag)
    {
	return;
    }
    
    file->save();
    int e=fdb->commit();
    
    if(e!=OK)
    {
	err=e;
    }
        
    delete file;    
    file=0;
    delete fdb;
    fdb=0;
    
    cache->savingEnd(changes );
    
    audioFile f(*this);
    qDebug()<<"save "<<f.tagChanged().size();
    core::db->updateSig(f);
    
    
}

void audioFiles::audioFile::load(const short int f)
{
    if(cache==0)
    {
	err=INVALID_FILE;
	return ;
    }
  
    if(f & SELECT)
    {
	stat=SELECT;
	err=cache->select();
	if(err==OK)
	{
	    return ;
	}
    }
    
    if(f & LOAD_FILE)
    {
	stat=LOAD_FILE;
 	err=cache->loadTags();
    }
    else
    {    
	stat=UNOWN;
	err=UNOWN;
    }
}

audioFiles::audioFile* audioFiles::audioFile::operator=(const audioFile &f)
{
    saveFlag=true;

    if(f.cache!=0)
    {
	cache=audioFiles::fileCache::getFileCache(f.path() );
    }
    
    changes.append(f.changes);
    fileSize=f.fileSize;
    return this;
}

QString audioFiles::audioFile::folder()
{
    if(cache==0)
    {
	err=INVALID_FILE;
	return QString();
    }
    
    return core::folder(path() );
}

QString audioFiles::audioFile::format()
{     
    if(cache==0)
    {
	err=INVALID_FILE;
	return QString();
    }
      
    return core::format(path() );
}

bool audioFiles::audioFile::inDataBase(bool force)
{
    if( cache==0)
    {
	 err=INVALID_FILE;
	 return false;
    }
    
    err=cache->select(force);
    
    if(err==OK)
    {
	   return true;
    }
    
    return false;
}


/*
void audioFiles::audioFile::recordClean()
{
//     recFlag=true;
//     record.clear();
}
*/
