#ifndef DATABASESCANNER_H
#define DATABASESCANNER_H

#include "dbTypes.h"
#include<QThread>
#include<QSharedPointer>
namespace core
{

class databaseScanner :public QThread
{
    public:
        friend class database;
        databaseScanner(dbState t,QObject *parent=0) :QThread(parent)
        {
            _type=t;
        }

        dbState type()
        {
            return _type;
        }

        void scan();
        //void stop()=0;

        virtual QWidget *widget()
        {
            return 0;
        }

    protected:
        //give the posibility to make some initialization befora start the thread
        virtual void startScan()
        {
            start();
        }

        
    private:
        dbState _type;
};
typedef QSharedPointer<core::databaseScanner> dbScanner;

}

#endif