#ifndef DBTHRJOB_H
#define DBTHRJOB_H
#include "dbJob.h"
#include"dbJob.h"
namespace database
{
class dbThrJob :public dbJob
{
    Q_OBJECT
    protected:

        class dbJobThread :public QThread
        {
            public:
               dbJobThread(dbThrJob *parent):QThread(parent){}
            protected:
               void run()
               {
                    static_cast<dbThrJob*>(parent() )->run();
               }
        };

    public:
        dbThrJob(QObject *parent) :dbJob(parent)
        {
            thr=new dbJobThread(this);
            connect(thr,SIGNAL(finished()),this,SLOT(done() ) );
        }

        ~dbThrJob(){};

        //the start function starts the execution of the thread.
        //if you want to make any work before the thread stars reimplement this function.
        void start()
        {
            thr->start();
            emit started();
        }

        QThread* thread()
        {
            return thr;
        }

        //instead of start you have to implement the run function.
        virtual void run()=0;


    protected slots:

        //reimplement this function if u want to do some clean up on the main thread
        virtual void done()
        {
            emit finished();
        }
    private:
        dbJobThread *thr;
};

}
#endif