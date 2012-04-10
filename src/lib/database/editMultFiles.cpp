#include"editMultFiles.h"
#include<database.h>
#include<QDebug>
void database::editMultFiles::editFiles::run()
{
    database::db()->getDatabase();
    foreach(audioFiles::audioFile f,fileList)
    {	   
	   f.setTag(tag_,value_);
    }
    database::db()->closeDatabase();
}

void database::editMultFiles::finishedSlot()
{
    num--;
    if(num==0)
    {
        emit finished();
    }
}

void database::editMultFiles::editFiles::start()
{
//     core::db->multFilesNum++;
    editMultFiles::self()->prepare(this);
    QThread::start();
}

database::editMultFiles::editFiles::editFiles(QObject* parent): QThread(parent)
{
    tag_=-1;
    
}


int database::editMultFiles::num=0;
database::editMultFiles* database::editMultFiles::p=0;