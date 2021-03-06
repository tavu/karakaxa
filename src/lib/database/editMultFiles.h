#ifndef EDITMULTFILES_H
#define EDITMULTFILES_H

#include<QThread>
#include<audioFiles.h>
// #include "func.h"
#include<QDebug>

namespace database
{

/*
 * this is a class appropriate for editing multiple audiofiles on a different thread
 */

class editMultFiles :public QObject
{
    Q_OBJECT
    private:    
        static editMultFiles *p;
        
    public:
        class editFiles :public  QThread 
    {
        public:
            editFiles(QObject* parent = 0);

            QList<audioFiles::audioFile> files()
            {
                return fileList;
            }

            void setFiles(const QList<audioFiles::audioFile> &list)
            {
                fileList=list;
            }

            int tag()
            {
                return tag_;
            }

            void setTag(int t)
            {
                tag_=t;
            }

            QVariant value()
            {
                return value_;
            }

            void setValue(const QVariant &var)
            {
                value_=var;
            }

            void start();

        protected:
            void run();
            int tag_;
            QVariant value_;
            QList<audioFiles::audioFile> fileList;
            QList<int> errors;            
    }; 
    
    friend class editFiles;
    
        editMultFiles() :QObject()
        {
            num=0;
        }

        static editMultFiles* self()
        {
            if(p==0)
            {
                p=new  editMultFiles();
            }
            return p;
        }

        static bool isEditing()
        {
            if(num>0)
            {
                return true;
            }
            return false;
        }
        

            

    private:
        static int num;        
        
        QMutex mutex;

        void multFilesEmiter()
        {
            emit finished();
        }

        void prepare(editFiles *p)
        {            
            mutex.lock();
            num++;
            mutex.unlock();
            connect(p,SIGNAL(finished()),this,SLOT(finishedSlot()));
            if(num==1)
            {
                emit started();
            }
        }
    	
    private slots:
        void finishedSlot();
    
    signals:
        void finished();
        void started ();

    
    
};
    
}
#endif