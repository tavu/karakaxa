#ifndef DATABASESCANNER_H
#define DATABASESCANNER_H

#include<QThread>
#include<QSharedPointer>

#include"databaseEvent.h"
#include "dbTypes.h"



namespace database
{

class databaseScanner :public QThread
{
    public:
        friend class databaseConection;
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

        dbEventP eventPointer()
        {
            return eventP;
        }

    protected:
        //give the posibility to make some initialization befora start the thread
        virtual void startScan()
        {
            start();
        }

        dbEventP eventP;
    private:
        dbState _type;
        
};

typedef QSharedPointer<database::databaseScanner> dbScanner;
}

#endif