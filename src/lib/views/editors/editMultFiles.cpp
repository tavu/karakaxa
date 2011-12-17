#include"editMultFiles.h"
#include"database/database.h"
#include<QDebug>
void views::editMultFiles::editFiles::run()
{
    core::db->getDatabase();
    foreach(audioFiles::audioFile f,fileList)
    {	   
	   f.setTag(tag_,value_);
	   qDebug()<<"ERer "<<f.error();
    }
    core::db->closeDatabase();   
}

void views::editMultFiles::finishedSlot()
{
    num--;
//     qDebug()<<"EDITTT";
    if(num==0)
    {
// 	qDebug()<<"EDITTT";
// 	multFilesEmiter();
// 	p=0;
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