#ifndef DBJOB_H
#define DBJOB_H
#include<QWidget>
#include<QThread>
#include"../dbBase.h"
namespace database
{

class dbJob :public dbBase
{
    Q_OBJECT
    public:
        dbJob(QObject *parent):dbBase(parent){}
        virtual ~dbJob(){}

        virtual void start()=0;

        //returns an appropriate widget for the status bar
        virtual QWidget* widget()
        {
            return 0;
        }

    signals:
        void finished();
        void started();

    protected slots:
        virtual void cancel()=0;
};


typedef QSharedPointer<database::dbJob> dbJobP;

}
#endif
