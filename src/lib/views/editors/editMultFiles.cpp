#include"editMultFiles.h"
#include<database.h>
#include<QDebug>
void views::editMultFiles::editFiles::run()
{
    database::db()->getDatabase();
    foreach(audioFiles::audioFile f,fileList)
    {	   
	   f.setTag(tag_,value_);
// 	   qDebug()<<"ERer "<<f.error();
    }
    database::db()->closeDatabase();
}

void views::editMultFiles::finishedSlot()
{
    num--;
    if(num==0)
    {
        emit finished();
    }
}

void views::editMultFiles::editFiles::start()
{
//     core::db->multFilesNum++;
    editMultFiles::self()->prepare(this);
    QThread::start();
}

views::editMultFiles::editFiles::editFiles(QObject* parent): QThread(parent)
{
    tag_=-1;
    
}


int views::editMultFiles::num=0;
views::editMultFiles* views::editMultFiles::p=0;